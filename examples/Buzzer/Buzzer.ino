// Challenge 4
#include "PikaBot.h"

PikaBot bot;

void setup() {
    // Set tempo
    bot.tempo = 180;

    // Play melody: Super Mario
    bot.play("e5:8 e r e r c e:4 g");

    delay(1000);

    // Reset tempo (to 120 bpm)
    bot.resetTempo();

    // Play melody: Baby Shark
    String repeated = "g:8 g g g:16 g:8 g:16 g:8";
    bot.play("d5 e " + repeated + " d e " + repeated + " d e " + repeated + " g:8 g f:2");

    delay(1000);

    // Play melody: Happy Birthday
    String repeated2 = "g:8 g a:4 g";
    bot.play(repeated2 + " c5 b4:2 " + repeated2 + " d5 c:2 g4:8 g g5:4 e c b4 a f5:8 f e:4 c d c:2");
}

void loop() {
}
