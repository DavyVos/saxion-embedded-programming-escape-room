#include "EscapeRoomState.hpp"
#include "Arduino.h"
#include "MemoryGame.hpp"
#include "BombDefusal.hpp"
#include "LockPicking.hpp"
#include "MultipleChoice.hpp"


void EscapeRoomState::startGame(GameContext* context) {
        context->Lcd->setCursor(0, 0);
        context->Lcd->println("Welcome to escape room!");
        context->Lcd->setCursor(0,1);
        context->Lcd->println("Press the button to start.");
}

void EscapeRoomState::update(GameContext *context)
{
    if (digitalRead(context->Button) == HIGH) {
        Serial.println("loading next game");
        this->nextGame(context);
    }
}

void EscapeRoomState::nextGame(GameContext* context) {
    context->StopGame();
    context->NextGame(new MemoryGame());
}

void EscapeRoomState::stopGame(GameContext *context)
{

}