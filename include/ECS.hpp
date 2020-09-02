#ifndef __ECS_H
#define __ECS_H

#include "nf_lib.h"
#include <nds.h>

#include "config.hpp"
#include "helper.hpp"

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

    /// Default constructor
    ECS();

    /// Modifies `this->positions` and runs NF_MoveSprite
    void updatePositions();

    /// Iterates through all entites and changes their sprites
    /// acordingly (Such as Super Ace flying to the side, or an enemy rotating)
    void updateSprites();

    /// This function changes sprites, spawns bullets and so
    /// * It does NOT move Super Ace nor instructs `ECS` to do so
    /// See `ECS::updatePositions()` for movement
    void handleInput();

    /// Returns the first valid ID to use for spawning entities
    size_t getNextId();

    /// Creates a new entity on the next valid ID
    /// * The screen is determined by `pos.getScreen()`
    void   spawnEntity(EntityType type, Pos pos);

    /// Looks for entities that can be destroyed
    /// (Such as bullets outside the screen and so)
    void   garbageCollector();

    /// ! Unimplemented
    /// Deletes a sprite using `NF_DeleteSprite` and recreates
    /// it on the opposite screen
    void   swapScreen(size_t id);
};

#endif