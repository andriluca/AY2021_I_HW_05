/* ========================================
 * Assignment #05, Luca Andriotto
 * ========================================
*/

#include "states.h"

/*****************************************************************************\
 * Function:    doButtonPressed
 * Description: 
 *     Handles the event related to the button being pressed.
\*****************************************************************************/

void doButtonPressed();

/*****************************************************************************\
 * Function:    doButtonPressed
 * Description: 
 *     Handles the event related to the timer overflow.
\*****************************************************************************/

void doSendData();

void init()
{
    /* HARDWARE INITS */
    
    // init UART.
    UART_Start();
    // init EEPROM.
    EEPROM_Start();
    // init I2C.
    I2C_Peripheral_Start();
    // init Accelerometer.
    I2C_LIS3DH_Start();
    
    /* END HARDWARE INITS */
    
    // init Interrupt.
    CyGlobalIntEnable;
    isr_BUTTON_StartEx(SW_ISR);

    // init Variables.
    outputDataRate = EEPROM_ReadByte(EEPROM_REGISTER);
    onButtonPressed = 0;
}

void stateMachine()
{
    for(;;)
    {
        if(onButtonPressed) doButtonPressed();   // Changing ODR and updating EEPROM.
        
		doSendData();                            //	If new data are available send them.
    }
}

void doButtonPressed()
{
    // Resetting button flag.
    onButtonPressed = 0;
    // Preparing and saving updated ODR on EEPROM.
    EEPROM_UpdateTemperature();
    EEPROM_WriteByte(outputDataRate,EEPROM_REGISTER);
    // Update register 1.
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                 LIS3DH_CTRL_REG1,
                                 (outputDataRate << 4 | LIS3DH_HI_RES_CTRL_REG1));
}

void doSendData()
{
	// Reading the status register.
	I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_STATUS_REG, &zyxda);
	// If new data are available gather them and send them through UART.
	if(zyxda & LIS3DH_ZYXDA_STATUS_REG)  I2C_LIS3DH_Manage_Data(outarray); 
}