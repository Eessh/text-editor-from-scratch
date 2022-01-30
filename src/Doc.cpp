#include "../include/Doc.hpp"

Doc::Doc() {
  text.push_back("");
  cursor.row = 0;
  cursor.col = 0;
  cursorRect = nullptr;
}
Doc::Doc(const std::vector<std::string>& initText) {
  text = initText;
  cursor.row = 0;
  cursor.col = 0;
  cursorRect = nullptr;
}

void Doc::executeCommand(const Command& command, const char& c) {
  switch(command) {
    case MOVE_CURSOR_LEFT:
      if (cursor.col == 0) {
        if (cursor.row != 0) {
          cursor.row -= 1;
          cursor.col = text[cursor.row].size();
        }
      }
      else {
        // std::cout << "Doc:Left\n";
        cursor.col -= 1;
        // std::cout << "Doc:Cursor: {" << cursor.row << ", " << cursor.col << "}\n";
      }
      break;
    case MOVE_CURSOR_RIGHT:
      if (cursor.col == text[cursor.row].size()) {
        if (cursor.row < text.size()-1) {
          cursor.row += 1;
          cursor.col = 0;
        }
      }
      else {
        // std::cout << "Doc:Right\n";
        cursor.col += 1;
        // std::cout << "Doc:Cursor: {" << cursor.row << ", " << cursor.col << "}\n";
      }
      break;
    case MOVE_CURSOR_UP:
      if (cursor.row != 0) {
        if (cursor.col > text[cursor.row-1].size())
          cursor.col = text[cursor.row-1].size();
        // std::cout << "Doc:Up\n";
        cursor.row -= 1;
        // std::cout << "Doc:Cursor: {" << cursor.row << ", " << cursor.col << "}\n";
      }
      break;
    case MOVE_CURSOR_DOWN:
      if (cursor.row != text.size()-1) {
        if (cursor.col > text[cursor.row+1].size())
          cursor.col = text[cursor.row+1].size();
        // std::cout << "Doc:Down\n";
        cursor.row += 1;
        // std::cout << "Doc:Cursor: {" << cursor.row << ", " << cursor.col << "}\n";
      }
      break;
    case BACKSPACE:
      if (cursor.col == 0) {
        if (cursor.row != 0) {
          if (text[cursor.row].empty()) {
            text.erase(text.begin()+cursor.row);
            cursor.row -= 1;
            cursor.col = text[cursor.row].size();
          }
          else {
            const std::string temp = text[cursor.row];
            text.erase(text.begin()+cursor.row);
            cursor.row -= 1;
            text[cursor.row] += temp;
            cursor.col = text[cursor.row].size();
          }
        }
      }
      else {
        backspace(cursor.row, cursor.col);
        cursor.col -= 1;
      }
      break;
    case ENTER:
      createRowAfter(cursor.row);
      cursor.row += 1;
      cursor.col = 0;
      break;
    case INSERT:
      insert(cursor.row, cursor.col, c);
      cursor.col += 1;
      break;
    default:
      break;
  }
  return;
}

void Doc::insert(const int& row, const int& col, const char& c) {
  text[row].insert(text[row].begin()+col, c);
  return;
}

void Doc::backspace(const int& row, const int& col) {
  text[row].erase(col-1, 1);
  return;
}

void Doc::createRowAfter(const int& row) {
  text.insert(text.begin()+row+1, "");
  return;
}

std::string numtoStr(const long unsigned int& n) {
  std::string s;
  long unsigned int num = n;
  int rem = 0;
  while (num != 0) {
    rem = num % 10;
    s.insert(s.begin(), rem==0 ? '0' : (char)(48+rem));
    num /= 10;
  }
  return s;
}
int digits(const long unsigned int& n) {
  long unsigned int num = n;
  int digits = 0;
  while (num != 0) {
    num /= 10;
    digits += 1;
  }
  return digits;
}
std::string getLineNumberStr(const long unsigned int& n, const long unsigned int& maxLineNumber) {
  int currDigits = digits(n);
  int maxDigits = digits(maxLineNumber);
  std::string s = numtoStr(n);
  while (currDigits != maxDigits) {
    s.push_back(' ');
    currDigits += 1;
  }
  return s;
}
void Doc::render(ALLEGRO_FONT* font, const float& horizontalPadding, const float& verticalPadding) {
  float x = 0, y = 0;
  float fontHeight = al_get_font_line_height(font);
  float fontWidth = al_get_text_width(font, "e");
  float cellWidth = fontWidth+2*horizontalPadding;
  float lineHeight = fontHeight+2*verticalPadding;
  float lineNumberWidth = al_get_text_width(font, numtoStr(text.size()-1).c_str());
  TextBlock* textBlock = new TextBlock(text[0]);
  TextBlock* lineNumberBlock = new TextBlock("0");
  for (long unsigned int i = 0; i < text.size(); i++) {
    textBlock->text = text[i];
    lineNumberBlock->text = getLineNumberStr(i, text.size()-1);
    // lineNumberBlock->render(x, y, horizontalPadding, verticalPadding, font);
    textBlock->render(x, y, horizontalPadding, verticalPadding, font);
    // textBlock->render(x+lineNumberWidth, y, horizontalPadding, verticalPadding, font);
    y += lineHeight;
  }
  // cursorRect = new Rectangle(cellWidth, lineHeight);
  cursorRect = new Rectangle(2, lineHeight);
  cursorRect->render((cursor.col)*cellWidth, (cursor.row)*lineHeight, al_map_rgb(102, 204, 255));
  delete(textBlock);
  delete(lineNumberBlock);
  delete(cursorRect);
  return;
}

void Doc::log() {
  std::cout << "Doc:\n\t";
  for (int i = 0; i < (int)text.size(); i++)
    std::cout << i << "| " << text[i] << "\n\t";
  std::cout << "\n";
  return;
}