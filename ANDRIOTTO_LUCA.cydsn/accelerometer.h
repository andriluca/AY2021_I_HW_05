/* ========================================
 * Assignment #1, Luca Andriotto
 * ========================================
*/

#ifndef ACCELEROMETER_H

    #define ACCELEROMETER_H
    #include "i2c.h"
    #include "define.h"
    
    typedef union
    {
        float32 data;
        uint32_t mask;
    } outtype;

    // Array collecting the float to send
    outtype outarray[LIS3DH_OUT_AXES];
    
    
/*****************************************************************************\
 * Function:    I2C_LIS3DH_Start
 * Input:       
 * Returns:     ErrorCode
 * Description: 
 *     Initialization of the LIS3DH Config Registers
\*****************************************************************************/
   
    ErrorCode I2C_LIS3DH_Start();
    
/*****************************************************************************\
 * Function:    I2C_LIS3DH_Manage_Data
 * Input:       outtype* array
 * Returns:     ErrorCode
 * Description: 
 *     Gathers LIS3DH data and sends them through UART
\*****************************************************************************/
    
    ErrorCode I2C_LIS3DH_Manage_Data(outtype* array);
    
#endif


