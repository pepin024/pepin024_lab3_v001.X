/* 
 * File:   pepin024_lab3_KEYPAD_v003.h
 * Author: pepin024
 *
 * Created on February 23, 2017, 1:44 PM
 */

#ifndef PEPIN024_LAB3_KEYPAD_V003_H
#define	PEPIN024_LAB3_KEYPAD_V003_H

#ifdef	__cplusplus
extern "C" {
#endif

    void initKeyPad(void);
    void readKeyPadRAW(void);
    int scanRow(int);



#ifdef	__cplusplus
}
#endif

#endif	/* PEPIN024_LAB3_KEYPAD_V003_H */

