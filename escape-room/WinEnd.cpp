#include "WinEnd.hpp"
#include "EscapeRoomState.hpp"


void WinEnd::startGame(GameContext *context)
{
    context->Lcd->setCursor(0, 0);
    context->Lcd->println("You have won!");
    context->Lcd->setCursor(0, 1);
    context->Lcd->println("Press button...");
}

void WinEnd::update(GameContext *context)
{
    if (digitalRead(context->Button) == HIGH)
    {
        Serial.println("loading next game");
        this->nextGame(context);
    }
}

void WinEnd::nextGame(GameContext *context)
{
    context->NextGame(new EscapeRoomState());
}

void WinEnd::stopGame(GameContext *context)
{
}