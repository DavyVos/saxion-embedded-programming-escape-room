#include "Defeat.hpp"
#include "EscapeRoomState.hpp"


void Defeat::startGame(GameContext *context)
{
    context->Lcd->setCursor(0, 0);
    context->Lcd->println("You have DIED!");
    context->Lcd->setCursor(0, 1);
    context->Lcd->println("Press button...");
}

void Defeat::update(GameContext *context)
{
    if (digitalRead(context->Button) == HIGH)
    {
        Serial.println("loading next game");
        this->nextGame(context);
    }
}

void Defeat::nextGame(GameContext *context)
{
    context->NextGame(new EscapeRoomState());
}

void Defeat::stopGame(GameContext *context)
{
}