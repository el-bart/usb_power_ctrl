#include "config.hpp"

#include <avr/io.h>
#include <avr/eeprom.h>

#include "Relays.hpp"


namespace
{
inline uint8_t* eepromStateAddress(const uint8_t n)
{
  return static_cast<uint8_t*>(0x0) + n;
}
}

Relays::Relays(void)
{
  static_assert( PORTS_COUNT==4, "update this code" );
  const uint8_t lut[PORTS_COUNT]={PB0, PB1, PB2, PB3};

  // configure each port
  for(uint8_t i=0; i<PORTS_COUNT; ++i)
  {
    state_[i] = getDefault(i);  // read default port state
    DDRB |= _BV( lut[i] );      // setup this port as output
    set( i, state_[i] );        // set state to the default value
  }
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


void Relays::setDefault(uint8_t n, bool state)
{
  // sanity check
  if(PORTS_COUNT<=n)
    return;
  // write to eeprom
  eeprom_update_byte( eepromStateAddress(n), state );
}


bool Relays::getDefault(uint8_t n) const
{
  // sanity check
  if(PORTS_COUNT<=n)
    return false;
  // read data from eeprom (converted to bool)
  return eeprom_read_byte( eepromStateAddress(n) );
}
