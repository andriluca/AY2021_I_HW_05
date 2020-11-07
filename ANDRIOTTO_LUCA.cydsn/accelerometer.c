/* ========================================
 * Assignment #1, Luca Andriotto
 * ========================================
*/

#include "accelerometer.h"

/*****************************************************************************\
 * Function:    I2C_LIS3DH_Get_Raw_Data
 * Input:       int16_t data
 * Returns:     ErrorCode
 * Description: 
 *     Populates an int16_t array with right-aligned sensor data
\*****************************************************************************/


ErrorCode I2C_LIS3DH_Get_Raw_Data(int16_t* data);

ErrorCode I2C_LIS3DH_Start()
{
    // Reading EEPROM register dedicated to startup ODR
    // Checking if the memorized value is in allowed range
    // if the value is out of range --> ODR is set to 1Hz
    if(EEPROM_ReadByte(EEPROM_REGISTER) > 6){
        EEPROM_UpdateTemperature();
        EEPROM_WriteByte(EEPROM_INIT_VALUE,EEPROM_REGISTER);
    }
    
    // init CTRL_REG1
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                LIS3DH_CTRL_REG1,
                                // writing the 4 MSb of the register 1 (related to ODR)
                                ((EEPROM_ReadByte(EEPROM_REGISTER) + 1)<<4 | LIS3DH_HI_RES_CTRL_REG1));
    
    // init CTRL_REG4
    I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                LIS3DH_CTRL_REG4,
                                LIS3DH_HI_RES_CTRL_REG4);
    
    return NO_ERROR;
}

ErrorCode I2C_LIS3DH_Manage_Data(outtype* array)
{
    // Initializing the data buffer
    uint8_t out[BYTE_TO_TRANSFER];
    out[0] = 0xA0;                      // --> HEADER
    out[BYTE_TO_TRANSFER - 1] = 0xC0;   // --> TAIL

    // Array dedicated to save accelerometer data in digit.
    int16_t sensorData[3];
    
    // Data acquisition
    I2C_LIS3DH_Get_Raw_Data(sensorData);
    
    // Data conversion
    for(int i = 0; i < LIS3DH_OUT_AXES; i++)  array[i].data = sensorData[i] * CONVERSION;
    
    // Counters
    int arrayIndex=0, shiftIndex=0;    // arrayIndex is used to browse the array cells. 
                                       // shiftIndex is used in order to perform the right shift operation on the data.
    for(int count = 1; count < BYTE_TO_TRANSFER - 1; count++) 
    {
        out[count] = array[arrayIndex].mask>>8*shiftIndex & 0xff;   // populating the union in its float argument
        shiftIndex=(shiftIndex+1) % BYTES_PER_AXIS;                 // updating the shift index
        if(!(count % BYTES_PER_AXIS)) arrayIndex++;                 // updating the array index, once all the data related to one axis are gathered.
    }
    
    // Sending the populated array
    UART_PutArray(out,BYTE_TO_TRANSFER);
    return NO_ERROR;
}

ErrorCode I2C_LIS3DH_Get_Raw_Data(int16_t* data)
{
    uint8_t sensorData[LIS3DH_OUT_N]; // This array is storing left aligned bytes coming from accelerometer
    
    // Storing the data coming from accelerometer
    uint8_t error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS, LIS3DH_OUT_X_L, LIS3DH_OUT_N, sensorData);
    
    // Re-arranging data to have them right aligned as integers
    for(int i = 0; i < LIS3DH_OUT_AXES; i++) data[i] = (int16_t)((sensorData[2*i+1]<<8 | sensorData[2*i])) >> LIS3DH_RIGHT_SHIFT;   
    
    return error ? ERROR : NO_ERROR;
}
