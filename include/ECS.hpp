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

    /// Returns the first valid ID to use for spawning entities
    size_t getNextId();

    /// Creates a new entity on the next valid ID
    /// * The screen the sprite will be visible on is determined by
    /// `pos.getScreen()` Another equal entity will be created on the other
    /// screen
    void spawnEntity(EntityType type, Pos pos);

    /// This function changes sprites, spawns bullets and so
    /// * It does NOT move Super Ace nor instructs `ECS` to do so
    /// See `ECS::updatePositions()` for movement
    void handleInput();

    /// Modifies `this->positions` and runs NF_MoveSprite
    void updatePositions();

    /// Iterates through all entites and changes their sprites
    /// acordingly (Such as Super Ace flying to the side, or an enemy rotating)
    void updateSprites();

    /// Looks for entities that can be destroyed
    /// (Such as bullets outside the screen and so)
    void garbageCollector();

    /// Handles the spawining of enemies and other events in the level
    void timelineHandler();
};

#endif