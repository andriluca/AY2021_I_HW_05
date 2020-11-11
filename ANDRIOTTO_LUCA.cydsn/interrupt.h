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
    
    uint8_t zyxda;                                  // keeps track of the zyxda bit of
                                                    // status register
    
    uint8_t outputDataRate;                         // keeps track of ODR changes
    volatile uint8_t onButtonPressed;               // keeps track of button states
    volatile uint8_t onTimeout;						// keeps track of the timer timeout.
        
/*****************************************************************************\
 * Function:    timeoutInit
 * Returns:     uint16_t
 * Description: 
 *     returns the proper timeout for the specific ODR.
\*****************************************************************************/
    
    void timeoutInit(uint8_t odr);              

    CY_ISR_PROTO(SW_ISR);
    CY_ISR_PROTO(TIMER_CHECK_STATUS_ISR);
    
#endif

    
