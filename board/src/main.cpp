/*
 * main.cpp
 *
 */
#include "config.hpp"       // this file must be included as first one!

#include "USART.hpp"
#include "Processor.hpp"
#include "Relays.hpp"
#include "uassert.hpp"


//
// MAIN
//
int main(void)
{
  Relays relays;                    // initialize relay controll interface
  USART::init();                    // configure serial interface

  uint8_t   f=0;                    // poistion to write in buffer
  char      cmd[IO_BUFFER_SIZE];    // command buffer
  bool      applied=false;          // checks if last command was applied
  cmd[0]=0;                         // buffor is empty by default
  Processor proc;                   // initialize processor

  // main loop
  for(;;)
  {
    // read char from port
//USART::send('A');
continue;
    const char c=USART::receive();
USART::send(c);

    // process it
    if(c=='\n' || c=='\r')
    {
USART::send("new line");
      // if command was alrady applied, just skip next new lines
      if(applied)
        continue;
      // end of line means processing is applied
      proc.process(cmd);
      applied=true;
    }
    else
    {
      // if no processing, add char to the buffer, or reset it's content if full

      // just in case
      if( f+1u>=sizeof(cmd) )
        f=0;
      // add char
      cmd[f]  =c;
      cmd[f+1]=0;
      ++f;
      applied=false;
    }
  }

  // this code is never reached...
  for(;;)
    USART::send("oops...");
  return 0;
} // main()

