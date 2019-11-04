/*
    gp2y0e03.c
    GP2Y0E03 distance sensor driver
    
    by PFMRLIB
    This code is licensed under BSD 2-clause license. For further information, please read the header file.
*/

#include "gp2y0e03.h"

#include<stdbool.h>

uint8_t distsen_read_reg(uint8_t reg,uint8_t *data){
    uint8_t errc = 0;

    //Write register
    twi_start();
    if(errc = twi_SLA(DISTSEN_ADDR,false))
        goto err;
    twi_write_byte(reg);
    twi_end();
    
    //Read data
    twi_start();
    if(errc = twi_SLA(DISTSEN_ADDR,true))
        goto err;
    //Read and NACK
    if(twi_read_byte(data,false))
        goto err;
    twi_end();

    goto noerr;

err:
    *data = 0x00;
noerr:
    return errc;
}

uint8_t distsen_write_reg(uint8_t reg,uint8_t data){
    uint8_t errc = 0;

    //Write register and data
    twi_start();
    if(errc = twi_SLA(DISTSEN_ADDR,false))
        goto err;
    twi_write_byte(reg);
    if(twi_write_byte(data))
        goto err;

err:
    twi_end();

    return errc;
}

uint8_t distsen_read_mulreg(uint8_t reg,uint8_t *data,uint8_t count){
    uint8_t errc = 0;
    uint8_t i;
    //Write register
    twi_start();
    if(errc = twi_SLA(DISTSEN_ADDR,false))
        goto err;
    twi_write_byte(reg);
    twi_end();
    
    //Read data
    twi_start();
    if(errc = twi_SLA(DISTSEN_ADDR,true))
        goto err;
    //Read and NACK
    for(i = 0;i < count - 1;i++){
        if(twi_read_byte(&data[i],true))
            goto err;
    }
    if(twi_read_byte(&data[i],false))
        goto err;
    
    twi_end();

err:
    twi_end();

    return errc;
}

uint8_t distsensor_read_dist(uint16_t *data){
    uint8_t val[2];
    uint8_t errc = 0;
    
    if(errc = distsen_read_mulreg(DISTSEN_REG_DISTH,val,2))
        return errc;

    *data = ((val[0]<<4) + (val[1] & 0x0F)) / 64;

    return 0;
}
