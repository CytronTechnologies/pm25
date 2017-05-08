#include "pm25.h"
#include "utility/debug.h"

void (*pm25_listen)() = NULL;

pm25 PM25;

pm25::pm25():
	pm01_val(0), 
	pm25_val(0),
	pm10_val(0)
{

}

bool pm25::init(Stream *serial, Stream *debugSerial, void (*ptr)()){
	_serial = serial;
	_serial->setTimeout(PM25_RESP_TIME);

	_debugSerial = debugSerial;

	pm25_listen = ptr;

	// disable autosend by default
	if(disableAutoSend()){
		LOGINFO("Initialisation successful")
		return true;
	}
	else{
		LOGERROR("Initialisation failed")
		while(1);
	}
	return false;
}

uint16_t pm25::get(pm25_sensor_type type){
	
	if(type == PM01_TYPE)
		return pm01_val;
	else if(type == PM25_TYPE)
		return pm25_val;
	else if(type == PM10_TYPE)
		return pm10_val;
	else
		return 0;
}

uint16_t pm25::read(pm25_sensor_type type){

	uint8_t resp[4];
	if(sendCmdAndGet(resp, sizeof(resp), 0x04)){
		pm01_val = 0; // not needed
		pm25_val = resp[0] << 8 | resp[1];
		pm10_val = resp[2] << 8 | resp[3];
	}
	else{
		// if command failed, initialise all values to 0
		pm01_val = pm25_val = pm10_val = 0;
	}
	return get(type);
}

bool pm25::start(){
	return sendCmd(0x01);
}

bool pm25::stop(){
	return sendCmd(0x02);
}

bool pm25::enableAutoSend(){
	return sendCmd(0x40);
}

bool pm25::disableAutoSend(){
	return sendCmd(0x20);
}

bool pm25::setAdjustmentCOF(uint8_t value){
	uint8_t header[2] = {0x68, 0x02};
	return sendCmd(0x08, value, false, header);
}

uint8_t pm25::getAdjustmentCOF(){
	uint8_t resp[1];
	if(sendCmdAndGet(resp, sizeof(resp), 0x10)){
		return resp[0];
	}
	else
		return 0xFF;
}

bool pm25::loop(){
	// initialise values to 0
	pm01_val = pm25_val = pm10_val = 0;
	pm25_listen();
	if(_serial->available()){
		/*while(_serial->available()){
			Serial.print(_serial->read(), HEX);
			Serial.print(" ");
		}
		Serial.println();*/

		uint8_t buf[32];
		if(_serial->find(0x42)){
			LOGINFO("Start auto sampling")
			_serial->readBytes(buf+1, 31);
			buf[0] = 0x42;

			for(uint8_t i=0; i< sizeof(buf);i++){
				LOGDEBUGHEX(buf[i])
				LOGDEBUG0(" ")
			}
			LOGDEBUGLN()

			if(buf[1] == 0x4d){
				if(getCheckSum(buf, sizeof(buf)) == (buf[30] << 8 | buf[31])){ //checksum
					//update the values
					pm01_val = buf[4] << 8 | buf[5];
					pm25_val = buf[6] << 8 | buf[7];
					pm10_val = buf[8] << 8 | buf[9];
					return true;
				}
			}
			LOGERROR("Incorrect data/Incorrect checksum/Unknown error")
		}
		/*else
			_serial->read();*/
	}
	return false;
}

bool pm25::sendCmd(uint8_t cmd, bool general, uint8_t *header){
	pm25_listen();
	flush();
	uint8_t temp[32];
	uint8_t cmdBuf[4] = {0, 0, 0, 0};
	if(general){
		cmdBuf[0] = 0x68;
		cmdBuf[1] = 0x01;
	}
	else{
		cmdBuf[0] = header[0];
		cmdBuf[1] = header[1];
	}
	cmdBuf[2] = cmd;
	cmdBuf[3] = getCheckSum8(cmdBuf, sizeof(cmdBuf));
	LOGINFO("Sending command")
	for(uint8_t i=0; i< sizeof(cmdBuf);i++){
		LOGDEBUGHEX(cmdBuf[i])
		LOGDEBUG0(" ")
		_serial->write(cmdBuf[i]);
	}
	LOGDEBUGLN()
	delay(PM25_DELAY);

	while(_serial->available()){
		
		// check if there is auto send buffer
		if(_serial->peek() == 0x42){
			_serial->readBytes(temp, 32);
			continue;
		}

		else{
			if(_serial->read() == 0xa5 && _serial->read() == 0xa5){
				LOGINFO("Positive ACK")
				return true;
			}
			else{
				LOGINFO("Negative ACK")
				return false;
			}

		}
	}

	/*if(_serial->find(0xA5)){
		Serial.print(_serial->read(), HEX);
		Serial.print(" ");
		//return (_serial->read() == 0xa5);
		return true;
	}

	else
		return false;*/

}

