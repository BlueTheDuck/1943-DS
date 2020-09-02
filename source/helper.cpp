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

s16 cap(s16 val, s16 min, s16 max) {
    if (val > max)
        return max;
    else if (val > min)
        return val;
    else
        return min;
}