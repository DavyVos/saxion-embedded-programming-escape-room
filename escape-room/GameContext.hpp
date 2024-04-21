#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <TM1638plus.h>
#include <LiquidCrystal_I2C.h>
#include "State.hpp"
#include <PS2Keyboard.h>
#include "Task.hpp"

class State;

const int MAX_TASKS = 5;

class GameContext
{

private:
    Task tasks[MAX_TASKS];
    int numTasks;

public:
    TM1638plus *Tm;
    LiquidCrystal_I2C *Lcd;
    PS2Keyboard *Keyboard;
    uint32_t Button;
    uint32_t Potentiometer;
    uint32_t Buzzer;
    State *CurrentState;
    long CurrentTimeStamp;
    long PreviousTimeStamp;
    long CurrentGameStartedAt;
    GameContext(
        State *currentState,
        TM1638plus *tm,
        PS2Keyboard *keyboard,
        LiquidCrystal_I2C *lcd,
        uint32_t button,
        uint32_t potentiometer,
        uint32_t buzzer);
    void NextGame(State *state);
    void StartGame();
    void GameOver();
    void GetCurrentTimeStamp();
    void Update();
    void StopGame();
    void AddTask(Task t);
    void clearTasks();
    uint8_t getDebouncedTmReading();
    void startGlobalTimer();
    long getGlobalTime();
};

#endif // GAME_CONTEXT