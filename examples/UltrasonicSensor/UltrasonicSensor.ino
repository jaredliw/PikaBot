// Challenge 2
#include "PikaBot.h"

PikaBot bot;

void setup() {
    // Move forward when powered on
    bot.moveForward(255);
}

void loop() {
    if (bot.ultrasonicDistance() <= 20) {
        // Turn to the left more than 90 degrees when the robot 
        // detects an obstacle within 20 cm range
        bot.turnLeft(255, 90);
    } else {
        // Continue to move forward otherwise
        bot.moveForward(255);
    }
}
