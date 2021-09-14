// Challenge 1
#include "PikaBot.h"

PikaBot bot;

void setup() {
    // Calibrate motors
    // Dry run the robot with speed 255 and delay 500,
    // measure the distance moved with a ruler (in my case it is 22 cm)
    bot.calibrateMotors(255, 500, 22);

    // Move in a rectangle
    bot.moveForward(255, 20);
    bot.turnLeft(255, 90);
    bot.moveForward(255, 30);
    bot.turnLeft(255, 90);
    bot.moveForward(255, 20);
    bot.turnLeft(255, 90);
    bot.moveForward(255, 30);

    delay(2000);

    // Move in a circle
    bot.move(128, 255);
    delay(4500);
    bot.stop();
    
    delay(2000);

    // Move in a triangle
    for (int i = 0; i < 3; i++) {
        bot.moveForward(255, 20);
        bot.turnLeft(255, 120);
    }
}

void loop() {
}