/*
 * main.cpp
 *
 */
#include "config.hpp"       // this file must be included as first one!

#include <avr/io.h>
#include <util/delay.h>     // <avr/delay.h> once

#include "USART.hpp"
#include "uassert.hpp"


//
// MAIN
//
int main(void)
{
  USART::init();                                    // configure serial interface
  USART::send("up and running...\n");

  // one big TODO !
  USART::send("awaiting commands...");

  for(;;)
  {
    const char r=USART::receive();
    USART::send("got char +1 ");
    USART::send(r+1);
    USART::send(" - and now... ");

    for(char c='a'; c<='z'; ++c)
      USART::send(c);
    USART::send('\n');
    _delay_ms(250);
  }
  for(;;);      // TODO: just for now
  return 0;
} // main()

