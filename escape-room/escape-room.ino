#include <PS2Keyboard.h>
#include <TM1638plus.h>
#include <LiquidCrystal_I2C.h>
#include "GameContext.hpp"
#include "EscapeRoomState.hpp"
#include "LockPicking.hpp"

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
#define DATAPIN 8
#define IRQPIN  9


int buttonState = 0;

LiquidCrystal_I2C* lcd = new LiquidCrystal_I2C(0x27, 16, 2);
TM1638plus* tm = new TM1638plus(TM_STROBE, TM_CLOCK, TM_DIO);
PS2Keyboard* keyboard = new PS2Keyboard();

EscapeRoomState* initialState = new EscapeRoomState();
GameContext* gameContext = new GameContext(
    initialState,
    tm,
    keyboard,
    lcd,
    BUTTON_PIN,
    WIPER_PIN,
    PIN_BUZZER
    );

void setup()
{
    lcd->init();
    lcd->backlight();

    // initialize the pushbutton pin as an input:
    pinMode(BUTTON_PIN, INPUT);
    pinMode(WIPER_PIN, INPUT);
    analogRead(WIPER_PIN);

    

    // Initialize LED & KEY / Whadda module
    tm->displayBegin();

    keyboard->begin( DATAPIN, IRQPIN );

    Serial.begin(115200);
}

void loop()
{   
    randomSeed(analogRead(A1));
    gameContext->Update();
}