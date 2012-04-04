/**
 * AquaControllerSerial controls the AquaControllers and gathers stats via serial connection
 */
#ifndef AquaControllerSerial_h
#define AquaControllerSerial_h

#include "Arduino.h"

class AquaControllerSerial
{
  public:
    AquaControllerSerial(HardwareSerial &_aquaControllerSerial);
    char * getTime();
    float getTemp();
    float getPh();
    int getOrp();
    boolean getBatteryStatus();
    boolean getHasPower();

    boolean getLT1State();
    char * getLT1Mode();
    boolean setLT1State();
    boolean setLT1Mode();

    boolean getLT2State();
    char * getLT2Mode();
    boolean setLT2State();
    boolean setLT2Mode();

    boolean getPM1State();
    char * getPM1Mode();
    boolean setPM1State();
    boolean setPM1Mode();

    boolean getPM2State();
    char * getPM2Mode();
    boolean setPM2State();
    boolean setPM2Mode();

    boolean getHETState();
    char * getHETMode();
    boolean setHETState();
    boolean setHETMode();

    boolean getCOLState();
    char * getCOLMode();
    boolean setCOLState();
    boolean setCOLMode();

    boolean getOZNState();
    char * getOZNMode();
    boolean setOZNState();
    boolean setOZNMode();

    boolean getC02State();
    char * getC02Mode();
    boolean setC02State();
    boolean setC02Mode();

    boolean getALMState();
    char * getALMMode();
    boolean setALMState();
    boolean setALMMode();



  private:
    HardwareSerial* aquaControllerSerial;
    void init();
    void update();
    void processTime(char * dataBuff);
    void processProbeData(char * dataBuff);
    void processTimer(int * timer, char * dataBuff);
    void processPowerFailed(char * dataBuff);
    void processPowerRestored(char * dataBuff);
    void processBatteryStatus(char * dataBuff);
    long _updateInterval;
    unsigned long _updateTime;
    char _time[16];
    float _temp;
    float _ph;
    int _orp;
    char _pwrFailed;
    char _pwrReset;
    int _battStatus;
    int _lt1[2];
    int _lt2[2];
    int _pm1[2];
    int _pm2[2];
    int _het[2];
    int _col[2];
    int _ozn[2];
    int _c02[2];
    int _alm[2];
};

#endif