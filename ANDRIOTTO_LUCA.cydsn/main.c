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
#include "project.h"
#include "define.h"
#include "interrupt.h"
#include "i2c.h"
#include "stdio.h"
#include "accelerometer.h"

void Peripherals_Init();

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    int16_t sensorData[3];
    float32 data[3];
    Peripherals_Init();
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    I2C_LIS3DH_Get_Data(data);
    char message1[50];
    //sprintf(message1, "\r\n%d\r\n%d\r\n%d\r\n", sensorData[0], sensorData[1], sensorData[2]);    
    //sprintf(message1, "\r\n%02f\r\n%f\r\n%f\r\n", data[0], data[1], data[2]);    
    //UART_PutString(message1);
    //CyDelay(100);
    for(;;)
    {
        /* Place your application code here. */
    }
}

void Peripherals_Init()
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
    isr_BUTTON_StartEx(SW_ISR);       
    
}
