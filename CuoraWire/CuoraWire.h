/*
    CuoraWire.h
    CuoraWire - TWI library for AVR microcontrollers with TWI function.(master operations only)

    BSD 2-Clause License

    Copyright (c) 2019, PFMRLIB
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CUORAWIRE_H
#define CUORAWIRE_H

#include<stdint.h>

#include<avr/io.h>

//TWI Clock Speed
#define TWI_FREQ_STANDARD 100000UL
#define TWI_FREQ_FULL 400000UL
#define TWI_FREQ_FAST 1000000UL
#define TWI_FREQ_HIGH 3200000UL

//TWI DDR and PORT
#define SCL_DDR DDRD
#define SCL_PORT PORTD
#define SCL_BIT PD0

#define SDA_DDR DDRD
#define SDA_PORT PORTD
#define SDA_BIT PD1

//TWI Frequency precacler
#define TWI_FREQ_PREC 0x00

//Must define F_CPU to calculate clock frequency
#ifndef F_CPU
#error "F_CPU not defined!"
#endif

/*
    Macro:get_status_code()
        Get status code of TWI transmission
    Arguments:
        None
    Value:
        TWI transmission status code
*/
#define get_status_code() (TWSR & (~((1<<TWPS1)|(1<<TWPS0))))

/*
    Function:void twi_init(uint16_t freq)
        Initialize TWI hardware
    Arguments:
        uint16_t freq:Frequency of SCL, prescaler = 1
    Return:
        None
*/
void twi_init(uint16_t freq);

/*
    Function:uint8_t twi_start(void)
        send START signal and return status
    Arguments:
        None
    Return:
        0 - START signal has sent successfully
        1 - Repeat START has sent successfully
        2 - Error
*/
uint8_t twi_start(void);

/*
    Function:void twi_end(void)
        Send STOP signal
    Arguments:
        None
    Return:
        None
*/
void twi_end(void);

/*
    Function:uint8_t twi_SLA(uint8_t sla,_Bool rw)
        Send slave address and r/w
    Arguments:
        uint8_t addr:Address of slave device
        _Bool rw:read(true) or write(false)
    Return:
        0 - ACK received
        1 - NACK received
        2 - Error
*/
uint8_t twi_SLA(uint8_t sla,_Bool rw);

/*
    Function:uint8_t twi_read_byte(uint8_t *data,_Bool ack)
        Read a byte
    Arguments:
        uint8_t *data:Pointer to write data
        _Bool ack:ACK(true)/NACK(false) after reading
    Return:
        Always 0
*/
uint8_t twi_read_byte(uint8_t *data,_Bool ack);

/*
    Function:uint8_t twi_write_byte(uint8_t data)
        Write a byte
    Arguments:
        uint8_t data:Data to be sent
    Return:
        0 - ACK received
        1 - NACK received
        2 - Error
*/
uint8_t twi_write_byte(uint8_t data);

#endif  //CUORAWIRE_H