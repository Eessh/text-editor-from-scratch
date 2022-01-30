#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <allegro5/allegro_font.h>
#include "Rectangle.hpp"
#include "TextBlock.hpp"

typedef enum Command {
  MOVE_CURSOR_LEFT,
  MOVE_CURSOR_RIGHT,
  MOVE_CURSOR_UP,
  MOVE_CURSOR_DOWN,
  BACKSPACE,
  ENTER,
  INSERT
} Command;

class Doc {
  private:
  std::vector<std::string> text;
  typedef struct Cursor {
    long unsigned int row;
    long unsigned int col;
  } Cursor;
  Cursor cursor;
  Rectangle* cursorRect;

  public:
  Doc();
  Doc(const std::vector<std::string>& initText);

  void executeCommand(const Command& command, const char& c = '\0');

  void insert(const int& row, const int& col, const char& c);
  void backspace(const int& row, const int& col);
  void createRowAfter(const int& row);

  inline std::vector<std::string> toTextBlocks() {return text;}

  void render(ALLEGRO_FONT* font, const float& horizontalPadding, const float& verticalPadding);

  void log();
};