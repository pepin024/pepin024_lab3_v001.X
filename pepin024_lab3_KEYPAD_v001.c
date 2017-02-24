#include <p24Fxxxx.h>
#include <xc.h>
#include "pepin024_lab3_delay_v002.h"

#define NOKEY 255

int rowMask[] = {0b0111, 0b1011, 0b1101, 0b1110};
int colMask[] = {NOKEY,NOKEY,NOKEY,NOKEY,NOKEY,NOKEY,NOKEY,3,
        NOKEY,NOKEY,NOKEY,2,NOKEY,1,0,NOKEY};

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
    return 0;
}

int scanRow(int row){
    if((row > 3) || (row < 0))
        row = 0;
    LATB |= 0xF000;
    LATB &= 0x0FFF + (rowMask[row] << 12);
    int key = PORTA & 0x000F;
    key = colMask[key];
    if(key == NOKEY)
        return NOKEY;
    return (4*row) + key;
    
}

int scanKeyPad(void){
    int row = 0;
    int key = NOKEY;
    for(row = 0; row < 4; row++){
        int tempKey = scanRow(row);
        if(tempKey != NOKEY)
            key = tempKey;
    }
    return key;
}