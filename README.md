# School Management System

A desktop application built with C++ and Qt5 for managing students, teachers, courses, and fee records.

## Features

- Add, remove, and search students
- Add, remove, and search teachers
- Create courses and enroll students
- Fee payment queue with sequential processing
- Undo last student admission

## Data Structures Used

| Module | Structure | Purpose |
|--------|-----------|---------|
| Students | Linked List | Dynamic student records |
| Teachers | Binary Search Tree | Sorted teacher lookup by ID |
| Courses | Hash Map | O(1) course access by ID |
| Fees | Queue | First-come first-served payment processing |
| Undo | Stack | Reverse last admission action |

## Build Instructions

Requires Qt5 and CMake 3.16+.

```bash
mkdir build && cd build
cmake ..
make
./SchoolManagementSystem
```

## Project Structure

```
school_mgmt/
├── CMakeLists.txt
├── main.cpp
├── mainwindow.h / mainwindow.cpp
├── mainwindow.ui
├── student.h / student.cpp
├── teacher.h / teacher.cpp
├── course.h / course.cpp
├── queue.h / queue.cpp
└── README.md
```
