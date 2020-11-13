# Assignment \#05

## Code organization
1. __"states.h"__ and __"states.c"__: Functions handling the initialization of the peripheral and the state machine.
1. __"accelerometer.h"__ and __"accelerometer.c"__: Functions handling LIS3DH module (Initialization, data acquisition and sending).
1. __"i2c.h"__ and __"i2c.c"__: Functions handling I2C Master communication (Initialization, writing and reading registers)
1. __"interrupt.h"__ and  __"interrupt.c"__: Function handling the routine when the button is pressed.
1. __"defines.h"__: Constants relevant for correct functioning of the system.

### Features required by the context
1. _"utils.h" > init()_: 
    - Checks if the content of the EEPROM Register is out of the encoded values and configures it correctly.
1. _"accelerometer.h" > I2C\_LIS3DH\_Start()_:
    - Writes the configuration register to make LIS3DH module work correctly.
1. _"interrupt.h" > CY\_ISR\_PROTO(SW\_ISR)_:
    - Updates circularly a variable representing the ODR. It also sets up a flag in order for the "states.h" > stateMachine() to write the updated value to the EEPROM.
1. _"states.h" > stateMachine()_
    - Checks out new available data by reading the Status Register of LIS3DH.
1. _"accelerometer.h" > I2C\_LIS3DH\_Manage\_Data(outtype* array)_:
    - Acquires the data from LIS3DH module (digit), converts it in ms^-2 and sends them as float to BCP. The obtained precision is the one of floating point data.
