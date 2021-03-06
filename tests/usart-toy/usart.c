#define F_CPU (6L*1000L*1000L)                  /* oscillator-frequency in Hz */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay.h>

#define UART_BAUD_RATE 9600
//#define UART_BAUD_RATE 38400
#define UART_BAUD_CALC(UART_BAUD_RATE,F_CPU) ((F_CPU)/((UART_BAUD_RATE)*16l)-1)

void delay(const uint8_t ds) {
  uint8_t i;
  for(i=0; i<ds; ++i)
    _delay_ms(100);
}

void usart_putc(unsigned char c) {
  // wait until UDR ready
  while(!(UCSRA & (1 << UDRE)));
  UDR = c;    // send character
}

void uart_puts (char *s) {
  //  loop until *s != NULL
  while (*s) {
    usart_putc(*s);
    s++;
  }
}

void init(void) {
  // TX:
  DDRD  |=  _BV(PD1);
  // RX:
  DDRD  &= ~_BV(PD0);
  PORTD |=  _BV(PD0);

  // set baud rate
  UBRRH = (uint8_t)(UART_BAUD_CALC(UART_BAUD_RATE,F_CPU)>>8);
  UBRRL = (uint8_t)UART_BAUD_CALC(UART_BAUD_RATE,F_CPU);

  // Enable receiver and transmitter; enable RX interrupt
  UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);

  //asynchronous 8N1
  //UCSRC = /*(1 << UMSEL) |*/ (1 << UCSZ1) | (1 << UCSZ0);
}

// INTERRUPT can be interrupted
// SIGNAL can't be interrupted
ISR (USART_RX_vect ) { // USART RX interrupt
  unsigned char c;
  c = UDR;
  usart_putc(c);
}

int main(void) {
  init(); // init USART
  sei();  // enable interrupts

  while(1)
  {
    char c;
    for(c='a'; c<='z'; ++c)
      usart_putc(c);
    usart_putc('\n');
    delay(1);
  }

  return 0;
}
