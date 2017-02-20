#include <p24Fxxxx.h>
#include <xc.h>
#include "pepin024_lab3_delay_v001.h"

void initKeyPad(void){
    AD1PCFG |= 0x1E03;  //Set pins to digital
    CNPU1 |= 0x000C; //Activates pullup resistors for columns
    CNPU2 |= 0x6000;
    TRISA |= 0x000F; //Set RA <3:0> as inputs
    TRISB &= 0x0FFF; //Set RB <15:13> as outputs
    
    LATB |= 0xF000; //Pull all Rows High
    
    return;
    
}

//Return 4 bit number RRCC
int readKeyPadRAW(void){
    int state;
    int row;
    LATBbits.LATB15 = 0;
    if((PORTA & 0b1111) != 0b1111){
        delay(2);
        state = (PORTA & 0b1111);
        row = 0;
    }
    LATBbits.LATB15 = 1;
    LATBbits.LATB14 = 0;
    if((PORTA & 0b01111) != 0b1111){
        delay(2);
        state = (PORTA & 0b1111);
        row = 1;
    }
    LATBbits.LATB14 = 1;
    LATBbits.LATB13 = 0;
    if(PORTA != 0b1111){
        delay(2);
        state = ((PORTA & 0b01111) != 0b1111);
        row = 2;
    }
    LATBbits.LATB13 = 1;
    LATBbits.LATB12 = 0;
    if((PORTA & 0b01111) != 0b1111){
        delay(2);
        state = (PORTA & 0b1111);
        row = 3;
    }
    LATBbits.LATB12 = 1;
    
    if(state == 0)
        return 0;
    
    //Pack state of column into 2 bit number
    int i;
    int j;
    j = row << 2;
    for(i = 0; i < 4; ++i){ 
        if((state & (1 << i)) == 0)
          return j + i;  
    }
    
}