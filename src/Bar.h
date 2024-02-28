#include <ncurses.h>
#include "ToDoList.hpp"

class Bar {
  private:
    int itsX = 1;
    int itsY = 1;
    bool isOpen = false;
    char itsPrefix = ':';
  public:
    void PrintBar(ToDoList* mainlist, ToDoList* secondlist, int max_x, int max_y, int *curr_x, int *curr_y, bool editX);
    void RemoveBar(int max_x, int max_y, int *curr_x, int *curr_y);
    bool getIsOpen();
    void runCommand(char command[], ToDoList* mainlist, ToDoList* secondlist);
};
