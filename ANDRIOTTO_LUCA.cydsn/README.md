# Assignment \#05

## Code organization
1. "states.h" and "states.c": Functions handling the initialization of the peripheral and the state machine.
1. "accelerometer.h" and "accelerometer.c": Functions handling LIS3DH module (Initialization, data acquisition and sending).
1. "i2c.h" and "i2c.c": Functions handling I2C Master communication (Initialization, writing and reading registers)
1. "interrupt.h" and  "interrupt.c": Function handling the routine when the button is pressed.
1. "defines.h": Constants relevant for correct functioning of the system.

### Features required by the context
1. "utils.h" > init(): 
    - Checks if the content of the EEPROM Register is out of the encoded values configures it correctly.
1. "accelerometer.h" > I2C\_LIS3DH\_Start():
    - Writes the configuration register to make LIS3DH module work correctly.
1. "interrupt.h" > CY_\__ISR\_PROTO(SW_\__ISR):
    - Updates circularly a variable representing the ODR. It also sets up a flag in order for the "states.h" > stateMachine() to write the updated value to the EEPROM.
1. "states.h" > stateMachine()
    - If a timeout has occurred, the data buffer is sent through UART.
1. "accelerometer.h" > I2C\_LIS3DH\_Manage\_Data(outtype* array):
    - Acquires the data from LIS3DH module (digit), converts it in ms^-2 and sends them as float to BCP. The obtained precision is the one of floating point data.
