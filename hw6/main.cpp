#include "bulk.h"
#include "commander.h"
#include <iostream>

int main() {
  CommandReceiver receiver(std::cin);
  CommandSender sender(std::cout);
  CommandWriter writer;
  receiver.addObserver(sender);
  receiver.addObserver(writer);
  receiver.startReceiving();
}
