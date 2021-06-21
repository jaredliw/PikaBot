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
    bool detectLine(IR sensor);
    bool isPressed();
    void lineFollow();
    void move(int16_t leftSpeed, int16_t rightSpeed);
    void moveBackward(uint8_t speed);
    void moveForward(uint8_t speed);
    void stop();
    void turnLeft(uint8_t speed);
    void turnRight(uint8_t speed);
    uint16_t ultrasonicDistance();
};

#endif
