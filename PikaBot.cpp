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

PikaBot::PikaBot(void) {
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

void PikaBot::lineFollow() {
    if (digitalRead(LEFT_IR) == LOW && digitalRead(RIGHT_IR) == LOW) {
        analogWrite(LEFT_FORWARD, 255);
        analogWrite(RIGHT_FORWARD, 255);
    } else if (digitalRead(LEFT_IR) == HIGH) {
        analogWrite(LEFT_FORWARD, -255);
        analogWrite(RIGHT_FORWARD, 255);
    } else if (digitalRead(RIGHT_IR) == HIGH) {
        analogWrite(LEFT_FORWARD, 255);
        analogWrite(RIGHT_FORWARD, -255);
    }
}
