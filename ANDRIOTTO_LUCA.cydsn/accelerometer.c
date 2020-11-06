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
#include "accelerometer.h"



ErrorCode I2C_LIS3DH_Start()
{
    // Reading EEPROM register dedicated to startup ODR
    // Checking if the memorized value is in allowed range
    if(EEPROM_ReadByte(EEPROM_REGISTER) > 6){
        EEPROM_UpdateTemperature();
        EEPROM_WriteByte(EEPROM_INIT_VALUE,EEPROM_REGISTER);
    }
    
    // init CTRL_REG1
    uint8_t error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                                LIS3DH_CTRL_REG1,
                                                ((EEPROM_ReadByte(EEPROM_REGISTER) + 1)<<4 | LIS3DH_HI_RES_CTRL_REG1));
    char message[50];
    sprintf(message,"init ODR: %d\r\n", EEPROM_ReadByte(EEPROM_REGISTER));
    UART_PutString(message);
    
    if(error == I2C_Master_MSTR_NO_ERROR)   UART_PutString("=== Setup Reg1 === \r\n");
    else                                    UART_PutString("=== ERROR: setup reg1 === \r\n");
    
    // init CTRL_REG4
    
    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                         LIS3DH_CTRL_REG4,
                                         LIS3DH_HI_RES_CTRL_REG4);
    
    if(error == I2C_Master_MSTR_NO_ERROR)   UART_PutString("=== Setup Reg4 === \r\n");
    else                                    UART_PutString("=== ERROR: setup reg4 ===\r\n");
    
    return error ? ERROR : NO_ERROR;
}
    
ErrorCode I2C_LIS3DH_Get_Data(float32* data)
{
    int16_t sensorData[3];
    uint8_t error = I2C_LIS3DH_Get_Raw_Data(sensorData);
    for(int i = 0; i < LIS3DH_OUT_AXES; i++)  data[i] = (float32)sensorData[i] * CONVERSION;
    
    return error ? ERROR : NO_ERROR;
}

ErrorCode I2C_LIS3DH_Get_Raw_Data(int16_t* data)
{
    uint8_t sensorData[LIS3DH_OUT_N];
    uint8_t error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS, LIS3DH_OUT_X_L, LIS3DH_OUT_N, sensorData);
    
    for(int i = 0; i<LIS3DH_OUT_AXES; i++) data[i] = (int16_t)((sensorData[2*i+1]<<8 | sensorData[2*i])) >> LIS3DH_RIGHT_SHIFT;
    
    return error ? ERROR : NO_ERROR;
}

