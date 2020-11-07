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

    
    char message1[50];
    uint8_t error;
    //sprintf(message1, "\r\n%d\r\n%d\r\n%d\r\n", sensorData[0], sensorData[1], sensorData[2]);    
    //sprintf(message1, "\r\n%02f\r\n%f\r\n%f\r\n", data[0], data[1], data[2]);    
    //UART_PutString(message1);
    //CyDelay(100);
    for(;;)
    {
        if(writeMemory)
        {
            EEPROM_UpdateTemperature();
            EEPROM_WriteByte(outputDataRate,EEPROM_REGISTER);
            // scrivere sul registro 1
            I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_CTRL_REG1,
                                        ((outputDataRate + 1) <<4 | LIS3DH_HI_RES_CTRL_REG1));
        }
        /* Place your application code here. */
        error = I2C_LIS3DH_Get_Data(data);
        sprintf(message1, "x: %.02f\r\n", data[0]);
        UART_PutString(message1);
        sprintf(message1, "y: %.02f\r\n", data[1]);
        UART_PutString(message1);
        sprintf(message1, "z: %.02f\r\n", data[2]);
        UART_PutString(message1);
//        if(error == I2C_Master_MSTR_NO_ERROR) UART_PutString("Error in getting data\r\n");
//        else UART_PutString("getting data: OK\r\n");
//        I2C_LIS3DH_Get_Raw_Data(sensorData);
        error=I2C_LIS3DH_Send_Data(out,data);
//        if(error == I2C_Master_MSTR_NO_ERROR) UART_PutString("Error in getting data\r\n");
//        else UART_PutString("getting data: OK\r\n");
//        I2C_LIS3DH_Send_Raw_Data(raw_out,sensorData);
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
    
    outputDataRate = EEPROM_ReadByte(EEPROM_REGISTER);

    out[0] = 0xA0;
    out[BYTE_TO_TRANSFER-1] = 0xC0;
    
    raw_out[0] = 0xA0;
    raw_out[RAW_BYTE_TO_TRANSFER-1] = 0xC0;
    writeMemory = 0;
}
