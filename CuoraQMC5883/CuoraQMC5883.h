/*
    Cuora_QMC5883.h
    QMC5883 3-Axis magnetic sensor library

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

#ifndef Cuora_QMC8883_H
#define Cuora_QMC5883_H

#include<stdint.h>

//Address of the sensor
#define QMC5883_ADDR 0x0D

//Register address
#define QMC5883_READSTART 0x00
#define QMC5883_XOUT 0x00
#define QMC5883_YOUT 0x02
#define QMC5883_ZOUT 0x04
#define QMC5883_STATOUT 0x06
#define QMC5883_TOUT 0x07
#define QMC5883_CR1 0x09
#define QMC5883_CR2 0x0A
#define QMC5883_FBR 0x0B

//Control constants
#define QMC5883_MODE_STBY 0x00
#define QMC5883_MODE_CONT 0x01

//Output data rate
#define QMC5883_ODR_10 0x00
#define QMC5883_ODR_50 0x04
#define QMC5883_ODR_100 0x08
#define QMC5883_ODR_200 0x0C

//Sensor range
#define QMC5883_RNG_2 0x00
#define QMC5883_RNG_8 0x10

//Over sample ratio
#define QMC5883_OSR_512 0x00
#define QMC5883_OSR_256 0x40
#define QMC5883_OSR_128 0x80
#define QMC5883_OSR_64 0xC0

#define QMC5883_SET_PERIOD 0x01
#define QMC5883_SOFT_RESET 0x80
#define QMC5883_DRDY_MASK 0x07

//Status code
#define QMC5883_DOR 0x04
#define QMC5883_OVL 0x02
#define QMC5883_DRDY 0x01

//Radius to degree
#define RAD2DEG 57.2958

/*
    Macro:qmc5883_config(mode,scale,osr,odr)
        Get status code of TWI transmission
    Arguments:
        mode:Mode of operation(Continuous or Standby)
        odr:Output data rate
        scale:Sensor range
        osr:Over sample ratio
    Value:
        See qmc5883_write() function for detailed information.
*/
#define qmc5883_config(mode,scale,osr,odr) qmc5883_write(QMC5883_CR1,mode|odr|scale|osr)

/*
    Macro:qmc5883_reset()
        Reset the sensor
    Arguments:
        None
    Value:
        See qmc5883_write() function for detailed information.
*/
#define qmc5883_reset() qmc5883_write(QMC5883_CR2,QMC5883_SOFT_RESET)

/*
    Function:qmc5883_init(uint8_t mode,uint8_t scale,uint8_t osr,uint8_t odr)
        Initialize the sensor
    Arguments:
        uint8_t mode:Mode of operation(Continuous or Standby)
        uint8_t odr:Output data rate
        uint8_t scale:Sensor range
        uint8_t osr:Over sample ratio
    Return:
        None
*/
void qmc5883_init(uint8_t mode,uint8_t scale,uint8_t osr,uint8_t odr);

/*
    Function:qmc5883_read_all(int16_t *x,int16_t *y,int16_t *z)
        Read raw data from the sensor
    Arguments:
        int16_t *x:Magnetic data of X axis
        int16_t *y:Magnetic data of Y axis
        int16_t *z:Magnetic data of Z axis
    Return:
        Status code(DOR,OVL,DRDY or their combination)
*/
uint8_t qmc5883_read_all(int16_t *x,int16_t *y,int16_t *z);

/*
    Function:uint8_t qmc5883_write(uint8_t reg,uint8_t val)
        Write to a register
    Arguments:
        uint8_t reg:Register address
        uint8_t val:Value
    Return:
        Always 0
*/
uint8_t qmc5883_write(uint8_t reg,uint8_t val);

/*
    Function:float qmc5883_get_azumith(const int *x,const int *y)
        Get azumith from x and y data
    Arguments:
        const int *x:X axis magnetic data
        const int *y:Y axis magnetic data
    Return:
        Azimuth
*/
float qmc5883_get_azimuth(const int *x,const int *y);

#endif  //Cuora_QMC8883_H