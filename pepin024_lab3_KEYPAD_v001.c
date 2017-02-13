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
