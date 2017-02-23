#include <p24Fxxxx.h>
#include <xc.h>

void mSec(void){
    T1CON = 0x8001;
    TMR1 = 0;
    PR1 = 15999;
    _T1IF = 0;
    while(_T1IF == 0);
    return;
}

void delay(unsigned int i){
    while(i--)
        mSec();
    return;
}