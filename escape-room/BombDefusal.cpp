#include "BombDefusal.hpp"
#include "NextGame.hpp"
#include "LockPicking.hpp"

int selectPattern = 0;
int step = 0;

int frame = 0;
bool left = false;

uint8_t buttonmasher[100];
int currentMash = 0;

// Function to find a uint8_t value in an array
bool findValue(uint8_t value, uint8_t *array, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        if (array[i] == value)
        {
            return true; // Value found
        }
    }
    return false; // Value not found
}

void kitLight(GameContext *context)
{
    if (context->CurrentTimeStamp % 100 == 0)
    {
        if (false == left)
        {
            if (frame < 8)
            {
                context->Tm->setLED(frame, 1);
            }
            if (frame > 3)
            {
                context->Tm->setLED(frame - 4, 0);
            }
            ++frame;
            if (12 == frame)
            {
                left = true;
            }
        }

        if (true == left)
        {
            --frame;
            if (frame < 8 && frame > -1)
            {
                context->Tm->setLED(frame, 1);
            }
            if (frame < 4)
            {
                context->Tm->setLED(frame + 4, 0);
            }
            if (0 == frame)
            {
                left = false;
            }
        }
    }
}

void BombDefusal::startGame(GameContext *context)
{
    context->Lcd->println("Bomb defusal");
    selectPattern = random(0, 3);
    switch (selectPattern)
    {
    case 0:
    {
        context->Tm->displayText("BOOT");
        context->AddTask(Task(kitLight, context));
        break;
    }
    case 1:
    {
        context->Tm->displayText("BOOT");
        context->Tm->setLED(3, 1);
        break;
    }
    case 2:
    {
        context->Tm->displayText("DANGER");
        break;
    }
    case 3:
    {
        context->Tm->displayText("WARNING");
        break;
    }
    }
}

void BombDefusal::nextGame(GameContext *context)
{
    context->Tm->reset();
    context->Lcd->print("Success");
    context->NextGame(new NextGame(new LockPicking()));
}

void BombDefusal::stopGame(GameContext *context)
{
}

void BombDefusal::update(GameContext *context)
{
    long millisSinceStarted = context->CurrentTimeStamp - context->CurrentGameStartedAt;
    uint8_t debouncedTmReading = context->getDebouncedTmReading();
    if (3000 < millisSinceStarted && 3200 > millisSinceStarted)
    {
        context->Lcd->clear();
    }

    if (0b00000000 < debouncedTmReading && 100 > currentMash)
    {
        buttonmasher[currentMash] = debouncedTmReading;
        currentMash++;
    }
    else
    {
        currentMash = 0;
    }

    switch (selectPattern)
    {
    case 0:
    {
        if (0b00000000 < debouncedTmReading && currentMash > 50)
        {
            if (findValue(0b00010001, buttonmasher, currentMash))
            {
                this->nextGame(context);
            }
            else
            {
                context->GameOver();
            }
        }
        break;
    }
    case 1:
    {
        if (0b00000000 < debouncedTmReading && 0b00000100 == debouncedTmReading)
        {
            this->nextGame(context);
        }
        else if (0b00000000 < debouncedTmReading)
        {
            context->GameOver();
        }
        break;
    }
    case 2:
    {
        if (10000 < context->CurrentTimeStamp - context->CurrentGameStartedAt && 0b00000000 == debouncedTmReading)
        {
            context->GameOver();
        }
        if (15000 < context->CurrentTimeStamp - context->CurrentGameStartedAt)
        {
            this->nextGame(context);
        }
        break;
    }
    case 3:
    {
        break;
    }
    }

    if (30000 < context->CurrentTimeStamp - context->CurrentGameStartedAt && selectPattern == 3)
    {
        this->nextGame(context);
    }
    else if (30000 < context->CurrentTimeStamp - context->CurrentGameStartedAt)
    {
        context->GameOver();
    }
}
