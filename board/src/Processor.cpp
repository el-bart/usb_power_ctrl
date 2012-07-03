#include "config.hpp"

#include <avr/pgmspace.h>

#include "Processor.hpp"
#include "USART.hpp"


namespace
{
// s1 - string in RAM, s2 - string in FLASH
bool strEqRF(const char* s1, const char* s2)
{
  // both nulls?
  if(s1==nullptr && s2==nullptr)
    return true;

  // check each char...
  while(true)
  {
    const char c2=pgm_read_byte(s2);
    // end of string?
    if(*s1==0 && c2==0)
      return true;
    // non-equal characters?
    if(*s1!=c2)
      return false;
    // one of the strings is shorter?
    if(*s1==0 || c2==0)
      return false;
    // move on to the next character
    ++s1;
    ++s2;
  }
} // strEq()


void sendOnOff(bool flag)
{
  USART::sendFlash( flag?PSTR("on"):PSTR("off") );
}
} // unnamed namespace



void Processor::process(char *buf)
{
  // tokenize input
  Tokenizer tokenizer(buf);

  // sanity check
  const char *cmd=tokenizer.getNextToken();
  if(cmd==NULL)
  {
    errorFlash( PSTR("no cmd") );
    return;
  }

  if( strEqRF(cmd, PSTR("hello")) )
  {
    handleHello(tokenizer);
    return;
  }

  if( strEqRF(cmd, PSTR("port")) )
  {
    handlePort(tokenizer);
    return;
  }

  if( strEqRF(cmd, PSTR("default")) )
  {
    handleDefault(tokenizer);
    return;
  }

  if( strEqRF(cmd, PSTR("status")) )
  {
    handleStatus(tokenizer);
    return;
  }

  errorFlash( PSTR("unknown cmd") );
}


void Processor::errorFlash(const char *str)
{
  USART::sendFlash( PSTR("ERROR: ") );
  if(str!=nullptr)
    USART::sendFlash(str);
  USART::send('\n');
}


void Processor::handleHello(Tokenizer& tokenizer)
{
  if( tokenizer.getNextToken()!=nullptr )
  {
    errorFlash( PSTR("too many args") );
    return;
  }
  // send the response
  USART::sendFlash( PSTR("USB power controller v") );
  USART::send('0'+VERSION_MAIN);
  USART::send('.');
  USART::send('0'+VERSION_MAJOR);
  USART::send('.');
  USART::send('0'+VERSION_MINOR);
  USART::send('\n');
}


void Processor::handlePort(Tokenizer& tokenizer)
{
  handleStateChangeImpl(tokenizer, PSTR("port "), &Relays::set);
}


void Processor::handleDefault(Tokenizer& tokenizer)
{
  handleStateChangeImpl(tokenizer, PSTR("default "), &Relays::setDefault);
}


void Processor::handleStatus(Tokenizer& tokenizer)
{
  const char *mode=tokenizer.getNextToken();
  // sanity checks
  if( tokenizer.getNextToken()!=nullptr )
  {
    errorFlash( PSTR("too many args") );
    return;
  }
  if(mode==nullptr)
  {
    errorFlash( PSTR("no mode") );
    return;
  }

  // parse requested mode
  char m;
  if( strEqRF(mode, PSTR("current")) )
    m='c';
  else
  {
    if( strEqRF(mode, PSTR("default")) )
      m='d';
    else
    {
      errorFlash( PSTR("invalid mode req") );
      return;
    }
  }

  // process
  bool states[PORTS_COUNT];
  switch(m)
  {
    case 'c':
         for(uint8_t i=0; i<PORTS_COUNT; ++i)
           states[i]=relays_.get(i);
         break;
    case 'd':
         for(uint8_t i=0; i<PORTS_COUNT; ++i)
           states[i]=relays_.getDefault(i);
         break;
    default:
         // this code is never reeached
         break;
  }

  // send reply
  for(uint8_t i=0; i<PORTS_COUNT; ++i)
  {
    if(i!=0)
      USART::send(' ');
    USART::send     ('0'+i);
    USART::sendFlash( PSTR("=") );
    sendOnOff(states[i]);
  }
  USART::send('\n');
}


void Processor::handleStateChangeImpl(Tokenizer& tokenizer, const char *flashNameStr, void (Relays::*setter)(uint8_t, bool) )
{
  // tokenization
  const char *num  =tokenizer.getNextToken();
  const char *state=tokenizer.getNextToken();
  // sanity checks
  if( tokenizer.getNextToken()!=nullptr )
  {
    errorFlash( PSTR("too many args") );
    return;
  }
  if(num==nullptr || state==nullptr)
  {
    errorFlash( PSTR("missing args") );
    return;
  }

  // get port number
  static_assert( PORTS_COUNT<10, "ports count can have just one digit" );
  if(num[0]<'0' || ('0'+PORTS_COUNT)<num[0] || num[1]!=0)
  {
    errorFlash( PSTR("invalid port") );
    return;
  }
  const uint8_t n=num[0]-'0';

  // get state
  bool flag;
  if( strEqRF(state, PSTR("on")) )
    flag=true;
  else
  {
    if( strEqRF(state, PSTR("off")) )
      flag=false;
    else
    {
      errorFlash( PSTR("invalid state req") );
      return;
    }
  }

  // set new state
  (relays_.*setter)(n, flag);

  // send reply
  USART::sendFlash(flashNameStr);
  USART::send     ('0'+n);
  USART::sendFlash( PSTR(" is ") );
  sendOnOff(flag);
  USART::send     ('\n');
}
