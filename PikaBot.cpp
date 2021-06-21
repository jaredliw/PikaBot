# include "PikaBot.h"

# define BUTTON 2
# define BUZZER 8
# define LEFT_FORWARD 11
# define LEFT_BACKWARD 10
# define RIGHT_FORWARD 9
# define RIGHT_BACKWARD 3
# define ULTRASONIC_TRIG 5
# define ULTRASONIC_ECHO 4
# define LEFT_IR A0
# define RIGHT_IR A1

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

void PikaBot::_delayMotors(uint8_t speed, uint8_t distance)
{
    if (distance > 0)
    {
        delay((int) round((float) distance / this->_distanceRef * speed / this->_speedRef * this->_delayRef));
        this->stop();
    }
}

void PikaBot::calibrateMotors(uint8_t speed, uint16_t delay, uint8_t distance)
{
    this->_speedRef = speed;
    this->_delayRef = delay;
    this->_distanceRef = distance;
}

bool PikaBot::detectLine(IR sensor)
{
    switch (sensor)
    {
    case LeftIR:
        return digitalRead(LEFT_IR) == HIGH;
    case RightIR:
        return digitalRead(RIGHT_IR) == HIGH;
    default:
        return false;
    }
}

bool PikaBot::isPressed()
{
    return digitalRead(BUTTON) == LOW;
}

void PikaBot::lineFollow()
{
    if (!this->detectLine(LeftIR) && !this->detectLine(RightIR))
    {
        analogWrite(LEFT_FORWARD, 255);
        analogWrite(RIGHT_FORWARD, 255);
    }
    else if (this->detectLine(LeftIR))
    {
        analogWrite(LEFT_FORWARD, -255);
        analogWrite(RIGHT_FORWARD, 255);
    }
    else if (this->detectLine(RightIR))
    {
        analogWrite(LEFT_FORWARD, 255);
        analogWrite(RIGHT_FORWARD, -255);
    }
}

void PikaBot::move(int16_t leftSpeed, int16_t rightSpeed)
{
    if (leftSpeed > 255)
    {
        leftSpeed = 255;
    }
    else if (leftSpeed < -255)
    {
        leftSpeed = -255;
    }
    if (rightSpeed > 255)
    {
        rightSpeed = 255;
    }
    else if (rightSpeed < -255)
    {
        rightSpeed = -255;
    }

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
}

void PikaBot::moveBackward(uint8_t speed, uint8_t distance)
{
    this->move(-speed, -speed);
    this->_delayMotors(speed, distance);
}

void PikaBot::moveForward(uint8_t speed, uint8_t distance)
{
    this->move(speed, speed);
    this->_delayMotors(speed, distance);
}

void PikaBot::stop()
{
    this->move(0, 0);
}

void PikaBot::turnLeft(uint8_t speed)
{
    this->move(speed, -speed);
}

void PikaBot::turnRight(uint8_t speed)
{
    this->move(-speed, speed);
}

uint16_t PikaBot::ultrasonicDistance()
{
    digitalWrite(ULTRASONIC_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIG, LOW);
    uint16_t distance = pulseIn(ULTRASONIC_ECHO, HIGH) * 0.017;
    if (distance > 2000)
    {
        return 0;
    }
    else
    {
        return distance;
    }
}
