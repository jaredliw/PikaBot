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
    void lineFollow();
    uint16_t ultrasonicDistance();
};

#endif
