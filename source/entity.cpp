#include "entity.hpp"

Entity::Entity(){};
Entity::Entity(Screen screen, ScreenLayer layer, u8 id, u16 gfx, u8 pal)
    : _screen(screen), _layer(layer), _id(id), _gfx(gfx), _pal(pal) {
    NF_CreateSprite(_screen, _id, _gfx, _pal, _x, _y);
}
Entity::~Entity() {
    // Check if this sprite was actually creaded (Or was just a dummy placeholder)
    if (NF_SPRITEOAM[_screen][_id].created)
        NF_DeleteSprite(_screen, _id);
}

void Entity::setFrame(u16 frame) {
    NF_SpriteFrame(this->_screen, this->_id, frame);
}

s16  Entity::getX() { return this->_x; }
s16  Entity::getY() { return this->_y; }
void Entity::setPos(s16 x, s16 y) {
    this->_x = x;
    this->_y = y;
    NF_MoveSprite(this->_screen, this->_id, x, y);
}

bool Entity::isVisible() { return !NF_SPRITEOAM[_screen][_id].hide; }
void Entity::setVisibility(bool visible) {
    NF_SPRITEOAM[_screen][_id].hide = !visible;
}
