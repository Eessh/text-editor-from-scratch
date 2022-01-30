#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class Rectangle {
  public:
  float w;
  float h;
  ALLEGRO_COLOR color;

  Rectangle(const float& width, const float& height): w(width), h(height) {}

  void render(
    const float& xCoord, const float& yCoord,
    ALLEGRO_COLOR rectColor = al_map_rgb(0, 0, 0)
  );
};