# CuoraWire
## Description
CuoraWire is a simple TWI library for AVR microcontrollers with TWI function. It provides user with several functions to read, write and control the TWI bus under master mode.  
## Structure
The library consists of two files:`CuoraWire.h`(Header) and `CuoraWire.c`(Source file).
## Functions,Macros and Constants
Detailed information on them are shown in the header file.
## Usage
1.Use `twi_init()` to intiialize TWI hardware.
2.Use `twi_start()` to send a START signal, which starts a transmission.  
3.Use `twi_SLA()` to write slave address and R/W control bit to the bus.  
4.Use `twi_read_byte()` or `twi_write_byte()` to read or write on the bus.
5.Use `twi_end()` to send a STOP signal, which stop the process.
## Notes
1.The library uses polling instead of interrupts.  
2.The library uses TWI function. So some microcontrollers without TWI function(e.g.ATtiny85) are NOT supported. Obviously, these microcontrollers with USI function(Could be configured as TWI) but lack of a TWI function are ALSO UNAVAILABLE for the library.  
3.When using the library on Arduino or other C++ compliers, use an `extern "C"` block to wrap `#include` codes.  