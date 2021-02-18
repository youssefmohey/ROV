//
// Created by Youssef on 2/18/2021.
//
void fun()
{
    char command =Serial.read();
    if(command>>7==1)
        other();
   //movement command
    else
    {
        int direction;
        //no speed
        if (command >> 4 == 7)
        {
            direction = command & 15;
            move(direction);
        }
        //with speed
        else
        {
            direction = command & 7;
            int speed = command >> 4;
            speed *=50;
            move(direction,speed);
        }
    }
}
void move(int direction ,int speed=-1)
{
    if(speed ==-1)
        movementsWithoutSpeed(direction);
    else
        movementsWithSpeed(direction,speed);
}
void movementsWithoutSpeed(int direction)
{
    /**
     * 0-> Stop
     * 7-> Rotate Vertical Right
     * 8-> Rotate Vertical Left
     * 9-> Rotate Horizontal Right
     * 10-> Rotate Horizontal Left
     */
    switch () (direction)
    {
        case 0:
            _motors.stop();
            break;
        case 7:
            _motors.turnRightAboutY_Axis(_speed);
            break;
        case 8:
            _motors.turnLeftAboutY_Axis(_speed);
            break;
        case 9:
            _motors.turnForwardAboutX_Axis(_speed);
            break;
        case 10:
            _motors.turnBackwardAboutX_Axis(_speed);
            break;
    }
}
void movementsWithSpeed(int direction,int speed)
{
    /**
     * 1-> UP
     * 2-> Down
     * 3-> Forward
     * 4-> Backward
     * 5-> Right
     * 6-> Left
     */
    switch (direction)
    {
        case 1:
            _motors.upwards(speed);
            break;
        case 2:
            _motors.downwards(speed);
            break;
        case 3:
            _motors.forward(speed);
            break;
        case 4:
            _motors.backward(speed);
            break;
        case 5:
            _motors.turnRight(speed);
            break;
        case 6:
            _motors.turnLeft(_speed);
    }
}