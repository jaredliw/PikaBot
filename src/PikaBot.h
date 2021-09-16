#ifndef PikaBot_h
#define PikaBot_h

#include <Arduino.h>

enum Duration
{
    WHOLE = 1,
    HALF = 2,
    QUARTER = 4,
    EIGHTH = 8,
    SIXTEENTH = 16,
    DOUBLE = 32,
    BREVE = 64,
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
    int tempo = 120;
    void calibrateMotors(int speed, int delay, int distance);
    bool detectLine(IR sensor);
    bool isPressed();
    void lineFollow(int speed);
    void move(int leftSpeed, int rightSpeed);
    void moveBackward(int speed);
    void moveBackward(int speed, int distance);
    void moveForward(int speed);
    void moveForward(int speed, int distance);
    void play(String musicSheet);
    void playTone(String pitch, int note);
    void playToneMs(String pitch, long duration);
    void resetTempo();
    void stop();
    void turnLeft(int speed);
    void turnLeft(int speed, int angle);
    void turnRight(int speed);
    void turnRight(int speed, int angle);
    int ultrasonicDistance();

private:
    int _delayRef = 500;
    int _distanceRef = 25;
    int _speedRef = 255;
    unsigned long lastMotorInstructionTime = 0;
    void _delayMotors(int speed, double distance);
};

#endif
