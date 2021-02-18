#ifndef UNTITLED1_MOVEMENTS_H
#define UNTITLED1_MOVEMENTS_H

#endif //UNTITLED1_MOVEMENTS_H
#include "Arduino.h"
#include <Servo.h>
class movements
{
public:
    const int maxHorizontalPWM=270;
    const int maxVertical_V1_V2_PWM=300;
    const int maxVertical_V3_PWM=230;
    //movements(int pins[]);
    void setPins(int pins[]);
    void forward(int speed);
    void backward(int speed);
    void right(int speed);
    void left(int speed);
    void turnRight(int speed);
    void turnLeft(int speed);
    void downwards(int speed);
    void upwards(int speed);
    void turnForwardAboutX_Axis(int speed);
    void turnBackwardAboutX_Axis(int speed);
    void turnRightAboutY_Axis(int speed);
    void turnLeftAboutY_Axis(int speed);
    void stop();
private:
    Servo _l1,_l2,_r1,_r2,_v1,_v2,_v3;
    Servo* _motors[7]={&_l1,&_l2,&_r1,&_r2,&_v1,&_v2,&_v3};
    const int _numberOfMotors=7;
};


