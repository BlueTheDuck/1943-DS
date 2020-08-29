#ifndef __WORLD_H
#define __WORLD_H

#include <nds.h>
#include "nf_lib.h"
#include "helper.hpp"

/// This class handles the overworld background
/// Including the gap between screens, the scrolling and generation of random
/// objects
class Background {
    int _screenGap = 0;
    ScreenLayer layer = ScreenLayer::ZERO;
public:
    s16 scrolling = 0;
    Background(int screenGap) {
        this->_screenGap = screenGap,
        NF_LoadTiledBg("bg/ocean", "bg_ocean", 256, 256);
        NF_CreateTiledBg(Screen::TOP, layer, "bg_ocean");
        NF_CreateTiledBg(Screen::BOT, layer, "bg_ocean");
    }
    void scroll();
};

#endif