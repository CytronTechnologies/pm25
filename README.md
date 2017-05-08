# pm25
Arduino Library for PM1.0/2.5/10 Laser Dust Sensor

## APIs
`PM25.init(Stream *pm25_ser, Stream *debugSerial, void(*listen)())`

  **Description**
    - Initialise PM25 sensor communication
 
  **Parameters**
    
  * **pm25_ser**: HardwareSerial or SoftwareSerial object for UART communication with PM25 sensor
    
  * **debugSerial**: HardwareSerial or SoftwareSerial object for debugging (by default **Serial**)
    
  * **listen** : function pointer, it is used when 1 or more SoftwareSerials are used, check examples
 
  **Returns**
    - boolean
 
## Debug
