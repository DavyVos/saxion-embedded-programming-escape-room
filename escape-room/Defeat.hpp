#ifndef DEFEAT_H
#define DEFEAT_H

#include "GameContext.hpp"

class GameContext;

class Defeat: public State {
public:
    String name = "winner chicken dinner";
    virtual ~Defeat() {}
    void update(GameContext *context) override;
    void startGame(GameContext *context) override;
    void stopGame(GameContext *context) override;
    void nextGame(GameContext *context) override;
};

#endif // DEFEAT_H