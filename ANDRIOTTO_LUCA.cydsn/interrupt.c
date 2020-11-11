/* ========================================
 * Assignment #05, Luca Andriotto
 * ========================================
*/

#include "interrupt.h"

CY_ISR_PROTO(SW_ISR)
{
    // updating ODR.
    outputDataRate = ((outputDataRate + 1) % EEPROM_TOTAL_ODRS); // --> cycle starting from 0.
    // setting flag to 1.
    onButtonPressed = 1;
}

CY_ISR_PROTO(TIMER_CHECK_STATUS_ISR)
{
	// Clearing the interrupt on TC.
    Timer_Check_Status_ReadStatusRegister();
	// Setting the timeout flag.
    onTimeout = 1;
}