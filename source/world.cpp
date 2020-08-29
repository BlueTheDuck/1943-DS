#include "world.hpp"

void Background::scroll() {
    NF_ScrollBg(Screen::TOP, ScreenLayer::ZERO, 0, scrolling);
    NF_ScrollBg(Screen::BOT, ScreenLayer::ZERO, 0, scrolling + _screenGap + 64);
    scrolling--;
    if (scrolling % 256 == 0) {
        scrolling = 0;
    }
}