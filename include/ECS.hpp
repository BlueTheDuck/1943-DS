#ifndef __ECS_H
#define __ECS_H

#include <nds.h>
#include "nf_lib.h"

#include "helper.hpp"
#include "config.hpp"

class ECS {
  public:
    /// ID of the player (Super Ace)
    static const int S_ACE_ID = 0;

    EntityType types[127];
    Direction  directions[127];
    Screen     screens[127];
    Pos        positions[127];

    /// Counts the amount of frames that passed since shot fired by the player
    size_t timeSinceShoot = 0;

    ECS();

    void   updatePositions();
    void   updateSprites();
    void   handleInput();
    size_t getNextId();
    void   spawnEntity(EntityType type, s16 x, s16 y);
    void   garbageCollector();
    void   moveToScreen(Screen screen);
};

#endif