/* ========================================
 * Assignment #05, Luca Andriotto
 * ========================================
*/

#include "stats.h"

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

void stateMachine()
{
    /*    -----> [zyxda]-----------
         /                         \
         |                          v
        IDLE -> [pressing] --> S1   S2
         ^                     |    |
         |                     |    |
         \____________________ /<___/
    */
    for(;;)
    {
        // IDLE: Reading status register
        I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,LIS3DH_STATUS_REG,&zyxda);        
        // S0: Checking if the button is pressed
        if(writeMemory) doButtonPressed();
        // S1: Populating and sending the array through UART
        if(zyxda & LIS3DH_ZYXDA_STATUS_REG) I2C_LIS3DH_Manage_Data(outarray);
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