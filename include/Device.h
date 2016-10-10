
#ifndef CDEVICE_H
#define CDEVICE_H
#include "Base.h"

#include <string>

//* class Device
class Device : public Base
{
public:
  Device();
  virtual ~Device();

  /**
   * Set the value of slot
   * @param new_var the new value of slot
   */
  void setSlot (int new_var)   {
      slot = new_var;
  }

  /**
   * Get the value of slot
   * @return the value of slot
   */
  int getSlot() {
    return slot;
  }
private:
  int slot;
};

#endif // CDEVICE_H
