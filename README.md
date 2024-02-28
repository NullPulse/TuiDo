# TuiDo 📝
TuiDo is a terminal-based todo manager inspired by Vim's interface. 

</p><p align="center">
  <img src="image/video.gif"> <br>
    <img src="https://img.shields.io/badge/release-v0.0.1-green" alt=""/> <img src="https://img.shields.io/badge/written in-C++-pink" alt=""/> <img src="https://img.shields.io/badge/written by-NullPulse-red" alt=""/>

</p>
<br>

### Usage

TuiDo offers a variety of commands to efficiently manage your todo lists. Here's a breakdown of the available commands:

#### Adding a Task

To add a new task to your todo list, use the `new` command followed by the index of the list and the task description:

```bash
:new <list_index> <task_description>
```
_Replace `<list_index>` with the index of the list where you want to add the task (0 or 1)._

#### Delating a Task

To delete a task from your todo list, use the del command followed by the index of the list and the index of the task:

```bash
:del <list_index> <task_index>
```

_Replace `<list_index>` with the index of the list where the task is located._

#### Changing Task Status

To change the status of a task (mark it as done or undone), use the ch command followed by the indices of the list and the task:

```
:ch <list_index> <task_index>
```

_Replace `<list_index>` and `<task_index>` with the appropriate indices._

#### Showing/Hiding Task Lists

You can show or hide specific task lists using the sh command followed by the index of the list:

```bash
:sh <list_index>
```

_Replace `<list_index>` with the index of the list you want to show or hide._

### Installation

Clone the repository to your local machine:

`git clone https://github.com/NullPulse/TuiDo`

Navigate to the TuiDo directory:

`cd TuiDo`

Compile the program:

`./build.sh`

Run TuiDo:

`./TuiDo`

#### Feedback

If you encounter any issues or have suggestions for improvements, please don't hesitate to open an [issue](https://github.com/NullPulse/TuiDo/issues).
