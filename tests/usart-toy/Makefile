#MCU=atmega8
MCU=attiny2313
CC=avr-gcc
OBJCOPY=avr-objcopy
# optimize for size:
CFLAGS= -mmcu=$(MCU) -Wall -Wstrict-prototypes -Os -mcall-prologues
#-------------------
all: usart.hex usart.bin
#-------------------
usart.hex : usart.out
	$(OBJCOPY) -R .eeprom -O ihex usart.out usart.hex
usart.out : usart.o
	$(CC) $(CFLAGS) -o usart.out -Wl,-Map,usart.map usart.o
usart.bin : usart.out
	$(OBJCOPY) -O binary $< $@
usart.o : usart.c
	$(CC) $(CFLAGS) -Os -c usart.c
# you need to erase first before loading the program.
# load (program) the software into the eeprom:
#load: usart.hex
#	uisp -dlpt=/dev/parport0 --erase  -dprog=dapa
#	uisp -dlpt=/dev/parport0 --upload if=usart.hex -dprog=dapa  -v=3 --hash=32

flash_mcu:
	avrdude -P avrdoper -c stk500v2 -p t2313 -U flash:w:usart.bin
	#avrdude -P avrdoper -c stk500v2 -p t2313 -U lfuse:w:0xe4:m -U hfuse:w:0xdf:m
	avrdude -P avrdoper -c stk500v2 -p t2313 -U lfuse:w:0xe0:m -U hfuse:w:0xdf:m

setup_ft232:
	ft232r_prog --cbus2 Clk6 --manufacturer "BaSz" --product "usb power controller" --max-bus-power 500

#-------------------
clean:
	rm -fv *.o *.map *.out *.hex *.bin
#-------------------
