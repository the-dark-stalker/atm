
#ifndef CRECEIPTPRINTER_H
#define CRECEIPTPRINTER_H
#include "Device.h"

#include <string>

//* class ReceiptPrinter
class ReceiptPrinter : public Device
{
public:
  ReceiptPrinter();
  virtual ~ReceiptPrinter();

  /**
   * Set the value of receipt
   * @param new_var the new value of receipt
   */
  void setReceipt (std::string new_var)   {
      receipt = new_var;
  }

  /**
   * Get the value of receipt
   * @return the value of receipt
   */
  std::string getReceipt() {
    return receipt;
  }
private:
  std::string receipt;
};

#endif // CRECEIPTPRINTER_H
