/* ========================================
 * Assignment #05, Luca Andriotto
 * ========================================
*/

#ifndef ACCELEROMETER_H

    #define ACCELEROMETER_H
    #include "i2c.h"
    #include "define.h"
    
    // The union is the trick to decompose a float into its constituting bytes.
    // Before a byte from outtype foo.mask is sent, a bit-to-bit AND operation
    // is performed considering foo.data and foo.mask.
    // This normally isn't possible when handling floats. Magic!
    
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
 *     Initialization of the LIS3DH Config Registers. 
 *     It gathers ODR from EEPROM.
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
