#include "helper.hpp"
#include "config.hpp"

Screen Pos::getScreen() {
    if (y <= 192 + SCREEN_GAP / 2)
        return Screen::TOP;
    else if (y > 192 + SCREEN_GAP / 2)
        return Screen::BOT;
}

s16 Pos::getYMapped() {
    switch (getScreen()) {
    case Screen::TOP:
        return y;
        break;
    case Screen::BOT:
        return y - 192 - SCREEN_GAP;
        break;
    }
}