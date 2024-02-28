#pragma once

#include "ToDoList.h"
#include "Utils.hpp"
#include <ncurses.h>

Task::Task(std::string description, bool status) {
  itsDescription = description;
  itsStatus = status;
}

std::string Task::getDescription() {
  return itsDescription;
}

bool Task::getStatus() {
  return itsStatus;
}

void Task::setDescription(std::string description) {
  itsDescription = description;
}

void Task::setStatus(bool status) {
  itsStatus = status;
}

ToDoList::ToDoList(std::string name, int* listCount) {
  itsName = name;
  itsIndex = *listCount;
  (*listCount)++;
}

std::string  ToDoList::getName() {
  return itsName;
}

int ToDoList::getIndex() {
  return itsIndex;
}


void ToDoList::InitializeList(std::vector<Task>* taskList, std::string filename) {
  std::string line;
  bool status;
  std::fstream file(filename);
  while(file.is_open()) {
    while(std::getline(file, line)) {
      LineToStatus(&line, &status);
      if(status) {
        taskList->push_back(Task(line, status));
      } else {
        taskList->insert(taskList->begin(), Task(line, status));
      }
    }
    file.close();
  }
}

void ToDoList::PrintList(int x, int y) {
  x = x+(60*itsIndex);
  int c = 0;
  init_pair(1, COLOR_WHITE, COLOR_GREEN);
  init_pair(2, COLOR_WHITE, COLOR_RED);
  init_pair(3, COLOR_WHITE, COLOR_BLUE);
  init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
  init_pair(5, COLOR_WHITE, COLOR_CYAN);
  attron(COLOR_PAIR(5));
  mvprintw(y-2, x, " %d ", itsIndex);
  attroff(COLOR_PAIR(5));
  attron(A_UNDERLINE);
  mvprintw(y-2, x+4, "%s", itsName.data());
  attroff(A_UNDERLINE);
  move(y, x);
  for(Task task : itsTaskList) {
    if(task.getStatus()) {
      attron(COLOR_PAIR(4));
      mvprintw(y, x, " %d ", c);
      attroff(COLOR_PAIR(4));
      attron(COLOR_PAIR(1));
      mvprintw(y, x+4, "  %s  ", "DONE");
      attroff(COLOR_PAIR(1));
      mvprintw(y++, x+13, "%s", task.getDescription().data());
    } else {
      attron(COLOR_PAIR(4));
      mvprintw(y, x, " %d ", c);
      attroff(COLOR_PAIR(4));
      attron(COLOR_PAIR(2));
      mvprintw(y, x+4, " %s ", "UNDONE");
      attroff(COLOR_PAIR(2));
      mvprintw(y++, x+13, "%s", task.getDescription().data());
    }
    refresh();
    c++;
  }
}

bool ToDoList::getIsOpen() {
  return isOpen;
}

void ToDoList::setIsOpen(bool status) {
  isOpen = status;
}

void ToDoList::RemoveTask(int taskIdx, std::string filename, ToDoList tasklist) {
  std::string task = tasklist.itsTaskList.at(taskIdx).getDescription();
  bool status = tasklist.itsTaskList.at(taskIdx).getStatus();
  RemoveFromFile(status, task, filename);
}

void ToDoList::CheckUncheckTask(int taskIdx, std::string filename, ToDoList tasklist) {
  std::string task = tasklist.itsTaskList.at(taskIdx).getDescription();
  bool status = tasklist.itsTaskList.at(taskIdx).getStatus();
  CheckUncheckFromFile(status, task, filename);
}

std::string ToDoList::getFile() {
  return itsFile;
}
