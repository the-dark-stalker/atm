
#ifndef CCASHDISPENSER_H
#define CCASHDISPENSER_H
#include "Device.h"

#include <string>

//* class CashDispenser
class CashDispenser : public Device
{
public:
  CashDispenser();
  virtual ~CashDispenser();

  /**
   * Set the value of cashOnHand
   * @param new_var the new value of cashOnHand
   */
  void setCashOnHand (double new_var)   {
      cashOnHand = new_var;
  }

  /**
   * Get the value of cashOnHand
   * @return the value of cashOnHand
   */
  double getCashOnHand() {
    return cashOnHand;
  }
private:
  double cashOnHand;
};

#endif // CCASHDISPENSER_H
