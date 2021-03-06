/*
 * main.cpp
 *
 */
#include "config.hpp"       // this file must be included as first one!

#include "USART.hpp"
#include "Processor.hpp"
#include "Watchdog.hpp"


//
// MAIN
//
int main(void)
{
  Watchdog  wdt;                    // use watchdog (disabled by default)
  Processor proc;                   // initialize processor
  USART::init();                    // configure serial interface
  wdt.enable();                     // enable watchdog as the last step

  uint8_t   f=0;                    // poistion to write in buffer
  char      cmd[IO_BUFFER_SIZE];    // command buffer
  bool      applied=false;          // checks if last command was applied
  cmd[0]=0;                         // buffor is empty by default

  // main loop
  for(;;)
  {
    // keep reseting watchdog while there is nothing to do
    do { wdt.reset(); }
    while( !USART::hasData() );

    // read char from port
    const char c=USART::receive();

    // process it
    if(c=='\n' || c=='\r')
    {
      // if command was alrady applied, just skip next new lines
      if(applied)
        continue;
      // end of line means processing is applied
      proc.process(cmd);
      applied=true;
      // reset command buffer
      cmd[0]=0;
      f     =0;
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
  return 0;
} // main()

