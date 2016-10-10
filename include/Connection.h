
#ifndef CCONNECTION_H
#define CCONNECTION_H
#include "Network.h"

#include <string>

//* class Connection
class Connection : public Network
{
public:
  Connection();
  virtual ~Connection();

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

#endif // CCONNECTION_H
