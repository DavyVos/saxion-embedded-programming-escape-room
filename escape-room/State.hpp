#ifndef STATE_H
#define STATE_H

#include "GameContext.hpp"

class GameContext;

class State {
public:
    String name;
    virtual ~State() {} // Virtual destructor to ensure correct deletion of derived classes
    
    virtual void update(GameContext* context) = 0; // Live fase when playig the game
    virtual void startGame(GameContext* context) = 0; // For first rendering and setup fase
    virtual void stopGame(GameContext* context) = 0; // Breakdown of game and cleaning
    virtual void nextGame(GameContext* context) = 0; // Loading next game into state
};

#endif // STATE_H