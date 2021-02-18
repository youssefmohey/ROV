//
// Created by Youssef on 1/22/2021.
//
#ifndef UNTITLED2_ROV_H
#define UNTITLED2_ROV_H

#include "Arduino.h"
#include "movements.h"
#include <SPI.h>
class Rov
{
public:
    Rov();
    void run();
private:

    bool _move=false;
    float _temp=0;
    float _previousTemp=0;
    long _pressure=0;
    long _previousPressure=0;
    movements _motors;
    String _previousCommand="";
    String _command="";
    float _speed=-1;
    float _previousSpeed=-1;
    bool _leak();
    unsigned int _Calibration(unsigned int secondByte);
    float _speedValues(float speed);
    void _movementsCommands();
    void _resetSensor();
    void _tempAndPressure(long &pressure,float& temp);
    void _sensors();
    void _readingMovements();

};



#endif //UNTITLED2_ROV_H
