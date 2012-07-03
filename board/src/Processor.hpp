#ifndef INCLUDE_PROCESSOR_HPP_FILE
#define INCLUDE_PROCESSOR_HPP_FILE

#include "Tokenizer.hpp"


class Processor
{
public:
  void process(char *buf);

private:
  void error(const char *msg) const;
  void handleHello(Tokenizer& tokenizer) const;
  void handlePort(Tokenizer& tokenizer) const;
  void handleDefault(Tokenizer& tokenizer) const;
  void handleStatus(Tokenizer& tokenizer) const;
};

#endif
