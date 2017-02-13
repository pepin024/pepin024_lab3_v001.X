#include <p24Fxxxx.h>
#include <xc.h>
#include "pepin024_lab3_delay_v001.h"

void initKeyPad(void){
    AD1PCFG |= 0x1E03;  //Set pins to digital
    CNPU1 |= 0x7800; //Activates pullup resistors for columns
    TRISB |= 0xF000; //Set RB <15:13> as inputs
    TRISA &= 0xFFF0; //Set RA <3:0> as outputs
    LATA |= 0x000F; //Pull all Rows High
    
    return;
    
}

//Return 4 bit number RRCC
int readKeyPadRAW(void){
    int state;
    int row;
    LATBbits.LATB15 = 0;
    if(PORTB > 0){
        delay(2);
        state = (PORTB & 0b1111);
        row = 0;
    }
    LATBbits.LATB15 = 1;
    LATBbits.LATB14 = 0;
    if(PORTB > 0){
        delay(2);
        state = (PORTB & 0b1111);
        row = 1;
    }
    LATBbits.LATB14 = 1;
    LATBbits.LATB13 = 0;
    if(PORTB > 0){
        delay(2);
        state = (PORTB & 0b1111);
        row = 2;
    }
    LATBbits.LATB13 = 1;
    LATBbits.LATB12 = 0;
    if(PORTB > 0){
        delay(2);
        state = (PORTB & 0b1111);
        row = 3;
    }
    LATBbits.LATB12 = 1;
    
    if(state == 0)
        return 0;
    
    //Pack state of column into 2 bit number
    int i;
    for(i = 0; (state >> i) != 1; ++i){  
    }
    return (row << 2) + i;
}