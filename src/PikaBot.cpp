#include "PikaBot.h"

#define BUTTON 2
#define BUZZER 8
#define LEFT_FORWARD 11
#define LEFT_BACKWARD 10
#define RIGHT_FORWARD 9
#define RIGHT_BACKWARD 3
#define ULTRASONIC_TRIG 5
#define ULTRASONIC_ECHO 4
#define LEFT_IR A0
#define RIGHT_IR A1

#define DELAY 50
#define WIDTH 15

int pitchToFreq(String pitch)
{
    auto l = pitch.length();
    if (l < 1 || l > 3)
    {
        return -1;
    }
    String firstChar = pitch.substring(0, 1);
    firstChar.toUpperCase();
    pitch = firstChar + pitch.substring(1);
    if (pitch.equals("R"))
    {
        return 0;
    }
    const String pitches[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    int octave;
    int lastCharPos = l - 1;
    if (isDigit(pitch[lastCharPos]))
    {
        octave = String(pitch[lastCharPos]).toInt();
        pitch = pitch.substring(0, lastCharPos);
        if (0 > octave || octave > 8)
        {
            return -1;
        }
    }
    else
    {
        octave = 4;
    }
    const String replaceWith[] = {"Db", "C#", "Eb", "D#", "Gb", "F#", "Ab", "G#", "Bb", "A#"};
    for (int i = 0; i < 10; i += 2)
    {
        if (replaceWith[i] == pitch)
        {
            pitch = replaceWith[i + 1];
        }
    }
    for (int idx = 0; idx < 12; idx++)
    {
        if (pitches[idx].equals(pitch))
        {
            int freq = round(27.5 * pow(2, (double) (12 * octave + idx - 9) / 12));
            return freq;
        }
    }
    return -1;
}

PikaBot::PikaBot(void)
{
    pinMode(BUTTON, INPUT_PULLUP);
    pinMode(BUZZER, OUTPUT);
    pinMode(LEFT_FORWARD, OUTPUT);
    pinMode(LEFT_BACKWARD, OUTPUT);
    pinMode(RIGHT_FORWARD, OUTPUT);
    pinMode(ULTRASONIC_TRIG, OUTPUT);
    pinMode(ULTRASONIC_ECHO, INPUT);
    pinMode(LEFT_IR, INPUT);
    pinMode(RIGHT_IR, INPUT);
}

void PikaBot::_delayMotors(int speed, double distance)
{
    if (not this->_isBetween(speed, 0, 255)) return;
    if (distance <= 0) return;

    delay((int) round((double) distance / this->_distanceRef * speed / this->_speedRef * this->_delayRef));
    this->stop();
}

bool PikaBot::_isBetween(int value, int lowerBound, int upperBound)
{
    return lowerBound <= value and value <= upperBound;
}

void PikaBot::calibrateMotors(int speed, int delay, int distance)
{
    if (not this->_isBetween(speed, 0, 255)) return;
    if (delay <= 0) return;
    if (distance <= 0) return;

    this->_speedRef = speed;
    this->_delayRef = delay;
    this->_distanceRef = distance;
}

bool PikaBot::detectLine(IR sensor)
{
    switch (sensor)
    {
    case LEFTIR:
        return digitalRead(LEFT_IR) == HIGH;
    case RIGHTIR:
        return digitalRead(RIGHT_IR) == HIGH;
    default:
        return false;
    }
}

bool PikaBot::isPressed()
{
    if (digitalRead(BUTTON) == HIGH)
    {
        return pulseIn(BUTTON, LOW, 1000000) != 0;
    }
    else
    {
        return false;
    }
}

void PikaBot::lineFollow(int speed)
{
    if (not this->_isBetween(speed, 0, 255)) return;

    if (this->detectLine(LEFTIR) && this->detectLine(RIGHTIR))
    {
        this->stop();
    }
    else if (!this->detectLine(LEFTIR) && !this->detectLine(RIGHTIR))
    {
        this->moveForward(speed);
    }
    else if (this->detectLine(LEFTIR))
    {
        this->turnRight(speed);
    }
    else if (this->detectLine(RIGHTIR))
    {
        this->turnLeft(speed);
    }
}

void PikaBot::move(int leftSpeed, int rightSpeed)
{
    while (this->lastMotorInstructionTime != 0 and millis() < lastMotorInstructionTime + DELAY) {}

    if (not this->_isBetween(leftSpeed, -255, 255) or not this->_isBetween(rightSpeed, -255, 255)) return;

    if (leftSpeed == 0)
    {
        analogWrite(LEFT_FORWARD, 0);
        analogWrite(LEFT_BACKWARD, 0);
    }
    else if (leftSpeed > 0)
    {
        analogWrite(LEFT_FORWARD, leftSpeed);
    }
    else
    {
        analogWrite(LEFT_BACKWARD, abs(leftSpeed));
    }

    if (rightSpeed == 0)
    {
        analogWrite(RIGHT_FORWARD, 0);
        analogWrite(RIGHT_BACKWARD, 0);
    }
    else if (rightSpeed > 0)
    {
        analogWrite(RIGHT_FORWARD, rightSpeed);
    }
    else
    {
        analogWrite(RIGHT_BACKWARD, abs(rightSpeed));
    }
    lastMotorInstructionTime = millis();
}

void PikaBot::moveBackward(int speed)
{
    if (not this->_isBetween(speed, 0, 255)) return;

    this->move(-speed, -speed);
}

void PikaBot::moveBackward(int speed, int distance)
{
    this->moveBackward(speed);
    this->_delayMotors(speed, distance);
}

void PikaBot::moveForward(int speed)
{
    if (not this->_isBetween(speed, 0, 255)) return;

    this->move(speed, speed);
}

void PikaBot::moveForward(int speed, int distance)
{
    this->moveForward(speed);
    this->_delayMotors(speed, distance);
}

void PikaBot::play(String musicSheet)
{
    musicSheet += ' ';
    int lastSpacePos = -1;
    int lastOctave = 4;
    int lastNote = QUARTER;
    while (true)
    {
        int spacePos = musicSheet.indexOf(' ', lastSpacePos + 1);
        if (spacePos == -1)
        {
            break;
        }
        int colonPos = musicSheet.indexOf(':', lastSpacePos + 1);
        String pitch;
        String note;
        if (colonPos != -1 && colonPos < spacePos)
        {
            pitch = musicSheet.substring(lastSpacePos + 1, colonPos);
            note = musicSheet.substring(colonPos + 1, spacePos);
        }
        else
        {
            pitch = musicSheet.substring(lastSpacePos + 1, spacePos);
            note = String(lastNote);
        }
        int intOctave = lastOctave;
        if (isDigit(pitch[pitch.length() - 1]))
        {
            intOctave = String(pitch[pitch.length() - 1]).toInt();
        }
        else if (!pitch.equals("R") && !pitch.equals("r"))
        {
            pitch += intOctave;
        }
        int intNote = note.toInt();
        lastSpacePos = spacePos;
        if ((!String(intNote).equals(note)) || intNote <= 0)
        {
            continue;
        }
        this->playTone(pitch, intNote);
        lastOctave = intOctave;
        lastNote = intNote;
    }
}

void PikaBot::playTone(String pitch, int note)
{
    if (not this->_isBetween(note, 1, 256)) return;

    this->playToneMs(pitch, round(240000. / this->tempo / note));
}

void PikaBot::playToneMs(String pitch, long duration)
{
    // Negative duration = forever
    int freq = pitchToFreq(pitch);
    tone(BUZZER, freq, duration);
    delay(duration * 1.3);
    noTone(BUZZER);
}

void PikaBot::resetTempo()
{
    this->tempo = 120;
}

void PikaBot::stop()
{
    this->move(0, 0);
}

void PikaBot::turnLeft(int speed)
{
    if (not this->_isBetween(speed, 0, 255)) return;

    this->move(speed, 0);
}

void PikaBot::turnLeft(int speed, bool reverse)
{
    if (reverse)
    {
        if (not this->_isBetween(speed, 0, 255)) return;

        this->move(0, -speed);
    }
    else
    {
        this->turnLeft(speed);
    }
}

void PikaBot::turnLeft(int speed, int angle)
{
    this->turnLeft(speed);
    this->_delayMotors(speed, 2 * PI * WIDTH * angle / 360);
}

void PikaBot::turnLeft(int speed, int angle, bool reverse)
{
    this->turnLeft(speed, reverse);
    this->_delayMotors(speed, 2 * PI * WIDTH * angle / 360);
}

void PikaBot::turnRight(int speed)
{
    if (not this->_isBetween(speed, 0, 255)) return;

    this->move(0, speed);
}

void PikaBot::turnRight(int speed, bool reverse)
{
    if (reverse)
    {
        if (not this->_isBetween(speed, 0, 255)) return;

        this->move(-speed, 0);
    }
    else
    {
        this->turnRight(speed);
    }
}

void PikaBot::turnRight(int speed, int angle)
{
    this->turnRight(speed);
    this->_delayMotors(speed, 2 * PI * WIDTH * angle / 360);
}

void PikaBot::turnRight(int speed, int angle, bool reverse)
{
    this->turnRight(speed, reverse);
    this->_delayMotors(speed, 2 * PI * WIDTH * angle / 360);
}

unsigned int PikaBot::ultrasonicDistance()
{
    digitalWrite(ULTRASONIC_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIG, LOW);
    unsigned int distance = pulseIn(ULTRASONIC_ECHO, HIGH) * 0.017;
    if (distance > 2000)
    {
        return 0;
    }
    else
    {
        return distance;
    }
}
