/*
 * main.cpp
 *
 */
#include "config.hpp"       // this file must be included as first one!

#include "USART.hpp"
#include "Processor.hpp"


//
// MAIN
//
int main(void)
{
  Processor proc;                   // initialize processor
  USART::init();                    // configure serial interface

  uint8_t   f=0;                    // poistion to write in buffer
  char      cmd[IO_BUFFER_SIZE];    // command buffer
  bool      applied=false;          // checks if last command was applied
  cmd[0]=0;                         // buffor is empty by default

USART::send("init done\n");

  // main loop
  for(;;)
  {
    // read char from port
    const char c=USART::receive();
USART::send(c);

    // process it
    if(c=='\n' || c=='\r')
    {
//USART::send("PROCESSING: ");
//USART::send(cmd);
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
  for(;;)
    USART::send("oops...");
  return 0;
} // main()

