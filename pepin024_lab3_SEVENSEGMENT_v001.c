#include <p24Fxxxx.h>
#include <xc.h>



char fontTable[] = {
    0b00000011,
    0b10011111,
    0b00100101,
    0b00001101,
    0b10011001,
    0b01001001,
    0b01000000,
    0b00011111,
    0b00000001,
    0b00011000,
    0b00010001,
    0b11000001,
    0b01100011,
    0b10000101,
    0b01100001,
    0b01110001,
    0b11111110,
    0b00000000
};

void init7seg(void){
    AD1PCFG |= 0x0030;
    TRISB &= 0b1111000000000011;
    LATB |= 0b0000001111111100; //Set anodes to high
    LATB &= 0b1111001111111111; //Set cathodes to low
    return;
}

void showChar7seg(char myChar, int digit){
    LATB |= 0b0000001111111100; //Set anodes to high
    LATB &= 0b1111001111111111; //Set cathodes to low
    
    if((myChar >= '0') && (myChar <= '9')){
        LATB &= ((fontTable[myChar - '0'] << 2) + 0xF003);
    }
    else if((myChar >= 'a') && (myChar <= 'f')){
        LATB &= ((fontTable[myChar - 'a' + 10] << 2) + 0xF003);
    }
    else if((myChar >= 'A') && (myChar <= 'F')){
        LATB &= ((fontTable[myChar - 'A' + 10] << 2) + 0xF003);
    }
    else if(myChar == '*'){
        LATB &= ((fontTable[16] << 2) + 0xF003);
    }
    else if(myChar == '#'){
        LATB &= ((fontTable[17] << 2) + 0xF003);
    }
    else
        return;
    
    if(digit == 0)
        LATBbits.LATB11 = 1;
    else if(digit == 1)
        LATBbits.LATB10 = 1;
    
    return;
}