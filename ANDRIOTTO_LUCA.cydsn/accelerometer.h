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
#ifndef ACCELEROMETER_H
    #define ACCELEROMETER_H
    #include "i2c.h"
    #include "define.h"
    #include "stdio.h"
    
    ErrorCode I2C_LIS3DH_Start();
    
    ErrorCode I2C_LIS3DH_Get_Raw_Data(int16_t* data);
    
    ErrorCode I2C_LIS3DH_Get_Data(float32* data);
    
    ErrorCode I2C_LIS3DH_Send_Data(uint8_t* out, float32* data);
    
    ErrorCode I2C_LIS3DH_Send_Raw_Data(uint8_t* out, int16_t* data);
    
#endif


