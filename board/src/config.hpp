/*
 * config.hpp
 *
 */
#ifndef INCLUDE_CONFIG_HPP_FILE
#define INCLUDE_CONFIG_HPP_FILE

// units commonly used
#define KHz   1000L
#define MHz   (1000L*KHz)

// quarc frequency in [Hz]
#define F_CPU (6L*MHz)

// USART speed (bps)
#define USART_BAUD (9600L)

// max queue size
#define IO_BUFFER_SIZE 16

// version
#define VERSION_MAIN  1
#define VERSION_MAJOR 0
#define VERSION_MINOR 0

// number of ports to controll
#define PORTS_COUNT 4

#endif
