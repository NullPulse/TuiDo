#pragma once

#include <ncurses.h>
#include <string>
#include <fstream>
#include <vector>
#include "ToDoList.hpp"

void SettingsInit(int max_x, int max_y, std::string message) {
  clear();
  start_color();
  noecho();
  raw();
  curs_set(0);
  border('*', '*', '*', '*', '*', '*', '*', '*');
  mvprintw(0, 6, "TuiDo");
  move(max_y/2, max_x/2-message.size()/2);
  printw(message.data());
}

void Decorations() {
  border(0, 0, 0, 0, 0, 0, 0, 0);
  mvprintw(0, 10, "TuiDo");
}

void LineToStatus(std::string* line, bool* status) {
  std::string substring = line->substr(0,1);
  if(substring == "+") {
    *status = true;
  } else {
    *status = false;
  }
  *line = line->substr(1, line->size()-1);
}

void AddToFile(std::string task, std::string status, std::string filename) {
  std::ofstream file(filename, std::fstream::app);
  file << status << task << "\n";
}


void RemoveFromFile(bool status, std::string description, std::string filename) {
  char st;
  int c = 0;
  if(status) {
    st = '+';
  } else {
    st = '-';
  }
  std::fstream file(filename);
  std::ofstream tempfile("temp.todo");
  std::string line;
  while(file.is_open()) {
    while(std::getline(file, line)) {
      if(!(line[0] == st && line.substr(1, line.length()-1) == description)) {
        tempfile << line[0] << line.substr(1, line.length()-1) << '\n';
      } 
      c++;
    }
    std::remove(filename.data());
    std::rename("temp.todo", filename.data());
    std::remove("temp.todo");
    file.close();
  }
}


void CheckUncheckFromFile(bool status, std::string description, std::string filename) {
  char st;
  int c = 0;
  if(status) {
    st = '+';
  } else {
    st = '-';
  }
  std::fstream file(filename);
  std::ofstream tempfile("temp.todo");
  std::string line;
  while(file.is_open()) {
    while(std::getline(file, line)) {
      if(!(line[0] == st && line.substr(1, line.length()-1) == description)) {
        tempfile << line[0] << line.substr(1, line.length()-1) << '\n';
      } else {
        if(status) {
          tempfile << '-';
        } else {
          tempfile << '+';
        }
        tempfile << line.substr(1, line.length()-1) << '\n';
      } 
      c++;
    }
    std::remove(filename.data());
    std::rename("temp.todo", filename.data());
    std::remove("temp.todo");
    file.close();
  }
}

void PrintAllToDoList(std::vector<ToDoList> listOfToDoList, int x, int y) {
  for(ToDoList todolist : listOfToDoList) {
    if(todolist.getIsOpen()) {
      todolist.PrintList(x, y);
    }
  }
}
