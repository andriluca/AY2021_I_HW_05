/* ========================================
 * Assignment #1, Luca Andriotto
 * ========================================
*/

#ifndef __DEFINE_H
    #define __DEFINE_H
    #include "project.h"
    
    // addresses
    #define LIS3DH_DEVICE_ADDRESS       0x18
    #define LIS3DH_CTRL_REG1            0x20        // settare gli ODR nel MSB
    #define LIS3DH_CTRL_REG4            0x23        // settare FS[1:0] e LIS3DH_SENSITIVITY (vedi maschere sotto)
    #define LIS3DH_OUT_X_L              0x28
    #define LIS3DH_OUT_X_H              0x29
    #define LIS3DH_OUT_Y_L              0x2A
    #define LIS3DH_OUT_Y_H              0x2B
    #define LIS3DH_OUT_Z_L              0x2C
    #define LIS3DH_OUT_Z_H              0x2D
    #define LIS3DH_OUT_N                6
    #define LIS3DH_OUT_AXES             3
    
    // data masks
    #define LIS3DH_HI_RES_CTRL_REG1     0x07        // parziale
    #define LIS3DH_HI_RES_CTRL_REG4     0x18        // totale
    
    #define GRAVITY                     9.81
    #define LIS3DH_SENSITIVITY          2.0
    #define CONVERSION                  LIS3DH_SENSITIVITY*0.001*GRAVITY    // m/(s^2 * digit)
    
    #define EEPROM_REGISTER             0x0000
    #define EEPROM_INIT_VALUE           0x01
    
    #define LIS3DH_RESOLUTION           12
    #define LIS3DH_TOTAL_BITS           16
    #define LIS3DH_RIGHT_SHIFT          (LIS3DH_TOTAL_BITS - LIS3DH_RESOLUTION)
    
    #define REQUIRED_BYTES              12
    #define RAW_REQUIRED_BYTES          6
    #define BYTE_TO_TRANSFER            1 + REQUIRED_BYTES + 1
    #define RAW_BYTE_TO_TRANSFER        1 + RAW_REQUIRED_BYTES + 1
    #define FLOAT_LIMIT                 2147483648UL
    
    uint8 outputDataRate;
    uint8_t out[BYTE_TO_TRANSFER];
    uint8_t raw_out[RAW_BYTE_TO_TRANSFER];
    volatile uint8_t writeMemory;
    
    

    
#endif

