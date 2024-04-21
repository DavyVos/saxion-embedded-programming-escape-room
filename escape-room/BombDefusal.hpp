#ifndef BOMB_DEFUSAL_H
#define BOMB_DEFUSAL_H

#include "State.hpp"

class BombDefusal : public State
{
private:
public:
    virtual ~BombDefusal() {}
    void update(GameContext* context) override;
    void startGame(GameContext* context) override;
    void stopGame(GameContext* context) override;
    void nextGame(GameContext* context) override;
};

#endif