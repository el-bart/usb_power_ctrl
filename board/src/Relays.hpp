#ifndef INCLUDE_PORTS_HPP_FILE
#define INCLUDE_PORTS_HPP_FILE

#include "config.hpp"

#include <avr/io.h>
#include <inttypes.h>


class Relays
{
public:
  Relays(void);

  void set(uint8_t n, bool state);
  bool get(uint8_t n) const;

  void setDefault(uint8_t n, bool state);
  bool getDefault(uint8_t n) const;

private:
  bool state_[PORTS_COUNT];
};

#endif
