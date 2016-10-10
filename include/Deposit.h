
#ifndef CDEPOSIT_H
#define CDEPOSIT_H
#include "Volume.h"
#include "Person.h"

#include <string>
#include <vector>

//* class Deposit
class Deposit : public Volume
{
public:
  Deposit();
  virtual ~Deposit();

  /**
   * Set the value of person
   * @param new_var the new value of person
   */
  void setPerson (Person new_var)   {
      person = new_var;
  }

  /**
   * Get the value of person
   * @return the value of person
   */
  Person getPerson() {
    return person;
  }
private:
  Person person;
};

#endif // CDEPOSIT_H
