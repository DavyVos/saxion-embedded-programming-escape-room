#include "LockPicking.hpp"
#include "NextGame.hpp"
#include "MultipleChoice.hpp"

byte hookChar[] = {
    B00011,
    B00011,
    B00011,
    B00011,
    B11011,
    B11011,
    B01111,
    B00110};

byte shaft[] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B11111,
    B11111,
    B00000,
    B00000};

byte pindown[] = {
    B11111,
    B00110,
    B00110,
    B00110,
    B00110,
    B00110,
    B00110,
    B00010};

byte pinup[] = {
    B11111,
    B00110,
    B00110,
    B00110,
    B00010,
    B00000,
    B00000,
    B00000};

byte empty[] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000};

int pickPosition = 0;
int currentLock = 0;

int lockCollection[2][8] = {
    {0, 8, 0, 0, 1, 0, 2, 0},
    {0, 8, 0, 3, 1, 0, 2, 0}};
int lastPicked = 0;

int baseTone = 440;
int toneMultiplier = 5;

void drawPick(GameContext *context)
{
    for (int i = 0; i < 16; i++)
    {
        context->Lcd->setCursor(i, 1);
        if (i == pickPosition)
        {
            context->Lcd->write(1); // write hook
        }
        else if (i < pickPosition)
        {
            context->Lcd->write(5); // write shaft
        }
        else
        {
            // lcd write empty character
            context->Lcd->write(0);
        }
    }
}

void drawPins(GameContext *context)
{
    for (int i = 0; i < 16; i++)
    {
        context->Lcd->setCursor(i, 0);
        if (i < 8)
        {
            int pin = lockCollection[currentLock][i];
            if (0 < pin && pin <= lastPicked)
            {
                // this pin has been picked and must be drawn in up position
                context->Lcd->write(4);
            }
            else if (0 < pin)
            {
                // this pin has not been picked
                context->Lcd->write(2);
            }
        }
        else
        {
            context->Lcd->write(0);
        }
    }
}

void LockPicking::startGame(GameContext *context)
{
    context->Lcd->createChar(0, empty);
    context->Lcd->createChar(1, hookChar);
    context->Lcd->createChar(2, pindown);
    context->Lcd->createChar(4, pinup);
    context->Lcd->createChar(5, shaft);
    currentLock = 0;
    lastPicked = 0;
}

void LockPicking::nextGame(GameContext *context)
{
    context->NextGame(new NextGame(new MultipleChoice()));
}

void LockPicking::update(GameContext *context)
{
    static long buttonPressedAt = 0;
    pickPosition = map(analogRead(context->Potentiometer), 25, 1023, 8, 0);
    int currentpin = lockCollection[currentLock][pickPosition];
    int pinTone = baseTone + (currentpin * toneMultiplier);
    int buttonState = digitalRead(context->Button);
    uint8_t debouncedTmReading = context->getDebouncedTmReading();

    drawPick(context);
    drawPins(context);

    if (2 == currentLock)
    {
        this->nextGame(context);
    }
    else if (8 == lastPicked)
    {
        Serial.println(currentLock);
        Serial.println(lastPicked);
        context->Lcd->clear();
        lastPicked = 0;
        currentLock++;
    }
    else
    {
        if (HIGH == buttonState)
        {
            tone(context->Buzzer, pinTone, 500);
        }

        if (0b00000001 < debouncedTmReading)
        {
            if (currentpin >= lastPicked)
            {
                lastPicked = currentpin;
                tone(context->Buzzer, pinTone, 50);
                tone(context->Buzzer, 400, 500);
            }
            else
            {
                context->GameOver();
            }
        }
    }

    if (0 < lastPicked && 20000 < context->CurrentTimeStamp - context->CurrentGameStartedAt)
    {
        context->GameOver();
    }
}

void LockPicking::stopGame(GameContext *context)
{
}