
#ifndef CCONSOLE_H
#define CCONSOLE_H
#include "Device.h"

#include <string>

//* class Console
class Console : public Device
{
public:
  Console();
  virtual ~Console();

  /**
   * Set the value of display
   * @param new_var the new value of display
   */
  void setDisplay (std::string new_var)   {
      display = new_var;
  }

  /**
   * Get the value of display
   * @return the value of display
   */
  std::string getDisplay() {
    return display;
  }
private:
  std::string display;
};

#endif // CCONSOLE_H
