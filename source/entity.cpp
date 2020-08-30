#include "entity.hpp"

Entity::Entity(Screen screen, ScreenLayer layer, u8 id, u16 gfx, u8 pal)
    : _screen(screen), _layer(layer), _id(id), _gfx(gfx), _pal(pal) {
    NF_CreateSprite(_screen, _id, _gfx, _pal, _x, _y);
}
Entity::~Entity() {
    NF_DeleteSprite(_screen, _id);
}

void Entity::setFrame(u16 frame) {
    NF_SpriteFrame(this->_screen, this->_id, frame);
}