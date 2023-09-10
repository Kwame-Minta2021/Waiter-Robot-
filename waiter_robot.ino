#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define the keypad
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

// Define the row and column pins
byte rowPins[ROWS] = {22, 24, 26, 28};
byte colPins[COLS] = {30, 32, 34};

// Create the keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

#define enA 9
#define enB 10
#define LM1 4  // left motor
#define LM2 5  // left motor
#define RM1 6  // right motor
#define RM2 7  // right motor

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(LM1, OUTPUT);
    pinMode(LM2, OUTPUT);
    pinMode(RM1, OUTPUT);
    pinMode(RM2, OUTPUT);
    Serial.begin(9600);

    // Initialize the LCD
    lcd.begin();
    lcd.backlight();
    lcd.print("Serving Table: ");
}

void loop() {
    char key = keypad.getKey();
    if (key != NO_KEY) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Serving Table: ");
        
        if (key == '1') {
            moveRobot(7000, -90, 5000, 180); // Forward, Turn left, Move forward, Turn around
            lcd.setCursor(0, 1);
            lcd.print("Table One Done");
            delay(3000);
        } else if (key == '2') {
            moveRobot(10000, 90, 5000, 180); // Forward, Turn right, Move forward, Turn around
            lcd.setCursor(0, 1);
            lcd.print("Table Two Done");
            delay(3000);
        } else if (key == '3') {
            moveRobot(12000, -90, 5000, 180); // Forward, Turn left, Move forward, Turn around
            lcd.setCursor(0, 1);
            lcd.print("Table Three Done");
            delay(3000);
        } else if (key == '0') {
            stopRobot();
            lcd.setCursor(0, 1);
            lcd.print("Robot Stopped");
        } else if (key == '*') {
            lcd.setCursor(0, 1);
            lcd.print("Robot Moving");
            moveRobot(1000, 0, 0, 0); // Move forward for 1 second
        }
    }
}

void moveRobot(int forwardTime, int turnAngle, int moveBackTime, int turnBackAngle) {
    forward();
    delay(forwardTime);
    stopRobot();
    delay(1000);
    
    if (turnAngle != 0) {
        if (turnAngle == 90) {
            right();
        } else if (turnAngle == -90) {
            left();
        }
        delay(1500); // Adjust delay for turning
        stopRobot();
        delay(500);
    }
    
    if (moveBackTime != 0) {
        backward();
        delay(moveBackTime);
        stopRobot();
        delay(1000);
    }
    
    if (turnBackAngle != 0) {
        if (turnBackAngle == 90) {
            right();
        } else if (turnBackAngle == -90) {
            left();
        }
        delay(1500); // Adjust delay for turning
        stopRobot();
        delay(500);
    }
}

void forward() {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
}

void backward() {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
}

void left() {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
}

void right() {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
}

void stopRobot() {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
}
