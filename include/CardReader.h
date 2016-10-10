
#ifndef CCARDREADER_H
#define CCARDREADER_H
#include "Device.h"

#include <string>

//* class CardReader
class CardReader : public Device
{
public:
  CardReader();
  virtual ~CardReader();

  /**
   * Set the value of input
   * @param new_var the new value of input
   */
  void setInput(std::string new_var) {
      input = new_var;
  }

  /**
   * Get the value of input
   * @return the value of input
   */
  std::string getInput()  {
    return input;
  }
private:
  std::string input;
};

#endif // CCARDREADER_H
