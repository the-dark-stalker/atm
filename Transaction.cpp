#include "Transaction.h"

#include <cstdlib>
#include <sstream>
#include <iostream>
#include <pqxx/connection>
#include <pqxx/field>
#include <pqxx/result>
#include <pqxx/transaction>

const bool debug = false;

typedef pqxx::result::const_iterator rIter;
typedef pqxx::const_tuple_iterator fIter;

Transaction::Transaction()
: state(false), atmxml("atm.xml") { }

bool Transaction::read() {
  if(!atmxml.LoadFile()) {
      std::cerr << "file " << atmxml.Value() << " have any errors" << std::endl;
      return false;
  }
  TiXmlElement *transaction = NULL;
  transaction = atmxml.FirstChildElement("transaction");
  if (NULL != transaction) {
    TiXmlElement *query = NULL;
    query = transaction->FirstChildElement("query");
    while (NULL != query) {
      const char * text = query->Attribute("text");
      int num_params = 0;
      TiXmlElement *param = NULL;
      switch (query->QueryIntAttribute("num_params", &num_params)) {
        case TIXML_SUCCESS:
          queries.push_back(text);
          param = query->FirstChildElement("param");
          for (int i = 0; i < num_params && NULL != param; ++i) {
            const char * name = param->Attribute("name");
            if (NULL != name && debug) {
              std::cout << "param: " << i << std::endl;
              std::cout << " name: " << name << std::endl;
            }
            const char * value = param->Attribute("value");
            if (NULL != value) {
              queries.push_back(value);
              if (debug)
                std::cout << " value: " << value << std::endl;
            }
          }
          break;
        case TIXML_WRONG_TYPE:
          std::cerr << "num_params: TIXML_WRONG_TYPE" << std::endl;
          break;
        default:
          queries.push_back(text);
          if (debug)
            std::cout << "query: " << text << std::endl;
          break;
      }
      query = query->NextSiblingElement("query");
      queries.push_back("");
    }
  } else return false;

  return true;
}

void prepare_one(pqxx::connection_base &c,const std::string &sql) {
  c.prepare(sql, sql);
}

pqxx::result
execute_one(
    pqxx::transaction_base &t,
    const std::string &sql,
    const std::string value) {
  return t.prepared(sql)(value).exec();
}

bool
Transaction::run_prepare(pqxx::connection_base &c, const std::string &query) {
  state = false;
  try {
    prepare_one(c, query);
    state = true;
  } catch (...) {
    std::cerr << "Запрос не был подготовлен: " << query << std::endl;
  }
  return state;
}

bool
Transaction::run_execute(pqxx::transaction_base &t, queryIter &i) {
  state = false;
  if (debug)
    std::cout << "execute: " << *i << std::endl;
  queryIter e;
  int count = 0;
  for (e = (i + 1); e != queries.end() && *e != ""; ++e, ++count) {
    if (debug)
      std::cout << "param[" << count << "] = " << *e << std::endl;
  }
  try {
    pqxx::result res;
    switch (count) {
      case 0:
        res = t.exec(*i);
        break;
      case 1:
        res = execute_one(t, *i, *(i + 1));
        break;
    }
    if (!res.size()) {
      std::cout << "Пустой вывод." << std::endl;
      t.commit();
    } else {
      // Show results
      for (rIter i = res.begin(), r_end = res.end(); i != r_end; ++i) {
        // Iterate fields
        for (fIter f = i->begin(), f_end = i->end(); f != f_end; ++f) {
          std::cout << f->name() << " = '" << f->c_str() << "'" << std::endl;
        }
        std::cout << std::endl;
      }
    }
    state = true;
  } catch (...) {
    std::cout << "Запрос не был выполнен: " << std::endl;
  }
  i = e;
  return state;
}

bool Transaction::run() {
  std::ostringstream oss;
  oss << "dbname=" << getenv("USER");
  oss << " user=" << getenv("USER");
  std::string conn_string(oss.str());
  try {
    pqxx::connection conn(conn_string);
    for (queryIter i = queries.begin(); i != queries.end(); ++i) {
      if (debug)
        std::cout << "iterate: " << *i << std::endl;
      if (*i == "") continue;
      pqxx::work xact(conn, "Transaction");
      const std::string &query = *i;
      if (not run_prepare(conn, query))
          throw std::runtime_error("Error in prepare");
      if (not run_execute(xact, i))
          throw std::runtime_error("Error in execute");
    }
  } catch (pqxx::broken_connection) {
    std::cout << "Ошибка: establish connection." << std::endl;
    state = false;
    return state;
  } catch (std::runtime_error & e) {
    std::cout << e.what() << std::endl;
    state = false;
    return state;
  }
  std::cout << "Запрос успешно выполнен." << std::endl;
  return true;
}

Transaction::~Transaction() { }
