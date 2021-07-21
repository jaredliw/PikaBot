#ifndef PikaBot_h
#define PikaBot_h

#include <Arduino.h>
#include <pitches.h>

enum Duration
{
    WHOLE,
    HALF,
    QUARTER,
    EIGHTH,
    SIXTEENTH,
    DOUBLE,
    BREVE,
};

enum IR
{
    LEFTIR,
    RIGHTIR,
};

int pitchToFreq(String pitch);

class PikaBot
{
public:
    PikaBot(void);
    uint16_t tempo = 120;
    void calibrateMotors(uint8_t speed, uint16_t delay, uint8_t distance);
    bool detectLine(IR sensor);
    bool isPressed();
    void lineFollow(uint8_t speed);
    void move(int16_t leftSpeed, int16_t rightSpeed);
    void moveBackward(uint8_t speed);
    void moveBackward(uint8_t speed, uint8_t distance);
    void moveForward(uint8_t speed);
    void moveForward(uint8_t speed, uint8_t distance);
    void playTone(uint16_t freq, unsigned long note);
    void setTempo(uint8_t tempo);
    void stop();
    void turnLeft(uint8_t speed);
    void turnLeft(uint8_t speed, uint8_t angle);
    void turnRight(uint8_t speed);
    void turnRight(uint8_t speed, uint8_t angle);
    uint16_t ultrasonicDistance();

private:
    uint16_t _delayRef = 500;
    uint8_t _distanceRef = 25;
    uint8_t _speedRef = 255;
    unsigned long lastMotorInstructionTime = 0;
    void _delayMotors(uint8_t speed, double distance);
};

#endif
