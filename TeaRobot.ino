#include <Servo.h>

bool _mix = false;
const int _ref = 25;

// Pin(s)
const int trigPin = 2;
const int echoPin = 3;
const int buttPin = 7;
const int servoPin = 9; 

// Lib(s)
Servo myservo;
void setup() {
    myservo.attach(servoPin);
    Serial.begin(9600);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(buttPin, INPUT);
}

void buttonispressed() {
    if (digitalRead(buttPin) == HIGH) {
        _mix = !_mix;
        Serial.println("Button Pressed !");
    }
}

void distance() {
    long distance = 0;

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    distance = pulseIn(echoPin, HIGH) * 0.034 / 2;

    if (distance < _ref - 5 && distance > 1)
        _mix = !_mix;

    Serial.print("Distance en cm :");
    Serial.print(distance);
    Serial.print(" | Activate :");
    Serial.println(_mix);
}

void mixing() {
    myservo.write(0);
    delay(250);
    myservo.write(45);
    delay(250);
    myservo.write(90);
    delay(250);
    myservo.write(135);
    delay(250);
    myservo.write(180);
    delay(250);
}

void loop() {
    distance();
    buttonispressed();
    if (_mix)
        mixing();
}

// Useful lines
// val = map(val, 0, 1023, 0, 180);
