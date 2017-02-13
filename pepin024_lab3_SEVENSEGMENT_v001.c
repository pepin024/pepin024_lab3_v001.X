#include <p24Fxxxx.h>
#include <xc.h>


void init7seg(void){
    AD1PCFG |= 0x0030;
    TRISB &= 0b1111000000000011;
    LATB |= 0b0000001111111100; //Set anodes to high
    LATB &= 0b1111001111111111; //Set cathodes to low
    return;
}
