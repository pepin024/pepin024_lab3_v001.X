#include <p24Fxxxx.h>
#include <xc.h>
#include "pepin024_lab3_SEVENSEGMENT_v001.h"
#include "pepin024_lab3_delay_v002.h"
#include "pepin024_lab3_KEYPAD_v003.h"

// PIC24FJ64GA002 Configuration Bit Settings
// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config POSCMOD = NONE
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

void loop(void);


char lastkey = 0;
char keyPadMask[] = {'1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C', '#', '0', '*', 'D', 0};

void setup(void) {
    CLKDIVbits.RCDIV = 0;
    
    init7seg();
    initKeyPad();
    
    return;
}

int main(void){
    
    setup();
    
    showChar7seg('0', 0);
    
    while(1)
       loop();
    return 1;
}

void loop(void){
    int i=0;
    int keyPress;
    keyPress = scanKeyPad();
    if(keyPress > 15)
        keyPress = 16;
    showChar7seg(keyPadMask[keyPress], 0);
  
    return;
}
