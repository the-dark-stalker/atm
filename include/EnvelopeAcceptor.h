
#ifndef CENVELOPEACCEPTOR_H
#define CENVELOPEACCEPTOR_H
#include "Device.h"

#include <string>

//* class EnvelopeAcceptor
class EnvelopeAcceptor : public Device
{
public:
  EnvelopeAcceptor();
  virtual ~EnvelopeAcceptor();
public:

  /**
   * Set the value of cacheIn
   * @param new_var the new value of cacheIn
   */
  void setCacheIn (double new_var)   {
      cacheIn = new_var;
  }

  /**
   * Get the value of cacheIn
   * @return the value of cacheIn
   */
  double getCacheIn() {
    return cacheIn;
  }
private:
  double cacheIn;
};

#endif // CENVELOPEACCEPTOR_H
