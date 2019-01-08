#pragma once

#include "bulk.h"
#include "observer.h"
#include <chrono>
#include <fstream>
#include <memory>
#include <queue>
#include <sstream>

#include <iostream>

class CommandReceiver : public Observable {
  size_t open_bracket_count = 0;
  std::istream& is;
  std::queue<std::shared_ptr<Bulk>> blks;
public:
  CommandReceiver(std::istream& is) : is(is) {
    createBulk();
  }

  void startReceiving() {
    std::string tmp;
    while(std::getline(is, tmp)) {
      if(tmp == "{") {
        if(blks.front()->cmds.size() && 0 == open_bracket_count) {
          createBulk();
        }
        open_bracket_count++;
      } else if(tmp == "}") {
        if(0 == --open_bracket_count)
          createBulk();
      } else {
        if(0 == blks.back()->cmds.size())
          blks.back()->init = static_cast<int>(
              static_cast<std::chrono::seconds>(std::time(nullptr)).count());
        blks.back()->cmds.emplace_back(Cmd{tmp});
      }
    }
    if(blks.size() && blks.front()->cmds.size() && !open_bracket_count)
      bulkReceived();
  }

  void createBulk() {
    if(blks.size())
      bulkReceived();
    blks.push(std::make_shared<Bulk>());
  }

  std::shared_ptr<Bulk> getBulk() const {
    return blks.front();
  }

  void bulkReceived() {
    setChanged();
    notifyObservers();
    blks.pop();
  }
};

class CommandSender : public Observer {
  std::ostream& os;
public:
  CommandSender(std::ostream& os) : os(os) {}
  void update(const Observable& receiver) override {
    os << *dynamic_cast<const CommandReceiver&>(receiver).getBulk().get();
    os << std::endl;
  }
};

class CommandWriter : public Observer {
public:
  void update(const Observable& receiver) override {
    auto bulk = dynamic_cast<const CommandReceiver&>(receiver).getBulk();
    std::ofstream ofs("bulk" + std::to_string(bulk->init) + ".log", std::ofstream::out);
    ofs << *bulk.get();
    ofs << std::endl;
    ofs.close();
  }
};
