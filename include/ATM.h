
#ifndef ATM_H
#define ATM_H
#include "Base.h"

#include "ATM.h"
#include "Base.h"
#include "CardReader.h"
#include "CashDispenser.h"
#include "Connection.h"
#include "Console.h"
#include "Deposit.h"
#include "Device.h"
#include "EnvelopeAcceptor.h"
#include "InetAddress.h"
#include "Logger.h"
#include "Network.h"
#include "Person.h"
#include "ReceiptPrinter.h"
#include "Transaction.h"
#include "Volume.h"

#include <string>

//* class ATM

class ATM;

class State
{
  public:
  virtual void on(ATM *m) {
    std::cout << "   already ON\n";
  }

  virtual void off(ATM *m) {
    std::cout << "   already OFF\n";
  }
};

class ATM : public Base
{
  State * current;
public:
  ATM();
  virtual ~ATM();

  void setCurrent(State *s) {
    current = s;
  }

  void on();
  void off();

  /**
   * Set the value of id
   * @param new_var the new value of id
   */
  void setId (int new_var)   {
      id = new_var;
  }

  /**
   * Get the value of id
   * @return the value of id
   */
  int getId() {
    return id;
  }

  /**
   * Set the value of place
   * @param new_var the new value of place
   */
  void setPlace (std::string new_var)   {
      place = new_var;
  }

  /**
   * Get the value of place
   * @return the value of place
   */
  std::string getPlace() {
    return place;
  }

  /**
   * Set the value of bankName
   * @param new_var the new value of bankName
   */
  void setBankName (std::string new_var)   {
      bankName = new_var;
  }

  /**
   * Get the value of bankName
   * @return the value of bankName
   */
  std::string getBankName() {
    return bankName;
  }

  /**
   * Set the value of cardReader
   * @param new_var the new value of cardReader
   */
  void setCardReader (CardReader new_var)   {
      cardReader = new_var;
  }

  /**
   * Get the value of cardReader
   * @return the value of cardReader
   */
  CardReader getCardReader() {
    return cardReader;
  }

  /**
   * Set the value of customerConsole
   * @param new_var the new value of customerConsole
   */
  void setCustomerConsole (Console new_var)   {
      customerConsole = new_var;
  }

  /**
   * Get the value of customerConsole
   * @return the value of customerConsole
   */
  Console getCustomerConsole() {
    return customerConsole;
  }

  /**
   * Set the value of log
   * @param new_var the new value of log
  void setLog (Logger new_var)   {
      log = new_var;
  }
   */

  /**
   * Get the value of log
   * @return the value of log
  Logger getLog() {
    return log;
  }
   */

  /**
   * Set the value of networkToBank
   * @param new_var the new value of networkToBank
   */
  void setNetworkToBank (Connection new_var)   {
      networkToBank = new_var;
  }

  /**
   * Get the value of networkToBank
   * @return the value of networkToBank
   */
  Connection getNetworkToBank() {
    return networkToBank;
  }

  /**
   * Set the value of cashDispenser
   * @param new_var the new value of cashDispenser
   */
  void setCashDispenser (CashDispenser new_var)   {
      cashDispenser = new_var;
  }

  /**
   * Get the value of cashDispenser
   * @return the value of cashDispenser
   */
  CashDispenser getCashDispenser() {
    return cashDispenser;
  }

  /**
   * Set the value of receiptPrinter
   * @param new_var the new value of receiptPrinter
   */
  void setReceiptPrinter (ReceiptPrinter new_var)   {
      receiptPrinter = new_var;
  }

  /**
   * Get the value of receiptPrinter
   * @return the value of receiptPrinter
   */
  ReceiptPrinter getReceiptPrinter() {
    return receiptPrinter;
  }

  /**
   * Set the value of ipAddress
   * @param new_var the new value of ipAddress
   */
  void setIpAddress (InetAddress new_var)   {
      ipAddress = new_var;
  }

  /**
   * Get the value of ipAddress
   * @return the value of ipAddress
   */
  InetAddress getIpAddress() {
    return ipAddress;
  }

  /**
   * Set the value of envelopeAcceptor
   * @param new_var the new value of envelopeAcceptor
   */
  void setEnvelopeAcceptor (EnvelopeAcceptor new_var)   {
      envelopeAcceptor = new_var;
  }

  /**
   * Get the value of envelopeAcceptor
   * @return the value of envelopeAcceptor
   */
  EnvelopeAcceptor getEnvelopeAcceptor() {
    return envelopeAcceptor;
  }
private:
  int id;
  std::string place;
  std::string bankName;
  CardReader cardReader;
  Console customerConsole;
  Connection networkToBank;
  CashDispenser cashDispenser;
  ReceiptPrinter receiptPrinter;
  InetAddress ipAddress;
  EnvelopeAcceptor envelopeAcceptor;
  Logger * log;
  void initAttributes() {}
};

class ON: public State
{
  public:
    ON()
    {
        std::cout << "   ON-ctor ";
    };
    ~ON()
    {
        std::cout << "   dtor-ON\n";
    };
    void off(ATM *m);
};
 
class OFF: public State
{
  public:
    OFF()
    {
        std::cout << "   OFF-ctor ";
    };
    ~OFF()
    {
        std::cout << "   dtor-OFF\n";
    };
    void on(ATM *m)
    {
        std::cout << "   going from OFF to ON";
        m->setCurrent(new ON());
        delete this;
    }
};
 
void ON::off(ATM *m)
{
  std::cout << "   going from ON to OFF";
  m->setCurrent(new OFF());
  delete this;
}

class Command {
public:
  virtual ~Command() {}

  virtual void execute() = 0;
};

template <class Receiver>
class ConcreteCommand : public Command {
public:
    typedef void (Receiver::*     Action)();
    ConcreteCommand(Receiver * r, Action a) : _action(a), _receiver(r) 
    {}

    virtual ~ConcreteCommand() {}

    void execute() {
        (_receiver->*_action)();
    }
private:
    Action     _action;
    Receiver * _receiver;
};

#endif // ATM_H
