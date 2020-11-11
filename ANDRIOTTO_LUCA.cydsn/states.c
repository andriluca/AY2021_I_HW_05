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

void doTimeout();

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
    isr_TIMER_CHECK_STATUS_StartEx(TIMER_CHECK_STATUS_ISR);

    // init variables
    outputDataRate = EEPROM_ReadByte(EEPROM_REGISTER);
    onButtonPressed = 0;
    onTimeout = 0;
    
    // init Timer
    Timer_Check_Status_Start();    
}

void stateMachine()
{
	/*    -----> [Timeout]---------
         /                         \
         |                          v
        IDLE -> [pressing] --> S1   S2
         ^                     |    |
         |                     |    |
         \---------------------/<---/
    */
    for(;;)
    {
        // S0: 	Checking if the button has been pressed
		//		or if timeout has occurred.
        if(onButtonPressed) doButtonPressed(); 	// S1 -->	changing ODR and updating
												//			EEPROM.
        if(onTimeout) doTimeout();				// S2 -->	checking the status register,
												//			if new data are available manage them.
		
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
                                 ((outputDataRate + 1) << 4 | LIS3DH_HI_RES_CTRL_REG1));
}

void doTimeout()
{
	// Resetting timeout flag.
	onTimeout = 0;
	// Reading the status register.
	I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,LIS3DH_STATUS_REG,&zyxda);
	// If new data are available gather them and send them through UART.
	if(zyxda & LIS3DH_ZYXDA_STATUS_REG)  I2C_LIS3DH_Manage_Data(outarray); 
}