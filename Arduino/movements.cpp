//
// Created by Youssef on 1/17/2021.
//
#include"movements.h"

/**
 * red +ve
 * black -ve
 * up +ve
 * down -ve
 */
#define red 1
#define black -1
#define up 1
#define down -1
#define CENTER_THROTTLE 1500
// this function is responsible for setting the motors pins and give it the CENTER_THROTTLE value
void movements::setPins(int pins[])
{
    for(int i=0;i<_numberOfMotors;i++)
    {
        _motors[i]->attach(pins[i]);
        _motors[i]->writeMicroseconds(CENTER_THROTTLE);
    }
}
//this function is responsible for forward movement 
void movements::forward(int speed)
{
    /**
     * _l1->red
     * _l2->red
     * _r1->red
     * _r2->red
     */
	speed=min(speed,maxHorizontalPWM);
    int speedRed=CENTER_THROTTLE+red*speed;
    _l1.writeMicroseconds(speedRed);
    _l2.writeMicroseconds(speedRed);
    _r1.writeMicroseconds(speedRed);
    _r2.writeMicroseconds(speedRed);
}
void movements::backward(int speed)
{
    /**
     * _l1->black
     * _l2->black
     * _r1->black
     * _r2->black
     */
    speed=min(speed,maxHorizontalPWM);
    int speedBlack=CENTER_THROTTLE+black*speed;
    _l1.writeMicroseconds(speedBlack);
    _l2.writeMicroseconds(speedBlack);
    _r1.writeMicroseconds(speedBlack);
    _r2.writeMicroseconds(speedBlack);
}
void movements::right(int speed)
{
    /**
     * _l1->red
     * _l2->black
     * _r1->black
     * _r2->red
     */
    speed=min(speed,maxHorizontalPWM);
    int speedRed=CENTER_THROTTLE+red*speed;
    int speedBlack=CENTER_THROTTLE+black*speed;
    _l1.writeMicroseconds(speedRed);
    _l2.writeMicroseconds(speedBlack);
    _r1.writeMicroseconds(speedBlack);
    _r2.writeMicroseconds(speedRed);
}
void movements::left(int speed)
{
    /**
     * _l1->black
     * _l2->red
     * _r1->red
     * _r2->black
     */
    speed=min(speed,maxHorizontalPWM);
    int speedRed=CENTER_THROTTLE+red*speed;
    int speedBlack=CENTER_THROTTLE+black*speed;
    _l1.writeMicroseconds(speedBlack);
    _l2.writeMicroseconds(speedRed);
    _r1.writeMicroseconds(speedRed);
    _r2.writeMicroseconds(speedBlack);
}
void movements::turnRight(int speed)
{
    /**
     * _l1->red
     * _l2->red
     * _r1->black
     * _r2->black
     */
    speed=min(speed,maxHorizontalPWM);
    int speedRed=CENTER_THROTTLE+red*speed;
    int speedBlack=CENTER_THROTTLE+black*speed;
    _l1.writeMicroseconds(speedRed);
    _l2.writeMicroseconds(speedRed);
    _r1.writeMicroseconds(speedBlack);
    _r2.writeMicroseconds(speedBlack);
}
void movements::turnLeft(int speed)
{
    /**
     * _l1->black
     * _l2->black
     * _r1->red
     * _r2->red
     */
    speed=min(speed,maxHorizontalPWM);
    int speedRed=CENTER_THROTTLE+red*speed;
    int speedBlack=CENTER_THROTTLE+black*speed;
    _l1.writeMicroseconds(speedBlack);
    _l2.writeMicroseconds(speedBlack);
    _r1.writeMicroseconds(speedRed);
    _r2.writeMicroseconds(speedRed);
}
void movements::upwards(int speed)
{
    /**
     * _v1->up
     * _v2->up
     */
    speed=min(speed,maxVertical_V1_V2_PWM);
    int speedUp=CENTER_THROTTLE+up*speed;
    _v1.writeMicroseconds(speedUp);
    _v2.writeMicroseconds(speedUp);
}
void movements::downwards(int speed)
{
    /**
     * _v1->down
     * _v2->down
     */
    speed=min(speed,maxVertical_V1_V2_PWM);
    int speedDown=CENTER_THROTTLE+down*speed;
    _v1.writeMicroseconds(speedDown);
    _v2.writeMicroseconds(speedDown);
}
void movements::turnForwardAboutX_Axis(int speed)
{
    /**
     * _v3->up
     */
    speed=min(speed,maxVertical_V3_PWM);
    int speedUp=CENTER_THROTTLE+up*speed;
    _v3.writeMicroseconds(speedUp);
}
void movements::turnBackwardAboutX_Axis(int speed)
{
    /**
     * _v3->down
     */
    speed=min(speed,maxVertical_V3_PWM);
    int speedDown=CENTER_THROTTLE+down*speed;
    _v3.writeMicroseconds(speedDown);
}
void movements::turnRightAboutY_Axis(int speed)
{
    /**
     * _v1->up
     * _v2->down
     */
    speed=min(speed,maxVertical_V1_V2_PWM);
    int speedDown=CENTER_THROTTLE+down*speed;
    int speedUp=CENTER_THROTTLE+up*speed;
    _v1.writeMicroseconds(speedUp);
    _v2.writeMicroseconds(speedDown);
}
void movements::turnLeftAboutY_Axis(int speed)
{
    /**
     * _v1->down
     * _v2->up
     */
    speed=min(speed,maxVertical_V1_V2_PWM);
    int speedDown=CENTER_THROTTLE+down*speed;
    int speedUp=CENTER_THROTTLE+up*speed;
    _v1.writeMicroseconds(speedDown);
    _v2.writeMicroseconds(speedUp);
}
//this function is responsible for stopping all the motors
void movements::stop()
{
    for (int i = 0; i < _numberOfMotors; i++)
        _motors[i]->writeMicroseconds(CENTER_THROTTLE);
}