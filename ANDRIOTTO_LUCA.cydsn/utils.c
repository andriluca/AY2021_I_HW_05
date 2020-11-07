/* ========================================
 * Assignment #1, Luca Andriotto
 * ========================================
*/

#include "utils.h"

void doButtonPressed();

void init()
{
    // init UART
    UART_Start();
    
    // init EEPROM
    EEPROM_Start();
    
    // init i2c
    I2C_Peripheral_Start();

    // init accelerometer
    I2C_LIS3DH_Start();
    
    // init interrupt
    CyGlobalIntEnable;
    isr_BUTTON_StartEx(SW_ISR);       

    // init variables
    outputDataRate = EEPROM_ReadByte(EEPROM_REGISTER);
    writeMemory = 0;
}

void loop()
{
    for(;;)
    {
        // Checking if the button is pressed
        if(writeMemory) doButtonPressed();
        // Populating and sending the array through UART
        I2C_LIS3DH_Manage_Data(outarray);
    }
}

void doButtonPressed()
{
    // Preparing and saving updated ODR on EEPROM
    EEPROM_UpdateTemperature();
    EEPROM_WriteByte(outputDataRate,EEPROM_REGISTER);
    // Update register 1
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                    LIS3DH_CTRL_REG1,
                                    ((outputDataRate + 1) << 4 | LIS3DH_HI_RES_CTRL_REG1));
}