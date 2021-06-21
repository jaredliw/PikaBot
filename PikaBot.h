#ifndef PikaBot_h
#define PikaBot_h

#include <Arduino.h>

enum IR
{
    LeftIR,
    RightIR,
};

class PikaBot
{
public:
    PikaBot(void);
    void calibrateMotors(uint8_t speed, uint16_t delay, uint8_t distance);
    bool detectLine(IR sensor);
    bool isPressed();
    void lineFollow();
    void move(int16_t leftSpeed, int16_t rightSpeed);
    void moveBackward(uint8_t speed, uint8_t distance);
    void moveForward(uint8_t speed, uint8_t distance);
    void stop();
    void turnLeft(uint8_t speed);
    void turnRight(uint8_t speed);
    uint16_t ultrasonicDistance();

private:
    uint16_t _delayRef = 500;
    uint8_t _distanceRef = 25;
    uint8_t _speedRef = 255;
    void _delayMotors(uint8_t speed, uint8_t distance);
};

#endif
