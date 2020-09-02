#ifndef __WORLD_H
#define __WORLD_H

#include <nds.h>
#include "nf_lib.h"
#include "helper.hpp"
#include "config.hpp"

/// The game has 2 oceans
/// `NEAR` is used at the end of the level
/// to fight the boss
enum World {
    FAR, NEAR
};

/// This class handles the overworld background
/// Including the gap between screens, the scrolling and generation of random
/// objects
class Background {
    /// Layer to draw the background
    ScreenLayer layer = ScreenLayer::ZERO;
    /// What background to draw
    World world = World::FAR;
public:
    s16 scrolling = 0;
    Background();
    void scroll();
    void loadBg();
};

#endif