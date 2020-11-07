/* ========================================
 * Assignment #1, Luca Andriotto
 * ========================================
*/

#ifndef __INTERRUPT_H
    #define __INTERRUPT_H
    #include "cytypes.h"
    #include "define.h"
    
    uint8 outputDataRate;                           // keeps track of ODR changes
    volatile uint8_t writeMemory;                   // keeps track of button states
    
    CY_ISR_PROTO(SW_ISR);
    
#endif

