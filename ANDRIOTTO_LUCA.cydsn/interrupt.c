/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "interrupt.h"
#include "project.h"
#include "define.h"
#include "cytypes.h"
#include "stdio.h"

CY_ISR_PROTO(SW_ISR){
    // aggiorno l'ODR
    outputDataRate = ((outputDataRate + 1) % 6);
    // aggioramento della EEPROM
    writeMemory = 1;
    
    char message[50];
    sprintf(message, "ODR changed to: %d\r\n", outputDataRate);
    UART_PutString(message);
}

/* [] END OF FILE */
