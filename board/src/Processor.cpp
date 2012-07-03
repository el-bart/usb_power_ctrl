#include "config.hpp"
#include "Processor.hpp"
#include "USART.hpp"

namespace
{
bool strEq(const char* s1, const char* s2)
{
  // both nulls or are the same string address?
  if(s1==s2)
    return true;
  // check each char...
  while(true)
  {
    // non-equal characters?
    if(*s1!=*s2)
      return false;
    // one of the strings is shorter?
    if(*s1==0 || *s2==0)
      return false;
    // move on to the next character
    ++s1;
    ++s2;
  }
  // no differences found - strings are equal then!
  return true;
} // strEq()
} // unnamed namespace



void Processor::process(char *buf)
{
  // tokenize input
  Tokenizer tokenizer(buf);

  // sanity check
  const char *cmd=tokenizer.getNextToken();
  if(cmd==NULL)
  {
    error("no command specified");
    return;
  }

  if( strEq(cmd, "hello") )
  {
    handleHello(tokenizer);
    return;
  }

  if( strEq(cmd, "port") )
  {
    handlePort(tokenizer);
    return;
  }

  if( strEq(cmd, "default") )
  {
    handleDefault(tokenizer);
    return;
  }

  if( strEq(cmd, "status") )
  {
    handleStatus(tokenizer);
    return;
  }

  error("unknown command specified");
}


void Processor::error(const char *msg) const
{
  USART::send("ERROR: ");
  if(msg!=nullptr)
    USART::send(msg);
}


void Processor::handleHello(Tokenizer& tokenizer) const
{
  if( tokenizer.getNextToken()!=nullptr )
  {
    error("too many arguments to hello command");
    return;
  }
  // send the response
  USART::send("USB power controller v");
  USART::send('0'+VERSION_MAIN);
  USART::send('.');
  USART::send('0'+VERSION_MAJOR);
  USART::send('.');
  USART::send('0'+VERSION_MINOR);
  USART::send('\n');
}


void Processor::handlePort(Tokenizer& tokenizer) const
{
}


void Processor::handleDefault(Tokenizer& tokenizer) const
{
}


void Processor::handleStatus(Tokenizer& tokenizer) const
{
}
