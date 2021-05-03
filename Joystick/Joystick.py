import pygame
import time
import serial

arduino = serial.Serial('COM4',9600) # cahnge '/dev/ttyACM0' to the port the arduino connected to it 
time.sleep(2) #wait for 2 secounds for the communication to get established
#print (arduino.readline())

currentSpeed = 1
currentDirection = 0
pressedButton = -1
prevHat = 0

def initialize(joyStickName):
    joystick_count = pygame.joystick.get_count()
    for j in range(joystick_count):
        joystick = pygame.joystick.Joystick(j)
        name = joystick.get_name()
        if name == joyStickName:
            joystick.init()
            return joystick
    print("No joystick found")
    pass


def button(joystick, buttonsNum):
    global pressedButton
    global currentDirection
    for i in range(buttonsNum):
        button = joystick.get_button(i)
        if button == 1:
            if i == 0:
                # send command to stop
                pressedButton = i
                currentDirection = 0
                print("Stop")
                sendingMovement(0, 0)
            print("Button {} pressed".format(i))
            # this function having problem


def hat(joystick, hatNum):
    # there is problem in joystick hat
    global prevHat
    dir = 0
    for i in range(hatNum):
        hat = joystick.get_hat(i)
        #print('hat:', hat[1])
        if hat[1] == -1:
            dir = 7
        elif hat[1] == 1:
            dir = 8
        else:
            dir = 0
    if prevHat != dir:
        prevHat = dir
        sendingMovement(currentSpeed, dir)


def axis(joystick, axesNum):

    global currentSpeed
    global currentDirection

    direction = 0
    speed = -1

    axis0 = -0.0078125
    axis1 = -0.0078125
    axis3 = -0.0078125

    for i in range(axesNum):
        axis = joystick.get_axis(i)
        if i == 2:
            speed = -1 * axis + 1
            speed = int(speed / 2.0 * 6.0)
            # print("speed: ", speed)

        elif axis != -0.0078125:  # axis < -0.2 or axis > 0.2:
            #print("Axis "+str(i)+ " "+str(axis))
            if i == 0:
                axis0 = axis
            elif i == 1:
                axis1 = axis
            elif i == 3:
                axis3 = axis

    if axis0 == -0.0078125 and axis1 == -0.0078125 and axis3 == -0.0078125:
        direction = 0
        # print("stop")
    elif axis3 > -0.0078125:
        direction = 5
        # print("turn around itself right "+str(speed))
    elif axis3 < -0.0078125:
        direction = 6
        # print("turn around itself left "+str(speed))
    elif axis1 <= -0.4:
        direction = 1
        # print("forward " + str(speed))
    elif axis1 > 0.4:
        direction = 2
        # print("backward " + str(speed))
    elif axis0 > -0.0078125:
        direction = 3
        # print("right "+str(speed))
    elif axis0 < -0.0078125:
        direction = 4
        # print("left "+str(speed))


    if direction != currentDirection or speed != currentSpeed:
        currentDirection = direction
        currentSpeed = speed
        print("sending command : " + str(direction) + " " + str(speed))
        sendingMovement(currentSpeed, currentDirection)

def sendingMovement(speed,dir):
    data = speed << 4
    print("python direction: " + str(dir))
    print("python speed: " + str(speed))
    data = data | dir
    print("data send to arduino:", data)
    data = data.to_bytes(1, 'big')

    # arduino.write(data)
    # print(arduino.read(1))

# main
pygame.init()
pygame.joystick.init()

pygame.display.set_caption('JoyStick')
surface = pygame.display.set_mode((800, 600))
clock = pygame.time.Clock()
done = True
font = pygame.font.Font(None, 20)
linesize = font.get_linesize()

joyStick = initialize("5-Axis,12-Button with POV")
buttonsNum = joyStick.get_numbuttons()
axesNum = joyStick.get_numaxes()
hatNum = joyStick.get_numhats()
while done:
    # wait until any change(input) in joystick
    for event in pygame.event.get():  # User did something.
        if event.type == pygame.QUIT:  # If user clicked close.
            done = False  # Flag that we are done so we exit this loop.
        elif event.type == pygame.JOYBUTTONDOWN:
            print("Joystick button pressed.")
            button(joyStick, buttonsNum)
        elif event.type == pygame.JOYBUTTONUP:
            if pressedButton == 0:
                axis(joyStick, axesNum)
                pressedButton = -1
            print("Joystick button released.")
        elif event.type == pygame.JOYAXISMOTION:
            # print("axis")
            axis(joyStick, axesNum)
        elif event.type == pygame.JOYHATMOTION:
            print("hat")
            hat(joyStick, hatNum)

    surface.fill((0, 0, 0))
    pygame.display.flip()
    clock.tick(20)
    '''if arduino.in_waiting:
                while arduino.in_waiting:
                    print(arduino.readline())'''
