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
#ifndef __I2C_H
    #define __I2C_H
    
    typedef enum{
        NO_ERROR,
        ERROR
    } ErrorCode;
    
    #include "I2C_Master.h"
    
    ErrorCode I2C_Peripheral_Start();
    
    ErrorCode I2C_Peripheral_Stop();
    
    ErrorCode I2C_Peripheral_ReadRegister(uint8_t device_address, 
                                            uint8_t register_address,
                                            uint8_t* data);
    
    ErrorCode I2C_Peripheral_ReadRegisterMulti(uint8_t device_address, 
                                            uint8_t register_address,
                                            uint8_t register_count,
                                            uint8_t* data);
    
    ErrorCode I2C_Peripheral_WriteRegister(uint8_t device_address,
                                            uint8_t register_address,
                                            uint8_t data);
    
    
#endif


/* [] END OF FILE */
