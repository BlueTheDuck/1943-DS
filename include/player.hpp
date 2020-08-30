#ifndef __PLAYER_H
#define __PLAYER_H

#include "entity.hpp"

class Player : public Entity {
public:
    Player(u8 id, u16 gfx, u8 pal);
    void update();
};

#endif