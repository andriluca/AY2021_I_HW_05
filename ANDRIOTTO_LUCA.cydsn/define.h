/* ========================================
 * Assignment #05, Luca Andriotto
 * ========================================
*/

#ifndef __DEFINE_H
    #define __DEFINE_H
    
    // addresses
    #define LIS3DH_DEVICE_ADDRESS       0x18        // Accelerometer's slave address (SAD)
    #define LIS3DH_CTRL_REG1            0x20        // Register 1 --> setup Hi Res Mode (ODRs' selection happens in interrupt)
    #define LIS3DH_CTRL_REG4            0x23        // Register 4 --> setup FS[1:0] + LIS3DH_SENSITIVITY (use masks below)
    #define LIS3DH_STATUS_REG           0x27        // Status Register
    #define LIS3DH_OUT_X_L              0x28        // First output register
    #define LIS3DH_OUT_N                6           // Number of output registers
    #define LIS3DH_OUT_AXES             3           // Accelerometer's number of axes
    
    // data values
    #define LIS3DH_HI_RES_CTRL_REG1     0x07        // Partial mask: the rest is initialized and modified by the interrupt
    #define LIS3DH_ZYXDA_STATUS_REG     0x08        // New available data incoming from the register
    
    // Full Scale Range. This values can be changed 
    #define LIS3DH_HI_RES_CTRL_REG4_FS0 0x00    // FS = [-2, +2]g   --> So = 1   
    #define LIS3DH_HI_RES_CTRL_REG4_FS1 0x10    // FS = [-4, +4]g   --> So = 2   chosen
    #define LIS3DH_HI_RES_CTRL_REG4_FS2 0x20    // FS = [-8, +8]g   --> So = 4   
    #define LIS3DH_HI_RES_CTRL_REG4_FS3 0x30    // FS = [-16, +16]g --> So = 12
    #define LIS3DH_HI_RES_CTRL_REG4     0x08 | LIS3DH_HI_RES_CTRL_REG4_FS1
    #define LIS3DH_SENSITIVITY          2                                   // mg/digit
    
    #define GRAVITY                     9.81                                // ms^-2
    #define CONVERSION                  LIS3DH_SENSITIVITY*0.001*GRAVITY    // ms^-2*digit^-1
    
    #define EEPROM_REGISTER             0x000f                              // EEPROM register for initialization
    #define EEPROM_INIT_VALUE           0x00                                // Initial value if cell content was incosistent.
                                                                            // 0x00 -->   1Hz   chosen
                                                                            // 0x01 -->  10Hz
                                                                            // 0x02 -->  25Hz
                                                                            // 0x03 -->  50Hz
                                                                            // 0x04 --> 100Hz
                                                                            // 0x00 --> 200Hz
    
    #define LIS3DH_RESOLUTION           12                                          // Hi Res
    #define LIS3DH_TOTAL_BITS           16                                          // Bits to memorize data (in digit)
    #define LIS3DH_RIGHT_SHIFT          (LIS3DH_TOTAL_BITS - LIS3DH_RESOLUTION)     // to perform right shift
    
    #define BYTES_PER_AXIS              (uint8_t)(LIS3DH_RESOLUTION/LIS3DH_OUT_AXES) 
    #define BYTE_TO_TRANSFER            1 + LIS3DH_RESOLUTION + 1
    
    
#endif
