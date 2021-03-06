/* ========================================
 * Assignment #05, Luca Andriotto
 * ========================================
*/

#ifndef __INTERRUPT_H

    #define __INTERRUPT_H
    
    #include "cytypes.h"
    #include "define.h"
    #include "Timer.h"
    #include "i2c.h"
    
    uint8_t outputDataRate;                         // keeps track of ODR changes.
    volatile uint8_t onButtonPressed;               // keeps track of button states.
    uint8_t zyxda;                                  // keeps track of the zyxda bit of status register.
    
    CY_ISR_PROTO(SW_ISR);
    
#endif
