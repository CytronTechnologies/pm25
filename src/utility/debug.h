#ifndef PM25Debug_H
#define PM25Debug_H

#include <stdio.h>

// Change _ESPLOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#define _PM25LOGLEVEL_ 1

#define LOGERROR(x)    if(_PM25LOGLEVEL_>0) { _debugSerial->print("[PM25] "); _debugSerial->println(x); }
#define LOGERROR1(x,y) if(_PM25LOGLEVEL_>2) { _debugSerial->print("[PM25] "); _debugSerial->print(x); _debugSerial->print(" "); _debugSerial->println(y); }
#define LOGWARN(x)     if(_PM25LOGLEVEL_>1) { _debugSerial->print("[PM25] "); _debugSerial->println(x); }
#define LOGWARN1(x,y)  if(_PM25LOGLEVEL_>2) { _debugSerial->print("[PM25] "); _debugSerial->print(x); _debugSerial->print(" "); _debugSerial->println(y); }
#define LOGINFO(x)     if(_PM25LOGLEVEL_>2) { _debugSerial->print("[PM25] "); _debugSerial->println(x); }
#define LOGINFO1(x,y)  if(_PM25LOGLEVEL_>2) { _debugSerial->print("[PM25] "); _debugSerial->print(x); _debugSerial->print(" "); _debugSerial->println(y); }

#define LOGDEBUGHEX(x)	 if(_PM25LOGLEVEL_>3) { if(x<16){_debugSerial->print('0');}_debugSerial->print(x, HEX);}
#define LOGDEBUGLN()     if(_PM25LOGLEVEL_>3) { _debugSerial->println(); }
#define LOGDEBUG(x)      if(_PM25LOGLEVEL_>3) { _debugSerial->println(x); }
#define LOGDEBUG0(x)     if(_PM25LOGLEVEL_>3) { _debugSerial->print(x); }
#define LOGDEBUG1(x,y)   if(_PM25LOGLEVEL_>3) { _debugSerial->print(x); _debugSerial->print(" "); _debugSerial->println(y); }
#define LOGDEBUG2(x,y,z) if(_PM25LOGLEVEL_>3) { _debugSerial->print(x); _debugSerial->print(" "); _debugSerial->print(y); _debugSerial->print(" "); _debugSerial->println(z); }


#endif
