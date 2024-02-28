#include "Bar.hpp"
#include "Utils.hpp"

int main() {

  initscr();

  Bar bar;
  int max_x, max_y;
  int curr_x, curr_y;
  bool quit = false;
  char in;
  int listCount = 0; 
  int todo_x, todo_y;
  
  getmaxyx(stdscr, max_y, max_x);
  SettingsInit(max_x, max_y, "Press any key to start.");

  ToDoList maintask("Main Task", &listCount);
  ToDoList secondarytask("Secondary Task", &listCount);

  while(!quit) {
    todo_x = 4, todo_y = 4;
    clear();

    maintask.itsTaskList.clear();
    maintask.InitializeList(&maintask.itsTaskList, ".config.todo");
    

    secondarytask.itsTaskList.clear();
    secondarytask.InitializeList(&secondarytask.itsTaskList, ".config2.todo");

    std::vector<ToDoList> AllToDoList {maintask, secondarytask};

    PrintAllToDoList(AllToDoList, todo_x, todo_y);
    Decorations();

    in = getch();

    clear();

    getmaxyx(stdscr, max_y, max_x);

    if(bar.getIsOpen()) {
      bar.PrintBar(&maintask, &secondarytask, max_x, max_y, &curr_x, &curr_y, false);
    }

    Decorations();
  
    switch(in) {
      case ':':
        if(bar.getIsOpen()) {
          bar.RemoveBar(max_x, max_y, &curr_x, &curr_y);
          PrintAllToDoList(AllToDoList, todo_x, todo_y);
        } else {
          PrintAllToDoList(AllToDoList, todo_x, todo_y);
          bar.PrintBar(&maintask, &secondarytask, max_x, max_y, &curr_x, &curr_y, true);
        }
        break;
    }
  }
}
