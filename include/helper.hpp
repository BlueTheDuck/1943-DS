#ifndef __HELPER_H
#define __HELPER_H

#include <nds.h>

enum Screen {
    TOP = 0,
    BOT = 1
};

enum ScreenLayer {
    ZERO = 0,
    ONE = 1,
    TWO = 2,
    THREE = 3,
};

/// Specifies the direction a plane is flying
/// These values are relative to the plane itself
enum Direction { Forward, Left, Right };

/// Specifies what kind of entity lives in a slot
enum EntityType {
    /// There is no entity living here
    None,
    /// The player
    SuperAce,
    /// Flying bullet
    Bullet,
    /// Kind of enemy
    /// TODO: There are many different enemies and AIs. Maybe add more types?
    Enemy
};

/// XY of an entity in game
/// the y coordinate maps [0;192] to the top screen
/// and [192+SCREEN_GAP;384+SCREEN_GAP] to the bottom screen
/// The gap is split between the 2
struct Pos {
    s16    x, y;
    Screen getScreen();
    /// Get the Y component relative to the screen
    /// that the sprite falls on
    s16 getYMapped();
};


/// Caps a value in the range [min; max]
s16 cap(s16 val, s16 min, s16 max);


#endif