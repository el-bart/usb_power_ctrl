#ifndef INCLUDE_PROCESSOR_HPP_FILE
#define INCLUDE_PROCESSOR_HPP_FILE

#include "Tokenizer.hpp"
#include "Relays.hpp"


class Processor
{
public:
  void process(char *buf);

private:
  void errorFlash(const char *msg=nullptr);
  void handleHello(Tokenizer& tokenizer);
  void handlePort(Tokenizer& tokenizer);
  void handleDefault(Tokenizer& tokenizer);
  void handleStatus(Tokenizer& tokenizer);

  Relays relays_;
};

#endif
