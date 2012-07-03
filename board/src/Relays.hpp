#ifndef INCLUDE_PORTS_HPP_FILE
#define INCLUDE_PORTS_HPP_FILE

#include "config.hpp"

#include <avr/io.h>


class Relays
{
public:
  Relays(void);

private:
  bool state_[PORTS_COUNT];
};

#endif
