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

  // by deafult all ports are off, for now
  for(uint8_t i=0; i<PORTS_COUNT; ++i)
    state_[i]=false;
}


void Relays::set(uint8_t n, bool state)
{
  // sanity check
  if(PORTS_COUNT<=n)
    return;
  // save change
  state_[n]=state;
  // set state on port
  const uint8_t lut[PORTS_COUNT]={PB0, PB1, PB2, PB3};
  if(state)
    PORTB |=  _BV(lut[n]);
  else
    PORTB &= ~_BV(lut[n]);
}


bool Relays::get(uint8_t n) const
{
  if(PORTS_COUNT<=n)
    return false;
  return state_[n];
}
