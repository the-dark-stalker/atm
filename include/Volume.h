
#ifndef CVOLUME_H
#define CVOLUME_H
#include "Base.h"

#include <string>

//* class Volume
class Volume : public Base
{
public:
  Volume();
  virtual ~Volume();
public:

  /**
   * Set the value of value
   * @param new_var the new value of value
   */
  void setValue (double new_var)   {
      value = new_var;
  }

  /**
   * Get the value of value
   * @return the value of value
   */
  double getValue() {
    return value;
  }
private:
  double value;
};

#endif // CVOLUME_H
