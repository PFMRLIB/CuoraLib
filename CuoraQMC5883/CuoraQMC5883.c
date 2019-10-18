/*
    QMC5883 Library

    by PFMRLIB
    This code is licensed under BSD 3-clause "Revised" license. For further information, please read the header file.
*/
#include<math.h>
#include<stdbool.h>

#include "Cuora_QMC5883.h"
#include "CuoraWire.h"

void qmc5883_init(uint8_t mode,uint8_t scale,uint8_t osr,uint8_t odr){
    twi_init(TWI_FREQ_STANDARD);

    qmc5883_write(QMC5883_FBR,QMC5883_SET_PERIOD);
    qmc5883_config(mode,scale,osr,odr);
}

uint8_t qmc5883_read_all(int16_t *x,int16_t *y,int16_t *z){
    uint8_t errc;
    uint8_t val[7];

    //Send register address
    twi_start();
    twi_SLA(QMC5883_ADDR,false);
    twi_write_byte(QMC5883_READSTART);
    twi_end();

    //Receive
    twi_start();
    twi_SLA(QMC5883_ADDR,true);
    for(uint8_t i = 0;i < 6;i++)
        twi_read_byte(&val[i],true);
    //Receive the final byte and end
    twi_read_byte(&val[7],false);
    twi_end();

    *x = (int16_t)(val[0]|(val[1]<<8));
    *y = (int16_t)(val[2]|(val[3]<<8));
    *z = (int16_t)(val[4]|(val[5]<<8));
    errc = val[6] & QMC5883_DRDY_MASK;

    return errc;
}

uint8_t qmc5883_write(uint8_t reg,uint8_t val){
    twi_start();
    twi_SLA(QMC5883_ADDR,false);
    twi_write_byte(reg);
    twi_write_byte(val);
    twi_end();

    return 0;
}

float qmc5883_get_azimuth(const int *x,const int *y){
    float azimuth;

    azimuth = atan2(*y,*x) * RAD2DEG;

    return azimuth < 0 ? azimuth + 360 : azimuth;
}
