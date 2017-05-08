# pm25
Arduino Library for PM1.0/2.5/10 Laser Dust Sensor

## APIs
> ### init()

  Initialise PM25 sensor communication
  
  **Usage**
  
  `PM25.init(Stream *pm25_ser, Stream *debugSerial, void(*listen)())`
  
  **Parameters**
    
  * **pm25_ser**: HardwareSerial or SoftwareSerial object for UART communication with PM25 sensor
    
  * **debugSerial**: HardwareSerial or SoftwareSerial object for debugging
    
  * **listen** : function pointer, it is used when 1 or more SoftwareSerials are used, check examples
 
  **Returns**
  boolean (true if success)

> ### start()

  Start taking particle measurement (this function is enabled by default)
  
  **Usage**
  
  `PM25.start()`
  
  **Parameters**
  
  None
  
  **Returns**
  boolean (true if success)
  
> ### stop()

  Stop taking particle measurement
  
  **Usage**
  
  `PM25.stop()`
  
  **Parameters**
  
  None
  
  **Returns**
  boolean (true if success)
  
> ### read()

  Start taking particle measurement result, by default it gives PM2.5 value
  
  **Usage**
  
  `uint16_t val = PM25.read()`
  
  `uint16_t val = PM25.read(PM01_TYPE)`
  
  `uint16_t val = PM25.read(PM25_TYPE)`
  
  `uint16_t val = PM25.read(PM10_TYPE)`
  
  **Parameters**
  
  * **Options**: PM01_TYPE, PM25_TYPE, PM10_TYPE
  
  **Returns**
  uint16_t (unsigned int)
  
> ### get()
> ### enableAutoSend()
> ### disableAutoSend()
> ### setAdjustmentCOF()
> ### getAdjustmentCOF()
 
## Debug
