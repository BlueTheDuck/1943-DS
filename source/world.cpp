#include "world.hpp"

Background::Background() {
    NF_LoadTiledBg("bg/far_ocean", "far_ocean_bg", 256, 256);
    NF_LoadTiledBg("bg/near_ocean", "near_ocean_bg", 256, 256);
    loadBg();
}

void Background::loadBg() {
    switch (world) {
    case World::FAR:
        NF_CreateTiledBg(Screen::TOP, layer, "far_ocean_bg");
        NF_CreateTiledBg(Screen::BOT, layer, "far_ocean_bg");
        break;
    case World::NEAR:
        NF_CreateTiledBg(Screen::TOP, layer, "near_ocean_bg");
        NF_CreateTiledBg(Screen::BOT, layer, "near_ocean_bg");
        break;
    default:
        break;
    }
}

void Background::scroll() {
    NF_ScrollBg(Screen::TOP, ScreenLayer::ZERO, 0, scrolling);
    NF_ScrollBg(Screen::BOT, ScreenLayer::ZERO, 0, scrolling + SCREEN_GAP + 64);
    scrolling--;
    if (scrolling % 256 == 0) {
        scrolling = 0;
    }
}
