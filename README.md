# pm25
Arduino Library for PM1.0/2.5/10 Laser Dust Sensor

## APIs
### init()

  Initialise PM25 sensor communication
  
  **Usage**
  
  `PM25.init(Stream *pm25_ser, Stream *debugSerial, void(*listen)())`
  
  **Parameters**
    
  * **pm25_ser**: HardwareSerial or SoftwareSerial object for UART communication with PM25 sensor
    
  * **debugSerial**: HardwareSerial or SoftwareSerial object for debugging
    
  * **listen** : function pointer, it is used when 1 or more SoftwareSerials are used, check examples
 
  **Returns**
  
  boolean (true if success)

### start()

  Start taking particle measurement (this function is enabled by default)
  
  **Usage**
  
  `PM25.start()`
  
  **Parameters**
  
  None
  
  **Returns**
  
  boolean (true if success)
  
### stop()

  Stop taking particle measurement
  
  **Usage**
  
  `PM25.stop()`
  
  **Parameters**
  
  None
  
  **Returns**
  
  boolean (true if success)
  
### read()

  Start taking new particle measurement result, by default it gives PM2.5 value
  
  **Usage**
  
  `uint16_t val = PM25.read()`
  
  `uint16_t val = PM25.read(PM01_TYPE)`
  
  `uint16_t val = PM25.read(PM25_TYPE)`
  
  `uint16_t val = PM25.read(PM10_TYPE)`
  
  **Parameters**
  
  * **Options**: PM01_TYPE, PM25_TYPE, PM10_TYPE
  
  **Returns**
  
  uint16_t (unsigned int)
  
### get()
  
  Gets the previously recorded particle measurement result (if any), normally used with [loop()](#loop)
  
  **Usage**
  
  `uint16_t val = PM25.get()`
  
  `uint16_t val = PM25.get(PM01_TYPE)`
  
  `uint16_t val = PM25.get(PM25_TYPE)`
  
  `uint16_t val = PM25.get(PM10_TYPE)`
  
  **Parameters**
  
  * **Options**: PM01_TYPE, PM25_TYPE, PM10_TYPE
  
  **Returns**
  
  uint16_t (unsigned int)
  
### enableAutoSend()
  
  Enable auto sampling, with fixed interval 1s
  
  **Usage**
  
  `PM25.enableAutoSend()`
  
  **Parameters**
  
  None
  
  **Returns**
  
  boolean (true if success)

### disableAutoSend()

  Disable auto sampling
  
  **Usage**
  
  `PM25.disableAutoSend()`
  
  **Parameters**
  
  None
  
  **Returns**
  
  boolean (true if success)
  
### setAdjustmentCOF()

  Set customer adjustment coefficient
  
  **Usage**
  
  `PM25.setAdjustmentCOF(val)`
  
  **Parameters**
  
  * **val**: range is from 30 - 200
  
  **Returns**
  
  boolean (true if success)
  
### getAdjustmentCOF()

  Get customer adjustment coefficient, by default the return value is 100
  
  **Usage**
  
  `PM25.getAdjustmentCOF()`
  
  **Parameters**
  
  None
  
  **Returns**
  
  uint8_t (unsigned char)
  
### loop()

  With [enableAutoSend()](#enableautosend), automatically gets the values from auto sampling. If successful, updates the sensor values, otherwise initialise the sensor values to 0. User can obtain the value by using [get()](#get)
  
  **Usage**
  
  `PM25.loop()`
  
  **Parameters**
  
  None
  
  **Returns**
  
  boolean (true if success)
