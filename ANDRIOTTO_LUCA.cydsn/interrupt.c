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
    outputDataRate = EEPROM_ReadByte(EEPROM_REGISTER);
    outputDataRate = ((outputDataRate + 1) % 6);
    // aggioramento della EEPROM
    EEPROM_UpdateTemperature();
    EEPROM_WriteByte(outputDataRate,EEPROM_REGISTER);
    // scrivere sul registro 1
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG1,
                                 ((EEPROM_ReadByte(EEPROM_REGISTER) + 1)<<4 | LIS3DH_HI_RES_CTRL_REG1));
    
    char message[50];
    sprintf(message, "ODR changed to: %d\r\n", outputDataRate);
    UART_PutString(message);
}

/* [] END OF FILE */
