cmake_minimum_required(VERSION 3.16)
project(SchoolManagementSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCES
    main.cpp
    mainwindow.cpp
    student.cpp
    teacher.cpp
    course.cpp
    queue.cpp
)

set(HEADERS
    mainwindow.h
    student.h
    teacher.h
    course.h
    queue.h
)

set(UI_FILES
    mainwindow.ui
)

add_executable(SchoolManagementSystem ${SOURCES} ${HEADERS} ${UI_FILES})
target_link_libraries(SchoolManagementSystem Qt5::Widgets)
