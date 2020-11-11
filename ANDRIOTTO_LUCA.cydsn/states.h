/* ========================================
 * Assignment #05, Luca Andriotto
 * ========================================
*/

#ifndef __STATES_H
    
    #define __STATES_H
    #include "accelerometer.h"
    #include "interrupt.h"
    
    

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
