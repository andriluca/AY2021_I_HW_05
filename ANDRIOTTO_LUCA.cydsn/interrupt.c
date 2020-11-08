/* ========================================
 * Assignment #05, Luca Andriotto
 * ========================================
*/

#include "interrupt.h"
#include "define.h"

CY_ISR_PROTO(SW_ISR)
{
    // updating ODR
    outputDataRate = ((outputDataRate + 1) % 6);
    // setting flag to 1
    writeMemory = 1;
}

