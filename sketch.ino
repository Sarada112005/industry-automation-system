#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PIR_SENSOR 15
#define RELAY_PIN 13
#define STEP_PIN 18
#define DIR_PIN 19
#define LED_PIN 5

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27 for 16x2 LCD

void setup() {
    Serial.begin(115200);
    
    pinMode(PIR_SENSOR, INPUT);
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    
    pinMode(STEP_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);

    lcd.begin(16,2);
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Industrial Auto");
    delay(2000);
    lcd.clear();
}

void loop() {
    int motionDetected = digitalRead(PIR_SENSOR);

    if (motionDetected) {
        Serial.println("Motion Detected!");
        digitalWrite(RELAY_PIN, HIGH);  // Activate Relay
        digitalWrite(LED_PIN, HIGH);    // Turn ON LED
        lcd.setCursor(0, 0);
        lcd.print("Machine: ON");

        // Run Stepper Motor
        digitalWrite(DIR_PIN, HIGH);
        for (int i = 0; i < 200; i++) {
            digitalWrite(STEP_PIN, HIGH);
            delayMicroseconds(500);
            digitalWrite(STEP_PIN, LOW);
            delayMicroseconds(500);
        }
        
    } else {
        Serial.println("No Motion.");
        digitalWrite(RELAY_PIN, LOW);  // Deactivate Relay
        digitalWrite(LED_PIN, LOW);    // Turn OFF LED
        lcd.setCursor(0, 0);
        lcd.print("Machine: OFF ");
    }

    delay(1000);
}