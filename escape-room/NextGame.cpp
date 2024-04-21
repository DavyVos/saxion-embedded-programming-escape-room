#include "NextGame.hpp"

NextGame::NextGame(State *next) : _next(next) {}

void NextGame::startGame(GameContext *context)
{
    context->Lcd->setCursor(0, 0);
    context->Lcd->println("Next game");
    context->Lcd->setCursor(0, 1);
    context->Lcd->println("Press button...");
}

void NextGame::update(GameContext *context)
{
    if (digitalRead(context->Button) == HIGH)
    {
        Serial.println("loading next game");
        this->nextGame(context);
    }
}

void NextGame::nextGame(GameContext *context)
{
    context->NextGame(this->_next);
}

void NextGame::stopGame(GameContext *context)
{
}