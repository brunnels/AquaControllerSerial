/**
 * AquaControllerSerial controls the AquaControllers and gathers stats via serial connection
 */

#include "Arduino.h"
#include "AquaControllerSerial.h"

AquaControllerSerial::AquaControllerSerial(HardwareSerial &_aquaControllerSerial)
{
  aquaControllerSerial = &_aquaControllerSerial;

  // Keep the rest of the initialization process in a separate method in case
  // we overload the constructor.
  init();
}

void AquaControllerSerial::init()
{
  aquaControllerSerial->begin(9600);
  _updateInterval = 1000;
  _updateTime = millis() - (_updateInterval + 5);
}

char * AquaControllerSerial::getTime()
{
  update();
  return _time;
}

float AquaControllerSerial::getTemp()
{
  update();
  return _temp;
}

float AquaControllerSerial::getPh()
{
  update();
  return _ph;
}

int AquaControllerSerial::getOrp()
{
  update();
  return _orp;
}

boolean AquaControllerSerial::getBatteryStatus(){}
boolean AquaControllerSerial::getHasPower(){}

boolean AquaControllerSerial::getLT1State()
{
  return _lt1[0];
}

char * AquaControllerSerial::getLT1Mode()
{
  if(_lt1[1] == 0) {
    return "Auto";
  }
  else {
    return "Manual";
  }
}

boolean AquaControllerSerial::setLT1State(){}
boolean AquaControllerSerial::setLT1Mode(){}

boolean AquaControllerSerial::getLT2State()
{
  return (int)_lt2[0];
}

char * AquaControllerSerial::getLT2Mode()
{
  if(_lt2[1] == 0) {
    return "Auto";
  }
  else {
    return "Manual";
  }
}

boolean AquaControllerSerial::setLT2State(){}
boolean AquaControllerSerial::setLT2Mode(){}

boolean AquaControllerSerial::getPM1State(){
  return _pm1[0];
}

char * AquaControllerSerial::getPM1Mode()
{
  if(_pm1[1] == 0) {
    return "Auto";
  }
  else {
    return "Manual";
  }
}

boolean AquaControllerSerial::setPM1State(){}
boolean AquaControllerSerial::setPM1Mode(){}

boolean AquaControllerSerial::getPM2State()
{
  return _pm2[0];
}

char * AquaControllerSerial::getPM2Mode()
{
  if(_pm2[1] == 0) {
    return "Auto";
  }
  else {
    return "Manual";
  }
}

boolean AquaControllerSerial::setPM2State(){}
boolean AquaControllerSerial::setPM2Mode(){}

boolean AquaControllerSerial::getHETState()
{
  return _het[0];
}

char * AquaControllerSerial::getHETMode()
{
  if(_het[1] == 0) {
    return "Auto";
  }
  else {
    return "Manual";
  }
}

boolean AquaControllerSerial::setHETState(){}
boolean AquaControllerSerial::setHETMode(){}

boolean AquaControllerSerial::getCOLState()
{
  return _col[0];
}

char * AquaControllerSerial::getCOLMode()
{
  if(_col[1] == 0) {
    return "Auto";
  }
  else {
    return "Manual";
  }
}

boolean AquaControllerSerial::setCOLState(){}
boolean AquaControllerSerial::setCOLMode(){}

boolean AquaControllerSerial::getOZNState(){
  return _ozn[0];
}

char * AquaControllerSerial::getOZNMode()
{
  if(_ozn[1] == 0) {
    return "Auto";
  }
  else {
    return "Manual";
  }
}

boolean AquaControllerSerial::setOZNState(){}
boolean AquaControllerSerial::setOZNMode(){}

boolean AquaControllerSerial::getC02State()
{
  return _c02[0];
}

char * AquaControllerSerial::getC02Mode()
{
  if(_c02[1] == 0) {
    return "Auto";
  }
  else {
    return "Manual";
  }
}

boolean AquaControllerSerial::setC02State(){}
boolean AquaControllerSerial::setC02Mode(){}

