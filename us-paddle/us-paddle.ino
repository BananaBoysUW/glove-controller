#include "NewPing.h"

#define MAX_DISTANCE 400
#define TRIGGER_PIN 12
#define ECHO_PIN 11

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
    Serial.begin(115200);
}

void loop() {
    // serially output the ultrasonic distance to be read by the brickbreaker game
    double dist = (sonar.ping() / 2) * 0.0343;
    Serial.println(dist);
    delay(50);
}
