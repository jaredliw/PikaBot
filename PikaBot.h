#ifndef PikaBot_h
#define PikaBot_h

#include <Arduino.h>
#include <stdint.h>

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
};

#endif
