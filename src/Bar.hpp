#include "Bar.h"
#include <ncurses.h>
#include <string>


void Bar::PrintBar(ToDoList* mainlist, ToDoList* secondlist, int max_x, int max_y, int *curr_x, int *curr_y, bool editX) {
  curs_set(1);
  char command[64];
  for(int x = 0; x < 64; x++) {command[x] = '|';}
  isOpen = true;
  int current_position = 0;
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  move(max_y-2, 1);
  attron(A_REVERSE);
  hline(' ', max_x-2);
  move(max_y-2, 1);
  addch(itsPrefix);
  attroff(A_REVERSE);
  *curr_y = max_y-2;
  if(editX) {
    *curr_x = 1;
  }
  int c = *curr_x+1;
  attron(COLOR_PAIR(1));
  bool exitbar = false;
  char in;
  while(!exitbar) {
    in = getch();
    switch(in) {
      // case esc
      // case enter
      case '\n': // change
        exitbar = true;
        current_position++;
        attroff(COLOR_PAIR(1));
        RemoveBar(max_x, max_y, curr_x, curr_y);
        curs_set(0);
        runCommand(command, mainlist, secondlist);
        break;
      case 27: // change
        exitbar = true;
        attroff(COLOR_PAIR(1));
        RemoveBar(max_x, max_y, curr_x, curr_y);
        break;
      case 127:
        if(c== 2) {
          continue;
        }
        current_position--;
        command[current_position] = ' ';
        c = c - 1;
        move(max_y-2, c);
        addch(' ');
        move(max_y-2, c);
        break;
      default:
        if(c >= 128) {
          continue;
        }
        current_position++;
        command[current_position-1] = in;
        c++;
        curr_x++;
        addch(in);
    }
  }
}

void Bar::RemoveBar(int max_x, int max_y, int *curr_x, int *curr_y) {
  clear();
  isOpen = false;
  move(max_y-2, 1);
  hline(' ', max_x-2);
}

bool Bar::getIsOpen() {
  return isOpen;
}

void Bar::runCommand(char command[], ToDoList* mainlist, ToDoList* secondlist) {
  std::string s(command);
  std::string file;
  ToDoList* target = 0;
  if(s.substr(4, 1) == "0") {
    file = ".config.todo";
    target = mainlist;
  } else if(s.substr(4,1) == "1") {
    file = ".config2.todo";
    target = secondlist;
  }

  if(s.substr(0, 1) == "q") {
    endwin();
    exit(0);
  } else if(s.substr(0,3) == "new") {
    int length = 0;
    for(int x = 3; x < 64; x++) {
      if(command[x] == '|') {
        break;
      } else {
        length++;
      }
    }
    AddToFile(s.substr(6, length-3), "-", file);
  } else if(s.substr(0,3) == "del") {
    mainlist->RemoveTask(std::stoi(s.substr(6, 1)), file,  *target);
  } else if(s.substr(0,2) == "ch") {
    if(s.substr(3,1) == "0") {
      target = mainlist;
      file = ".config.todo";
    } else {
      target = secondlist;
      file = ".config2.todo";
    }
    mainlist->CheckUncheckTask(std::stoi(s.substr(5,1)), file, *target);
  } else if(s.substr(0,2) == "sh") {
    if(s.substr(3,1) == "0") {
      if(mainlist->getIsOpen()) {
        mainlist->setIsOpen(false);
      } else {
        mainlist->setIsOpen(true);
      }
    } else if(s.substr(3,1) == "1") {
      if(secondlist->getIsOpen()) {
        secondlist->setIsOpen(false);
      } else {
        secondlist->setIsOpen(true);
      }
    }
  }
}
