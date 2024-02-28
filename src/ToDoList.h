#include <vector>
#include <string>
#include <fstream>

class Task {
  private: 
    bool itsStatus; 
    std::string itsDescription; 
  public:
    Task(std::string description, bool status);
    std::string getDescription();
    bool getStatus();
    void setStatus(bool status);
    void setDescription(std::string description);
};

class ToDoList {
  private:
    std::string itsFile;
    std::string itsName;
    bool isOpen = true;
    int itsIndex;

  public:
    std::vector<Task> itsTaskList; 
    ToDoList(std::string name, int *listCount);
    std::string getName();
    void setIsOpen(bool status);
    void setFile(std::string name) {itsFile = name;}
    bool getIsOpen();
    std::string getFile();
    int getIndex();
    void InitializeList(std::vector<Task>* taskList, std::string filename);
    void PrintList(int x, int y);
    void RemoveTask(int taskIdx, std::string filename, ToDoList tasklist);
    void CheckUncheckTask(int taskIdx, std::string filename, ToDoList tasklist);
};
