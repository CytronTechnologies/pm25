#ifndef _PM25_H
#define _PM25_H

#include <Arduino.h>
#include <SoftwareSerial.h>

#define PM25_RESP_TIME 1500
#define PM25_DELAY 100

typedef enum pm25_sensor_type {
	PM01_TYPE,
	PM25_TYPE,
	PM10_TYPE
};

class pm25 {

public:

	pm25();

	bool init(Stream *serial, Stream *debugSerial, void (*ptr)()=[]{});
	uint16_t get(pm25_sensor_type type=PM25_TYPE);
	uint16_t read(pm25_sensor_type type=PM25_TYPE);
	bool start();
	bool stop();
	bool enableAutoSend();
	bool disableAutoSend();
	bool setAdjustmentCOF(uint8_t value);
	uint8_t getAdjustmentCOF();
	bool loop();

private:

	Stream* _serial;
	Stream* _debugSerial;
	
	uint16_t pm01_val;
	uint16_t pm25_val;
	uint16_t pm10_val;

	bool sendCmd(uint8_t cmd, bool general=true, uint8_t *header=NULL);
	bool sendCmd(uint8_t cmd, uint8_t value, bool general=true, uint8_t *header=NULL);
	bool sendCmdAndGet(uint8_t *buf, uint8_t len, uint8_t cmd, bool general=true, uint8_t *header=NULL);
	uint8_t getCheckSum8(uint8_t *buf, uint8_t len);
	uint16_t getCheckSum(uint8_t *buf, uint8_t len);
	void flush();

};

extern pm25 PM25;

#endif