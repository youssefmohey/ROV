//
// Created by Youssef on 1/22/2021.
//
#include "Rov.h"

Rov::Rov()
{
    int motorPins[]={l1,l2,r1,r2,v1,v2,v3};
    _motors.setPins(motorPins);
    SPI.begin(); //see SPI library details on arduino.cc for details
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV32); //divide 16 MHz to communicate on 500 kHz
    pinMode(clock, OUTPUT);
    pinMode(leakageSensor,INPUT);
}
void Rov::run()
{
    //sending sensors reading if the reading changed to serial
    _sensors();
    //if the motors directions & speed sent in serial
    if(Serial.available())
        _readingCommands();
}
void Rov::_readingCommands()
{
    char command =Serial.read();
    if(command>>7==1);
    //movement command
    else
    {
        int direction=command & 15;
        int speed = command >> 4;
        speed *=50;
        _movementsWithSpeed(direction,speed);
    }
}

void Rov::_movementsWithSpeed(int direction,int speed)
{
    /**
     * 0-> Stop
     * 1-> Forward
     * 2-> backward
     * 3-> right
     * 4-> left
     * 5-> turnRight
     * 6-> turnLeft
     * 7-> downwards
     * 8-> upwards
     * 9-> turnForwardAboutX_Axis
     * 10-> turnBackwardAboutX_Axis
     * 11-> turnRightAboutY_Axis
     * 12-> turnLeftAboutY_Axis
     */
    
    if(speed==_previousSpeed&&direction==_previousDirection)
        return;
    if(_previousDirection!=direction)
        _motors.stop();
    _previousDirection=direction;
    _previousSpeed=speed;
    switch (direction)
    {
        case 0:
            _motors.stop();
            break;
        case 1:
            _motors.forward(speed);
            break;
        case 2:
            _motors.backward(speed);
            break;
        case 3:
            _motors.right(speed);
            break;
        case 4:
            _motors.left(speed);
            break;
        case 5:
            _motors.turnRight(speed);
            break;
        case 6:
            _motors.turnLeft(speed);
            break;
        case 7:
            _motors.downwards(speed);
            break;
        case 8:
            _motors.upwards(speed);
            break;
        case 9:
            _motors.turnForwardAboutX_Axis(speed);
            break;
        case 10:
            _motors.turnBackwardAboutX_Axis(speed);
            break;
        case 11:
            _motors.turnRightAboutY_Axis(speed);
            break;
        case 12:
            _motors.turnLeftAboutY_Axis(speed);
            break;
    }
}
//this function is responsible for sending sensors values in serial if the values changed
void Rov::_sensors()
{
    /*if(_leak())
        Serial.println("leak");*/
    _tempAndPressure(_pressure,_temp);
    if(_previousPressure!=_pressure)
    {
        Serial.println("pressure");
        Serial.println(_pressure);
        _previousPressure=_pressure;
    }
    if(_previousTemp!=_temp)
    {
        Serial.println("temp");
        Serial.println(_temp);
        _previousTemp=_temp;
    }
}
bool Rov::_leak()
{

    if(digitalRead(leakageSensor)==HIGH)
        return true;
    return false;
}
void Rov::_resetSensor() //this function keeps the sketch a little shorter
{
    SPI.setDataMode(SPI_MODE0);
    SPI.transfer(0x15);
    SPI.transfer(0x55);
    SPI.transfer(0x40);
}
unsigned int Rov::_Calibration(unsigned int secondByte)
{
    unsigned int word1 = 0;
    unsigned int word11 = 0;
    SPI.transfer(0x1D); //send first byte of command to get calibration word 1
    SPI.transfer(secondByte); //send second byte of command to get calibration word 1
    SPI.setDataMode(SPI_MODE1); //change mode in order to listen
    word1 = SPI.transfer(0x00); //send dummy byte to read first byte of word
    word1 = word1 << 8; //shift returned byte
    word11 = SPI.transfer(0x00); //send dummy byte to read second byte of word
    word1 = word1 | word11; //combine first and second byte of word
    _resetSensor();//resets the sensor
    return word1;
}
void Rov::_tempAndPressure(long &pressure,float& temp)
{
    TCCR1B = (TCCR1B & 0xF8) | 1 ; //generates the MCKL signal
    analogWrite (clock, 128) ;
    _resetSensor();//resets the sensor - caution: afterwards mode = SPI_MODE0!
//Calibration word 1
    unsigned int word1 = _Calibration(0x50);
//Calibration word 2; see comments on calibration word 1
    unsigned int word2 = _Calibration(0x60);
//Calibration word 3; see comments on calibration word 1
    unsigned int word3 = _Calibration(0x90);
//Calibration word 4; see comments on calibration word 1
    unsigned int word4 = _Calibration(0xA0);
    long c1 = word1 >> 1;
    long c2 = ((word3 & 0x3F) << 6) | ((word4 & 0x3F));
    long c3 = (word4 >> 6) ;
    long c4 = (word3 >> 6);
    long c5 = (word2 >> 6) | ((word1 & 0x1) << 10);
    long c6 = word2 & 0x3F;
    _resetSensor();//resets the sensor
//Temperature:
    unsigned int tempMSB = 0; //first byte of value
    unsigned int tempLSB = 0; //last byte of value
    unsigned int D2 = 0;
    SPI.transfer(0x0F); //send first byte of command to get temperature value
    SPI.transfer(0x20); //send second byte of command to get temperature value
    delay(35); //wait for conversion end
    SPI.setDataMode(SPI_MODE1); //change mode in order to listen
    tempMSB = SPI.transfer(0x00); //send dummy byte to read first byte of value
    tempMSB = tempMSB << 8; //shift first byte
    tempLSB = SPI.transfer(0x00); //send dummy byte to read second byte of value
    D2 = tempMSB | tempLSB; //combine first and second byte of value
    _resetSensor();//resets the sensor
//Pressure:
    unsigned int presMSB = 0; //first byte of value
    unsigned int presLSB =0; //last byte of value
    unsigned int D1 = 0;
    SPI.transfer(0x0F); //send first byte of command to get pressure value
    SPI.transfer(0x40); //send second byte of command to get pressure value
    delay(35); //wait for conversion end
    SPI.setDataMode(SPI_MODE1); //change mode in order to listen
    presMSB = SPI.transfer(0x00); //send dummy byte to read first byte of value
    presMSB = presMSB << 8; //shift first byte
    presLSB = SPI.transfer(0x00); //send dummy byte to read second byte of value
    D1 = presMSB | presLSB;
    const long UT1 = (c5 * 8) + 20224;
    const long dT =(D2 - UT1);
    const long TEMP = 200 + ((dT * (c6 + 50))/1024);
    const long OFF = (c2*4) + (((c4 - 512) * dT)/4096);
    const long SENS = c1 + ((c3 * dT)/1024) + 24576;
    long PCOMP = ((((SENS * (D1 - 7168))/16384)- OFF)/32)+250;
    float TEMPREAL = TEMP/10;
    /*Serial.println("pressure");
    Serial.println(PCOMP);
    //Serial.println(" mbar");*/
    const long dT2 = dT - ((dT >> 7 * dT >> 7) >> 3);
    const float TEMPCOMP = (200 + (dT2*(c6+100) >>11))/10;
    /*Serial.println("temperature");
    Serial.println(TEMPCOMP);
    Serial.println(" °C");*/
    pressure=PCOMP;
    temp=TEMPCOMP;

    //delay(1000);
}
