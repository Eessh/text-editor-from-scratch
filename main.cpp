#include <iostream>
#include <vector>
#include <string>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "include/Rectangle.hpp"
#include "include/TextBlock.hpp"
#include "include/Doc.hpp"

using namespace std;

ALLEGRO_TIMER* timer = nullptr;
ALLEGRO_EVENT_QUEUE* queue = nullptr;
ALLEGRO_DISPLAY* disp = nullptr;
ALLEGRO_FONT* font = nullptr;
bool init();
bool check();
void deallocate();

int main() {
  if (!init()) return 1;
	timer = al_create_timer(1.0 / 30.0);
	queue = al_create_event_queue();
	disp = al_create_display(1080, 720);
	// font = al_create_builtin_font();
	font = al_load_ttf_font("res/Iosevka.ttf", 24, ALLEGRO_TTF_NO_AUTOHINT);
  if (!check()) return 1;
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	bool done = false;
	bool redraw = true;
	ALLEGRO_EVENT event;

  // Rectangle* rect = new Rectangle(40, 30);
  // TextBlock* text = new TextBlock("hola");
  Doc* doc = new Doc({"line1", "line2", "line3", "line4", "Abey saale"});

  al_start_timer(timer);
  while (!done) {
    al_wait_for_event(queue, &event);
    switch(event.type) {
      case ALLEGRO_EVENT_DISPLAY_CLOSE:
        redraw = false;
        done = true;
        break;
      case ALLEGRO_EVENT_TIMER:
        // redraw = true;
        break;
      case ALLEGRO_EVENT_KEY_CHAR:
        if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
          // cout << "Left\n";
					doc->executeCommand(MOVE_CURSOR_LEFT);
        }
				else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
          // cout << "Right\n";
					doc->executeCommand(MOVE_CURSOR_RIGHT);
        }
				else if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
          // cout << "Up\n";
					doc->executeCommand(MOVE_CURSOR_UP);
        }
				else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
          // cout << "Down\n";
					doc->executeCommand(MOVE_CURSOR_DOWN);
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
          // cout << "Backspace\n";
          doc->executeCommand(BACKSPACE);
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_ENTER || event.keyboard.keycode == ALLEGRO_KEY_PAD_ENTER) {
          // cout << "Enter\n";
          doc->executeCommand(ENTER);
        }
        else if(1<=event.keyboard.keycode && event.keyboard.keycode<=26) {
          // cout << "Insert\n";
          if (event.keyboard.modifiers == ALLEGRO_KEYMOD_SHIFT)
            doc->executeCommand(INSERT, event.keyboard.keycode+64);
          else
            doc->executeCommand(INSERT, event.keyboard.keycode+96);
        }
        else if (28<=event.keyboard.keycode && event.keyboard.keycode<=36) {
          // cout << "Insert\n";
          doc->executeCommand(INSERT, event.keyboard.keycode+21);
        }
        else if (37<=event.keyboard.keycode && event.keyboard.keycode<=46) {
          // cout << "Insert\n";
          doc->executeCommand(INSERT, event.keyboard.keycode+11);
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_TILDE) {
          // cout << "Insert\n";
          doc->executeCommand(INSERT, '`');
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_MINUS || event.keyboard.keycode == ALLEGRO_KEY_PAD_MINUS) {
          // cout << "Insert\n";
          doc->executeCommand(INSERT, '-');
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_EQUALS || event.keyboard.keycode == ALLEGRO_KEY_PAD_EQUALS) {
          // cout << "Insert\n";
          doc->executeCommand(INSERT, '=');
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_TAB) {
          // cout << "Insert\n";
          doc->executeCommand(INSERT, ' ');
          doc->executeCommand(INSERT, ' ');
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_OPENBRACE) {
          // cout << "Insert\n";
          doc->executeCommand(INSERT, '{');
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_CLOSEBRACE) {
          // cout << "Insert\n";
          doc->executeCommand(INSERT, '}');
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_SEMICOLON) {
          // cout << "Insert\n";
          doc->executeCommand(INSERT, ';');
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_QUOTE) {
          // cout << "Insert\n";
          doc->executeCommand(INSERT, (char)44);
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_BACKSLASH) {
          // cout << "Insert\n";
          doc->executeCommand(INSERT, (char)92);
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_BACKSLASH2) {
          // cout << "Insert\n";
          doc->executeCommand(INSERT, '|');
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_COMMA) {
          // cout << "Insert\n";
          doc->executeCommand(INSERT, ',');
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_FULLSTOP) {
          // cout << "Insert\n";
          doc->executeCommand(INSERT, '.');
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_SLASH || event.keyboard.keycode == ALLEGRO_KEY_PAD_SLASH) {
          // cout << "Insert\n";
          doc->executeCommand(INSERT, '/');
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_SPACE) {
          // cout << "Insert\n";
          doc->executeCommand(INSERT, ' ');
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_PAD_ASTERISK) {
          // cout << "Insert\n";
          doc->executeCommand(INSERT, '*');
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_PAD_PLUS) {
          // cout << "Insert\n";
          doc->executeCommand(INSERT, '+');
        }

        redraw = true;
        break;
      default:
        // redraw = false;
        break;
    }
    if (redraw && al_event_queue_is_empty(queue)) {
      al_clear_to_color(al_map_rgb(50, 50, 50));
      
      // rect->render(20, 20);
      // text->render(100, 100, 0, 0, font);
      doc->render(font, 0, 0);
      // doc->log();

      al_flip_display();
      redraw = false;
    }
  }
  // delete(rect);
  // delete(text);
  delete(doc);
  deallocate();

  return 0;
}

bool init() {
	if(!al_init()) {
		cout << "couldn't initialize allegro\n";
		return false;
	}
	if(!al_install_keyboard()) {
		cout << "couldn't initialize keyboard\n";
		return false;
	}
	if(!al_init_ttf_addon()) {
		cout << "couldn't initialize ttf_addon\n";
		return false;
	}
	if(!al_init_primitives_addon()) {
		cout << "couldn't initialize primitives_addon\n";
		return false;
	}
	return true;
}
bool check() {
	if(!timer) {
		cout << "couldn't initialize timer\n";
		return false;
	}
	if(!queue) {
		cout << "couldn't initialize queue\n";
		return false;
	}
	if(!disp) {
		cout << "couldn't initialize display\n";
		return false;
	}
	if(!font) {
		cout << "couldn't initialize font\n";
		return false;
	}
	return true;
}
void deallocate() {
	al_shutdown_ttf_addon();
	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
}