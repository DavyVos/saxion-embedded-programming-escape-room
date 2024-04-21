#ifndef WIN_END_H
#define WIN_END_H

#include "GameContext.hpp"

class GameContext;

class WinEnd: public State {
public:
    String name = "winner chicken dinner";
    virtual ~WinEnd() {}
    void update(GameContext *context) override;
    void startGame(GameContext *context) override;
    void stopGame(GameContext *context) override;
    void nextGame(GameContext *context) override;
};

#endif // WIN_END_H