#ifndef MULTIPLECHOICE_H
#define MULTIPLECHOICE_H

#include "State.hpp"

class MultipleChoice : public State
{
private:
    /* data */
public:
    String name = "LockPicking";
    virtual ~MultipleChoice() {};
    void update(GameContext* context) override;
    void startGame(GameContext* context) override;
    void stopGame(GameContext* context) override;
    void nextGame(GameContext* context) override;
};

#endif //MULTIPLECHOICE_H