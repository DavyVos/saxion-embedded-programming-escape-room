#ifndef LOCK_PICKING_H
#define LOCK_PICKING_H

#include "State.hpp"

class LockPicking : public State
{
private:
    /* data */
public:
    String name = "LockPicking";
    virtual ~LockPicking() {};
    void update(GameContext* context) override;
    void startGame(GameContext* context) override;
    void stopGame(GameContext* context) override;
    void nextGame(GameContext* context) override;
};

#endif //LOCK_PICKING_H