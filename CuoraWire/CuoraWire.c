/*
    CuoraWire.c
    CuoraWire - TWI library for AVR microcontrollers with TWI function
    
    by PFMRLIB
    This code is licensed under BSD 3-clause "Revised" license. For further information, please read the header file.
*/
#include<util/twi.h>

#include "CuoraWire.h"

void twi_init(uint16_t fclk){
    //Set pullup for TWI pins
    MCUCR &= ~(1<<PUD);
    SCL_DDR &= ~(1<<SCL_BIT);
    SDA_DDR &= ~(1<<SDA_BIT);

    SCL_PORT |= (1<<SCL_BIT);
    SDA_PORT |= (1<<SDA_BIT);
    //Set TWI
    TWSR = (TWI_FREQ_PREC<<TWPS0);
    TWBR = ((F_CPU / fclk) - 16) / 2;
    //Enable TWI
    TWCR = (1<<TWEN);
}

uint8_t twi_start(void){
    //Send START
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    //Wait for response
    while((TWCR & (1<<TWINT)) == 0);
    //Check status
    uint8_t statcode = get_status_code();
    if(statcode == TW_START){
        return 0;
    }else if(statcode == TW_REP_START){
        return 1;
    }else{
        return 2;
    }
}

void twi_end(void){
    //Send STOP
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

uint8_t twi_SLA(uint8_t sla,_Bool rw){
    //Send address and R/W
    if(rw){
        TWDR = (sla<<1)|0x01;
    }else{
        TWDR = (sla<<1)|0x00;
    }
    //Send
    TWCR = (1<<TWINT)|(1<<TWEN);
    //Wait for response
    while((TWCR & (1<<TWINT)) == 0);
    //Check status
    uint8_t statcode = get_status_code();
    if((statcode == TW_MT_SLA_ACK) || (statcode == TW_MR_SLA_ACK)){
        return 0;
    }else if((statcode == TW_MT_SLA_NACK) || (statcode == TW_MR_SLA_NACK)){
        return 1;
    }else{
        return 2;
    }
}

uint8_t twi_read_byte(uint8_t *data,_Bool ack){
    //Start reading
    if(ack){
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    }else{
        TWCR = (1<<TWINT)|(1<<TWEN);
    }
    //Wait for response
    while((TWCR & (1<<TWINT)) == 0);
    //Get data
    *data = TWDR;

    return 0;
}

uint8_t twi_write_byte(uint8_t data){
    //Load data to TWDR
    TWDR = data;
    //Send
    TWCR = (1<<TWINT)|(1<<TWEN);
    //Wait for response
    while((TWCR & (1<<TWINT)) == 0);
    //Check status
    uint8_t statcode = get_status_code();
    if(statcode == TW_MT_DATA_ACK){
        return 0;
    }else if(statcode == TW_MT_DATA_NACK){
        return 1;
    }else{
        return 2;
    }
}
