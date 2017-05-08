#include <pm25.h>
#include <SoftwareSerial.h>
SoftwareSerial pm25_ser(8, 9);

void PM25_listen(){
  if(!pm25_ser.isListening()){
    Serial.println(F("[PM25] >> Listening"));
    pm25_ser.listen();
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pm25_ser.begin(9600);
  
  // set uart for pm25, and uart for debug
  // set listen function if one or more SoftwareSerials are used
  PM25.init(&pm25_ser, &Serial, PM25_listen);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  // update values at every 5s interval

  uint16_t val = PM25.read();
  Serial.print(F("PM2.5 val: ")); 
  Serial.print(val);
  Serial.println(F("  ug/m3"));

  delay(5000);
}
