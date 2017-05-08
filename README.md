# pm25
Arduino Library for PM1.0/2.5/10 Laser Dust Sensor

## APIs
### init()

  Initialise PM25 sensor communication
  
  **Usage**
  
  `PM25.init(Stream *pm25_ser, Stream *debugSerial, void(*listen)())`
  
  **Parameters**
    
  * **pm25_ser**: HardwareSerial or SoftwareSerial object for UART communication with PM25 sensor
    
  * **debugSerial**: HardwareSerial or SoftwareSerial object for debugging (by default **Serial**)
    
  * **listen** : function pointer, it is used when 1 or more SoftwareSerials are used, check examples
 
  **Returns**
    - boolean

`PM25.start()`
`PM25.stop()`
`PM25.read()`
`PM25.get()`
`PM25.enableAutoSend()`
`PM25.disableAutoSend()`
`PM25.setAdjustmentCOF()`
`PM25.getAdjustmentCOF()`
 
## Debug
