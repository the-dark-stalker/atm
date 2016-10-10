
#ifndef CTRANSACTION_H
#define CTRANSACTION_H
#include "Volume.h"

#include <string>
#include <vector>
#include <pqxx/connection>
#include <pqxx/transaction>
#include <tinyxml.h>

//* class Transaction
class Transaction : public Volume
{
  typedef std::vector<std::string>::const_iterator queryIter;
public:
  Transaction();
  bool read();
  bool run();
  bool run_prepare(pqxx::connection_base &c, const std::string &query);
  bool run_execute(pqxx::transaction_base &t, queryIter &i);
  virtual ~Transaction();

  /**
   * Set the value of state
   * @param new_var the new value of state
   */
  void setState (int new_var)   {
      state = new_var;
  }

  /**
   * Get the value of state
   * @return the value of state
   */
  int getState() {
    return state;
  }
private:
  int state;
  TiXmlDocument atmxml;
  std::vector<std::string> queries;
};

#endif // CTRANSACTION_H
