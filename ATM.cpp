#include "ATM.h"
#include "Transaction.h"

ATM::ATM() {
  current = new OFF();
  std::cout << '\n';
  std::string file_name = "log.txt";
  log = new FileLogger(file_name);
}

ATM::~ATM() {
  delete log;
  delete current;
}

void ATM::on() {
  current->on(this);
}

void ATM::off() {
  current->off(this);
}

int main(int argc, char *argv[]) {
  Transaction transaction;
  transaction.read();
  transaction.run();

  void(ATM:: *ptrs[])() = {
    &ATM::off, &ATM::on
  };
  ATM fsm;
  Command * cmdOn = new ConcreteCommand<ATM>(&fsm, &ATM::on);
  Command * cmdOff = new ConcreteCommand<ATM>(&fsm, &ATM::off);
  cmdOn->execute();
  cmdOff->execute();
  int num;
  while (1)
  {
    std::cout << "Enter 0/1: ";
    std::cin >> num;
    (fsm.*ptrs[num])();
  }
  delete cmdOff;
  delete cmdOn;
  return 0;
}
