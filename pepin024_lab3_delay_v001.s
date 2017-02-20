


.equ __P24FJ64GA002,1 ;required "boiler-plate" (BP)
.include "p24Fxxxx.inc" ;BP
#include "xc.inc" ;BP

.text ;BP (put the following data in ROM(program memory))
   
.global  _mSec
    
    
_mSec:
    REPEAT #15993
    NOP
    RETURN
    
    .end