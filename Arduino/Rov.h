//
// Created by Youssef on 1/22/2021.
//
#ifndef UNTITLED2_ROV_H
#define UNTITLED2_ROV_H

#include "Arduino.h"
#include "movements.h"
#include <SPI.h>
#define leakageSensor 2
#define clock 9
#define l1 3
#define l2 4
#define r1 5
#define r2 6
#define v1 7
#define v2 8
#define v3 10
class Rov
{
public:
    Rov();
    void run();
private:
    float _temp=0;
    float _previousTemp=0;
    long _pressure=0;
    long _previousPressure=0;
    int _previousDirection=-1;
    movements _motors;
    bool _leak();
    unsigned int _Calibration(unsigned int secondByte);
    void _resetSensor();
    void _tempAndPressure(long &pressure,float& temp);
    void _sensors();
    void _readingCommands();
    //void _move();
    //void _movementsWithoutSpeed(int direction);
    void _movementsWithSpeed(int direction,int speed);

};



#endif //UNTITLED2_ROV_H
