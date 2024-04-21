#ifndef MEMORY_GAME_H
#define MEMORY_GAME_H

#include "State.hpp"

class MemoryGame : public State
{
private:
    /* data */
public:
    String name = "Memory Game";
    virtual ~MemoryGame(){};
    void update(GameContext *context) override;
    void startGame(GameContext *context) override;
    void stopGame(GameContext *context) override;
    void nextGame(GameContext *context) override;
};

#endif