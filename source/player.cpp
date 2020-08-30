#include "player.hpp"

Player::Player(u8 id, u16 gfx, u8 pal)
    : Entity(Screen::BOT, ScreenLayer::ZERO, id, gfx, pal) {
    /*
        The spritesheet has 5 frames
        0-1: Fly left
        2: Fly straight
        3-4: Fly right
    */
    this->setFrame(2);
}

void Player::update() {
    // Assume scanKeys was called

    // Set correct sprite
    if (keysDown() & KEY_LEFT) {
        this->setFrame(1);
    } else if (keysHeld() & KEY_LEFT) {
        this->setFrame(0);
    } else if (keysDown() & KEY_RIGHT) {
        this->setFrame(3);
    } else if (keysHeld() & KEY_RIGHT) {
        this->setFrame(4);
    } else {
        this->setFrame(2);
    }

    // Update position
    if (keysCurrent() & KEY_LEFT && this->_x > 0) {
        this->_x--;
    }
    if (keysCurrent() & KEY_RIGHT && this->_x < 224) {
        this->_x++;
    }
    if (keysCurrent() & KEY_UP && this->_y > 0) {
        this->_y--;
    }
    if (keysCurrent() & KEY_DOWN && this->_y < 160) {
        this->_y++;
    }
    NF_MoveSprite(_screen, _id, _x, _y);

    // Shoot
    // TODO: Spawn bullet when KEY_Y is pressed
}