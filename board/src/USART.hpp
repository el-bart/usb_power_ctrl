/*
 * USART.hpp
 *
 */
#ifndef INCLUDE_USART_HPP_FILE
#define INCLUDE_USART_HPP_FILE

#include <stdio.h>

/** \brief set of operations on serial interface.
 */
struct USART
{
  /** \brief initialize USART.
   */
  static void init(void);

  /** \brief send singe byte.
   *  \param b byte to send.
   */
  static void send(char b);
  /** \brief sends given string.
   *  \param str string to be sent.
   */
  static void send(const char *str);
  /** \brief sends given string, placed in FLASH not in RAM.
   *  \param str string present in the FLASH, to be sent.
   */
  static void sendFlash(const char *str);

  /** \brief get one byte form the usart.
   *  \return data read.
   */
  static char receive(void);
}; // struct USART

#endif
