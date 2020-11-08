/* ========================================
 * Assignment #05, Luca Andriotto
 * ========================================
*/

#ifndef __STATES_H
    
    #define __STATES_H
    #include "accelerometer.h"
    #include "interrupt.h"
    
    // to check status register --> sampling only if new data are available
    uint8_t zyxda;

/*****************************************************************************\
 * Function:    init
 * Description: 
 *     Initialization of all the peripherals.
\*****************************************************************************/
    
    void init();
    
/*****************************************************************************\
 * Function:    loop
 * Description: 
 *     Contains the state machine.
\*****************************************************************************/

    void stateMachine();
    
#endif
