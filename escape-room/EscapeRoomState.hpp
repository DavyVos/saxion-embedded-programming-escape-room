#ifndef ESCAPE_ROOM_STATE_H
#define ESCAPE_ROOM_STATE_H

#include "State.hpp"
#include "GameContext.hpp"

class EscapeRoomState: public State {
public:
    String name = "EscapeRoom";

    virtual ~EscapeRoomState() {}
    
    void update(GameContext* context) override;
    void startGame(GameContext* context) override;
    void stopGame(GameContext* context) override;
    void nextGame(GameContext* context) override;
};

#endif // ESCAPE_ROOM_STATE_H