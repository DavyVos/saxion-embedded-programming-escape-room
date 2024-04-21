#include "MemoryGame.hpp"
#include "NextGame.hpp"
#include "BombDefusal.hpp"
#include "Arduino.h"

String convertIntArrayToString(int *intArray, int size)
{
    String result = "";
    for (int i = 0; i < size; i++)
    {
        // Convert the current element to a string and append it to the result
        result += String(intArray[i]);

        // If it's not the last element, append a separator (e.g., comma)
        if (i < size - 1)
        {
            result += ",";
        }
    }
    return result;
}

bool verifyAnswer(int *sequence, char userAnswer[], int size)
{
    Serial.println(userAnswer);
    // Iterate over each element in the sequence
    for (int i = 0; i < size; i++)
    {
        Serial.println(sequence[i]);
        // Check if the user's answer matches the corresponding element in the sequence
        if (userAnswer[i] - '0' != sequence[i])
        {
            // If there is a mismatch, return false
            return false;
        }
    }
    // If all elements match, return true
    return true;
}

int minimumsize = 3;
int rounds = 2;
int *sequence = new int[10];

char keyboardstrokes[10] = {};
int currentKey = 0;

int currentRound = 0;
long startOfRound = 0;
long displayTime = 2000;

void fillRandomSequence()
{
    for (int j = 0; j < minimumsize + currentRound; j++)
    {
        sequence[j] = (int)random(0, 10);
    }
}

void MemoryGame::startGame(GameContext *context)
{
    context->Lcd->setCursor(0, 0);
    context->Lcd->println("Start memory game");
    fillRandomSequence();
    currentRound = 0;
    currentKey = 0;
}

void MemoryGame::update(GameContext *context)
{
    long millisSinceStarted = context->CurrentTimeStamp - context->CurrentGameStartedAt;
    int size = currentRound + minimumsize;

    if (3000 < millisSinceStarted && 3200 > millisSinceStarted)
    {
        context->Lcd->clear();
        String firstNumbers = convertIntArrayToString(sequence, size) + "      ";
        Serial.println(firstNumbers);
        context->Lcd->println(firstNumbers);
        startOfRound = context->CurrentTimeStamp;
        while(context->Keyboard->available())
        {
            context->Keyboard->read();
        }
    }

    if (true == context->Keyboard->available() && displayTime + 100 < startOfRound)
    {
        char nextKey = context->Keyboard->read();

        if (PS2_ENTER == nextKey || 10 <= currentKey)
        {
            bool result = verifyAnswer(sequence, keyboardstrokes, size);
            if (true == result && currentRound < rounds)
            {
                Serial.println(currentRound);
                currentRound++;
                currentKey = 0;
                startOfRound = context->CurrentTimeStamp;
                size = currentRound + minimumsize;
                fillRandomSequence();
                String firstNumbers = convertIntArrayToString(sequence, size) + "      ";
                Serial.println(firstNumbers);
                context->Lcd->clear();
                context->Lcd->setCursor(0, 0);
                context->Lcd->println(firstNumbers);
                startOfRound = context->CurrentTimeStamp;
            }
            else if (true == result)
            {
                this->nextGame(context);
            }
            else
            {
                context->GameOver();
            }
        }
        else
        {
            context->Lcd->setCursor(currentKey, 0);
            keyboardstrokes[currentKey] = nextKey;
            currentKey++;
            context->Lcd->print(nextKey);
        }
    }

    if (displayTime < context->CurrentTimeStamp - startOfRound && displayTime + 100 > context->CurrentTimeStamp - startOfRound)
    {
        context->Lcd->clear();
    }
}

void MemoryGame::stopGame(GameContext *context)
{
}

void MemoryGame::nextGame(GameContext *context)
{
    context->NextGame(new NextGame(new BombDefusal()));
}