bool pm25::sendCmd(uint8_t cmd, uint8_t value, bool general, uint8_t *header){
	pm25_listen();
	flush();
	uint8_t temp[32];
	uint8_t cmdBuf[5] = {0, 0, 0, 0, 0};
	if(general){
		cmdBuf[0] = 0x68;
		cmdBuf[1] = 0x01;
	}
	else{
		cmdBuf[0] = header[0];
		cmdBuf[1] = header[1];
	}
	cmdBuf[2] = cmd;
	cmdBuf[3] = value;
	cmdBuf[4] = getCheckSum8(cmdBuf, sizeof(cmdBuf));
	LOGINFO("Sending command with value")
	for(uint8_t i=0; i< sizeof(cmdBuf);i++){
		LOGDEBUGHEX(cmdBuf[i])
		LOGDEBUG0(" ")
		_serial->write(cmdBuf[i]);
	}
	LOGDEBUGLN()
	delay(PM25_DELAY);

	while(_serial->available()){
		
		// check if there is auto send buffer
		if(_serial->peek() == 0x42){
			_serial->readBytes(temp, 32);
			continue;
		}

		else{
			if(_serial->read() == 0xa5 && _serial->read() == 0xa5){
				LOGINFO("Positive ACK")
				return true;
			}
			else{
				LOGINFO("Negative ACK")
				return false;
			}
		}
	}
}

bool pm25::sendCmdAndGet(uint8_t *buf, uint8_t len, uint8_t cmd, bool general, uint8_t *header){
	pm25_listen();
	flush();
	uint8_t cmdBuf[4] = {0, 0, 0, 0};
	for(uint8_t i=0; i < len; i++)
		buf[i] = 0;

	if(general){
		cmdBuf[0] = 0x68;
		cmdBuf[1] = 0x01;
	}
	else{
		cmdBuf[0] = header[0];
		cmdBuf[1] = header[1];
	}
	cmdBuf[2] = cmd;
	cmdBuf[3] = getCheckSum8(cmdBuf, sizeof(cmdBuf));
	LOGINFO("Sending command and expecting value returned")
	for(uint8_t i=0; i< sizeof(cmdBuf);i++){
		LOGDEBUGHEX(cmdBuf[i])
		LOGDEBUG0(" ")
		_serial->write(cmdBuf[i]);
	}
	LOGDEBUGLN()
	delay(PM25_DELAY);

	long timeout = PM25_RESP_TIME;

	while(_serial->available() && timeout--){

		if(_serial->peek() == 0x42){
			uint8_t temp[32];
			_serial->readBytes(temp, 32);
			delay(1);
			continue;
		}

		else if(_serial->peek() == 0x96){
			if(_serial->read() == 0x96 && _serial->read() == 0x96){
				LOGERROR("Negative ACK")
				return false;
			}
		}

		else if(_serial->read() == 0x40){
			timeout = PM25_RESP_TIME;
			int len = _serial->read();
			uint8_t resp[len+2] = {0};
			_serial->readBytes(resp+2, len);
			uint8_t checksum = _serial->read();
			resp[0] = 0x40; resp[1] = len;

			for(uint8_t i=0; i< sizeof(resp);i++){
				LOGDEBUGHEX(resp[i])
				LOGDEBUG0(" ")
			}
			LOGDEBUGHEX(checksum)
			LOGDEBUG0(" ")
			LOGDEBUGLN()

			uint8_t chcksum = getCheckSum8(resp, sizeof(resp));
			//Serial.print("Checksum: ");Serial.println(chcksum, HEX);

			if(checksum == chcksum){
				for(uint8_t i=0;i<len-1;i++){
					buf[i]=resp[i+3];
				}
				return true;
			}
			else{
				LOGERROR("INVALID CHECKSUM")
				return false;
			}
		}
		delay(1);
	}
	LOGERROR(">>> Timeout")
	return false;
}

uint8_t pm25::getCheckSum8(uint8_t *buf, uint8_t len){
	uint16_t total = 0;
	for(uint8_t i=0; i < len; i++){
		total += buf[i];
	}
	total = 65535 - total;
	total = total + 1;
	total = total % 256;
	return (uint8_t)total;
}

uint16_t pm25::getCheckSum(uint8_t *buf, uint8_t len){
	uint16_t total = 0;
	for(int i=0 ;i < (len-2); i++){
		total += buf[i];
	}
	return total;
}

void pm25::flush(){
	while(_serial->available()){
		_serial->read();
	}
}

