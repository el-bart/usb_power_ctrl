#include "config.hpp"

#include <avr/io.h>

#include "Relays.hpp"


Relays::Relays(void)
{
  // port PB0
  DDRB  |= _BV(PB0);
  PORTB &=~_BV(PB0);
  // port PB1
  DDRB  |= _BV(PB1);
  PORTB &=~_BV(PB1);
  // port PB2
  DDRB  |= _BV(PB2);
  PORTB &=~_BV(PB2);
  // port PB3
  DDRB  |= _BV(PB3);
  PORTB &=~_BV(PB3);

  static_assert( PORTS_COUNT==4, "update this code" );
}
