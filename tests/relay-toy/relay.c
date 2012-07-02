#define F_CPU (6L*1000L*1000L)                  /* oscillator-frequency in Hz */

#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>

void delay(const uint8_t ds)
{
  uint8_t i;
  for(i=0; i<ds; ++i)
    _delay_ms(100);
}


int main(void)
{
  DDRB=0xFF;
  PINB=0x00;

  while(1)
  {
    PORTB|= _BV(PB0);
    delay(10);
    PORTB&=~_BV(PB0);
    delay(20);

    PORTB|= _BV(PB1);
    delay(10);
    PORTB&=~_BV(PB1);
    delay(20);

    PORTB|= _BV(PB2);
    delay(10);
    PORTB&=~_BV(PB2);
    delay(20);

    PORTB|= _BV(PB3);
    delay(10);
    PORTB&=~_BV(PB3);
    delay(20);

    delay(2*10);
  }

  return 0;
}
