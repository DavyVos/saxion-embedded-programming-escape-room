#ifndef NEXT_GAME_H
#define NEXT_GAME_H

#include "State.hpp"
#include "GameContext.hpp"

class NextGame: public State {
private:
    State *_next;
public:
    String name = "EscapeRoom";
    NextGame(State *next);
    virtual ~NextGame() {}
    void update(GameContext* context) override;
    void startGame(GameContext* context) override;
    void stopGame(GameContext* context) override;
    void nextGame(GameContext* context) override;
};

#endif // NEXT_GAME_H