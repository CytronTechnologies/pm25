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
  
  // enable auto send, allows auto sampling at 1s interval
  PM25.enableAutoSend();
  
}

void loop() {

  // put your main code here, to run repeatedly:

  // loop() return true if values for PM25 is successfully updated
  if(PM25.loop()){
    Serial.print("PM2.5 val: ");
    Serial.print(PM25.get());
    Serial.println("  ug/m3");
  }
}
