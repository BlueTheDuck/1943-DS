#ifndef __ENTITY_H
#define __ENTITY_H

#include "helper.hpp"
#include "nf_lib.h"
#include <nds.h>

struct Size {
    u8 w;
    u8 h;
};

class Entity {
  protected:
    Screen      _screen;
    ScreenLayer _layer;
    u8          _id;
    u16         _gfx;
    u8          _pal;
    s16         _x = 0, _y = 0;

  public:
    /// Member initializer constructor
    Entity();
    Entity(Screen screen, ScreenLayer layer, u8 id, u16 gfx, u8 pal);
    ~Entity();

    /// Set animation frame
    void setFrame(u16 frame);

    /// Get X position
    s16 getX();
    /// Get Y position
    s16 getY();
    /// Set position
    void setPos(s16 x, s16 y);
    /// Get visibility
    bool isVisible();
    /// Set visibility
    void setVisibility(bool visible);
};

#endif