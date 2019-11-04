/*
    gp2y0e03.h
    GP2Y0E03 distance sensor driver

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

#ifndef GP2Y0E03_H
#define GP2Y0E03_H

#include<stdint.h>

#include "CuoraWire.h"

//Sensor address
#define DISTSEN_ADDR 0x40

//Data hold config
#define DISTSEN_REG_HOLD 0x03

#define DISTSEN_CNT_HOLD 0x00
#define DISTSEN_CNT_AUTO 0x01

//Emitting pulse width
#define DISTSEN_REG_PW 0x13

#define DISTDEN_CNT_PUL320 0x07
#define DISTDEN_CNT_PUL240 0x06
#define DISTDEN_CNT_PUL160 0x05
#define DISTDEN_CNT_PUL80 0x04
#define DISTDEN_CNT_PUL40 0x03

//Sensor range
#define DISTSEN_REG_SB 0x35

//Distnce register
#define DISTSEN_REG_DISTH 0x5E
#define DISTSEN_REG_DISTL 0x5F

//Sensor active/standby control
#define DISTSEN_REG_STBY 0xE8

#define DISTSEN_CNT_ACT 0x00
#define DISTSEN_CNT_STBY 0x01

//Sensor reset
#define DISTSEN_REG_RST 0xEE

#define DISTSEN_CNT_RST 0x06

/*
    Macro:distsensor_config(reg,val)
        Read from the sensor's register
    Arguments:
        reg:Register address
        val:Value
    Value:
        See distsensor_write_reg() function
*/
#define distsen_config(reg,val) distsen_write_reg(reg,val)

/*
    Macro:distsensor_reset()
        Reset the sensor
    Arguments:
        None
    Value:
        See distsensor_write_reg() function
*/
#define distsen_reset() distsen_write_reg(DISTSEN_REG_RST,DISTSEN_CNT_RST)

/*
    Function:uint8_t distsensor_read_reg(uint8_t reg,uint8_t *data)
        Read from the sensor's register
    Arguments:
        uint8_t reg:Register address
        uint8_t *data:data
    Return:
        0 if success        
*/
uint8_t distsen_read_reg(uint8_t reg,uint8_t *data);

/*
    Function:uint8_t distsensor_write_reg(uint8_t reg,uint8_t data)
        Write to the sensor's register
    Arguments:
        uint8_t reg:Register address
        uint8_t *data:data
    Return:
        0 if success      
*/
uint8_t distsen_write_reg(uint8_t reg,uint8_t data);

/*
    Function:uint8_t distsensor_read_mulreg(uint8_t reg,uint8_t *data)
        Burst read the sensor's register
    Arguments:
        uint8_t reg:Register address
        uint8_t *data:data
    Return:
        0 if success      
*/
uint8_t distsen_read_mulreg(uint8_t reg,uint8_t *data,uint8_t count);

/*
    Function:uint8_t distsensor_read_dist(void)
        Read distance
    Arguments:
        uint16_t *data:Distance data
    Return:
        0 if success
*/
uint8_t distsensor_read_dist(uint16_t *data);

#endif  //GP2Y0E03_H
