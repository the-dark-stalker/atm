
#ifndef CNETWORK_H
#define CNETWORK_H
#include "Base.h"

#include <string>

//* class Network
class Network : public Base
{
public:
  Network();
  virtual ~Network();

  /**
   * Set the value of state
   * @param new_var the new value of state
   */
  void setState (bool new_var)   {
      state = new_var;
  }

  /**
   * Get the value of state
   * @return the value of state
   */
  bool getState() {
    return state;
  }
private:
  bool state;
};

#endif // CNETWORK_H