boolean AquaControllerSerial::getALMState()
{
  return _alm[0];
}

char * AquaControllerSerial::getALMMode()
{
  if(_alm[1] == 0) {
    return "Auto";
  }
  else {
    return "Manual";
  }
}
boolean AquaControllerSerial::setALMState(){}
boolean AquaControllerSerial::setALMMode(){}

void AquaControllerSerial::AquaControllerSerial::update()
{
  if(millis() - _updateTime > _updateInterval) {
    int retCnt = 0, i = 0, wait = 0;
    char c, dataBuff[33];
    memset(dataBuff, '\0', 33);

    aquaControllerSerial->println("c");

    while(retCnt != 19) {
      if (aquaControllerSerial->available()) {
        c = aquaControllerSerial->read();
        if(retCnt > 2 && retCnt < 18  && retCnt != 4 && c != '\n') {
          dataBuff[i++] = c;
        }

        if(c == '\n') {
          if(retCnt > 2 && retCnt < 18  && retCnt != 4) {
            switch(retCnt) {
              // time
              case 3:
                processTime(dataBuff);
                break;

              // temp ph orp
              case 5:
                processProbeData(dataBuff);
                break;

              // LT1
              case 6:
                processTimer(_lt1, dataBuff);
                break;

              // LT2
              case 7:
                processTimer(_lt2, dataBuff);
                break;

              // PM1
              case 8:
                processTimer(_pm1, dataBuff);
                break;

              // PM2
              case 9:
                processTimer(_pm2, dataBuff);
                break;

              // HET
              case 10:
                processTimer(_het, dataBuff);
                break;

              // COL
              case 11:
                processTimer(_col, dataBuff);
                break;

              // OZN
              case 12:
                processTimer(_ozn, dataBuff);
                break;

              // C02
              case 13:
                processTimer(_c02, dataBuff);
                break;

              // ALM
              case 14:
                processTimer(_alm, dataBuff);
                break;

              // Power Failed
              case 15:
  //              Serial.println(dataBuff);
                break;

              // Power Restored
              case 16:
  //              Serial.println(dataBuff);
                break;

              // Battery
              case 17:
                //Serial.println(dataBuff);
                break;
            }

            //clear the buffer
            memset(dataBuff,'\0',33);
          }

          i = 0;
          retCnt++;
        }
      }
      else if(wait < 100){
        delay(1);
        wait++;
      }

      _updateTime = millis();
    }
  }
}

void AquaControllerSerial::processTime(char * dataBuff)
{
  strncpy(_time, dataBuff, 15);
  _time[15] = '\0';
}

void AquaControllerSerial::processProbeData(char * dataBuff)
{
  char tempStr[5];
  char phStr[5];
  char orpStr[4];
  strncpy(tempStr, dataBuff, 4);
  tempStr[4] = '\0';
  _temp = atof(tempStr);

  strncpy(phStr, dataBuff + 5, 4);
  phStr[4] = '\0';
  _ph = atof(phStr);

  strncpy(orpStr, dataBuff + 10, 3);
  orpStr[3] = '\0';
  _orp = atoi(orpStr);
}

void AquaControllerSerial::processTimer(int * timer, char * dataBuff)
{
  char * pch;
  int pwr;
  int cntrl;

  if(pch = strstr (dataBuff, "ON")) {
    pwr = 1;
  }
  else if(pch = strstr (dataBuff,"OFF")) {
    pwr = 0;
  }

  if(pch = strstr (dataBuff,"Auto")) {
    cntrl = 0;
  }
  else if(pch = strstr (dataBuff,"Manual")) {
    cntrl = 1;
  }

  timer[0] = pwr;
  timer[1] = cntrl;
}

void AquaControllerSerial::processPowerFailed(char * dataBuff)
{

}

void AquaControllerSerial::processPowerRestored(char * dataBuff)
{

}

void AquaControllerSerial::processBatteryStatus(char * dataBuff)
{

}