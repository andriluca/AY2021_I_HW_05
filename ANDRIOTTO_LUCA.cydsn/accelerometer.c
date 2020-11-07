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
    for(int i = 0; i < LIS3DH_OUT_AXES; i++)  data[i] = sensorData[i] * CONVERSION;
    
    return error ? ERROR : NO_ERROR;
}

ErrorCode I2C_LIS3DH_Send_Data(uint8_t* out, float32* data)
{
    union {
        float32 f;
        uint32_t l;
    } floating[3];
    
    int i=0, j=0;
    
    floating[0].f = data[0];
    floating[1].f = data[1];
    floating[2].f = data[2];
    
    for(int count = 1; count < BYTE_TO_TRANSFER - 1; count++) 
    {
        out[count] = floating[i].l>>8*j & 0xff;
        j=(j+1)%4;
        if(!(count%4)) i++;
    }
    
//    char message[55];
//    sprintf(message, "x: %02x %02x %02x %02x\r\n",out[4],out[3],out[2],out[1]);
//    UART_PutString(message);
//    CyDelay(1000);
//    sprintf(message, "y: %02x %02x %02x %02x\r\n",out[8],out[7],out[6],out[5]);
//    UART_PutString(message);
//    CyDelay(1000);
//    sprintf(message, "z: %02x %02x %02x %02x\r\n",out[12],out[11],out[10],out[9]);
//    CyDelay(1000);
//    UART_PutString(message);
//    
    UART_PutArray(out,BYTE_TO_TRANSFER);
    
    return NO_ERROR;
}

ErrorCode I2C_LIS3DH_Send_Raw_Data(uint8_t* out, int16_t* data)
{
    uint8_t i=0, j=0;
    for(int count = 1; count < RAW_BYTE_TO_TRANSFER - 1; count++) 
    {
        out[count] = (uint8_t)(data[i]>>8*j & 0xff);
        j=(j+1)%2;
        if(!(count%2)) i++;
        
    }
//    char message[55];
//    sprintf(message, "x: %02x %02x \r\n",(uint8_t)data[0]>>8 & 0xff, (uint8_t)data[0] & 0xff);
//    UART_PutString(message);
//    CyDelay(1000);
//    sprintf(message, "y: %02x %02x \r\n", (uint8_t)data[1]>>8 &0xff,(uint8_t)data[1] &0xff);
//    UART_PutString(message);
//    CyDelay(1000);
//    sprintf(message, "z: %02x %02x \r\n",(uint8_t)data[2]>>8 & 0xff,(uint8_t)data[2]&0xff);
//    UART_PutString(message);
//    CyDelay(1000);    
//    
//    sprintf(message, "x: %02x %02x \r\n",out[2],out[1]);
//    UART_PutString(message);
//    CyDelay(1000);
//    sprintf(message, "y: %02x %02x \r\n",out[4],out[3]);
//    UART_PutString(message);
//    CyDelay(1000);
//    sprintf(message, "z: %02x %02x \r\n",out[6],out[5]);
//    UART_PutString(message);
//    CyDelay(1000);    
//    
    UART_PutArray(out,RAW_BYTE_TO_TRANSFER);
    
    return NO_ERROR;
}


ErrorCode I2C_LIS3DH_Get_Raw_Data(int16_t* data)
{
    uint8_t sensorData[LIS3DH_OUT_N];
    uint8_t error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS, LIS3DH_OUT_X_L, LIS3DH_OUT_N, sensorData);
    
    for(int i = 0; i < LIS3DH_OUT_AXES; i++) data[i] = (int16_t)((sensorData[2*i+1]<<8 | sensorData[2*i])) >> LIS3DH_RIGHT_SHIFT;
    
//    char message[55];
//    sprintf(message, "x: %d\r\n",data[0]);
//    UART_PutString(message);
//    CyDelay(1000);
//    sprintf(message, "y: %d\r\n",data[1]);
//    UART_PutString(message);
//    CyDelay(1000);
//    sprintf(message, "z: %d\r\n",data[2]);
//    UART_PutString(message);
//    CyDelay(1000);    
//    
//    float32 floatdata[3];
//    for(int i = 0; i<3; i++) floatdata[i] = sensorData[i] * 2.0;
//    
//    sprintf(message, "x: %f\r\n",floatdata[0]);
//    UART_PutString(message);
//    CyDelay(1000);
//    sprintf(message, "y: %f\r\n",floatdata[1]);
//    UART_PutString(message);
//    CyDelay(1000);
//    sprintf(message, "z: %f\r\n",floatdata[2]);
//    UART_PutString(message);
//    CyDelay(1000);    
//    
    
    return error ? ERROR : NO_ERROR;
}

