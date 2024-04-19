#include <TM1638plus.h>
#include <LiquidCrystal_I2C.h>

#define PIN_BUZZER 3
#define FREQ_LOW 500
#define FREQ_HIGH 1200
#define WHOOP_DURATION 3500
#define WHOOP_STEPS 350
#define BUTTON_PIN 2
#define WIPER_PIN A0
#define TM_STROBE 4
#define TM_CLOCK 6
#define TM_DIO 7

int buttonState = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);
TM1638plus tm(TM_STROBE, TM_CLOCK, TM_DIO);

void setup()
{
    lcd.init();
    lcd.backlight();
    lcd.setCursor(3,0);
    lcd.print("Hello world!");

    // initialize the pushbutton pin as an input:
    pinMode(BUTTON_PIN, INPUT);
    pinMode(WIPER_PIN, INPUT);

    // Initialize LED & KEY / Whadda module
    tm.displayBegin();

    Serial.begin(115200);

    int freqchange = (FREQ_HIGH - FREQ_LOW) / WHOOP_STEPS;
    int toneDuration = WHOOP_DURATION / WHOOP_STEPS;

    for (int i = 0; i < 10; i++)
    {
        for (int freq = FREQ_LOW; freq <= FREQ_HIGH; freq += freqchange)
        {
            // read the state of the pushbutton value:
            buttonState = digitalRead(BUTTON_PIN);
            // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
            if (buttonState == HIGH)
            {
                // turn LED on:
                tone(PIN_BUZZER, freq, toneDuration);
            }
            delay(toneDuration);
        }
        delay(500);
    }
}

void loop()
{
    // lcd.println("Hello world!");
    int wiperValue = analogRead(WIPER_PIN);
    Serial.printf("%d --> %d mV\n", wiperValue,
                  map(wiperValue, 20, 1023, 0, 3300));

    // Turn on leftmost LED
    tm.setLED(0, 1);
    delay(1000);
    // Turn on rightmost LED as well
    tm.setLED(7, 1);
    delay(1000);
    // Turn on LED 2, 4, 6 and 8 - others off
    tm.setLEDs(0b1010101000000000);
    delay(1000);
    // Clear display
    tm.reset();
    delay(1000);
}