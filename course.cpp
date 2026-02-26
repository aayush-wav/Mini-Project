#include "course.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

void CourseTable::addCourse(int id, std::string title, int teacherId) {
    Course c;
    c.courseId = id;
    c.title = title;
    c.teacherId = teacherId;
    table[id] = c;
}

void CourseTable::removeCourse(int id) {
    table.erase(id);
}

void CourseTable::enrollStudent(int courseId, int studentId) {
    if (table.find(courseId) == table.end())
        return;
    table[courseId].enrolledStudents.push_back(studentId);
}

void CourseTable::dropStudent(int courseId, int studentId) {
    if (table.find(courseId) == table.end())
        return;
    auto& v = table[courseId].enrolledStudents;
    v.erase(std::remove(v.begin(), v.end(), studentId), v.end());
}

Course* CourseTable::getCourse(int id) {
    if (table.find(id) == table.end())
        return nullptr;
    return &table[id];
}

void CourseTable::displayAll() {
    if (table.empty()) {
        std::cout << "No courses available.\n";
        return;
    }
    std::cout << std::left << std::setw(8) << "ID"
              << std::setw(25) << "Title"
              << std::setw(12) << "Teacher ID"
              << std::setw(10) << "Students" << "\n";
    std::cout << std::string(55, '-') << "\n";
    for (auto& pair : table) {
        Course& c = pair.second;
        std::cout << std::setw(8) << c.courseId
                  << std::setw(25) << c.title
                  << std::setw(12) << c.teacherId
                  << std::setw(10) << c.enrolledStudents.size() << "\n";
    }
}

void CourseTable::displayEnrolled(int courseId) {
    if (table.find(courseId) == table.end()) {
        std::cout << "Course not found.\n";
        return;
    }
    Course& c = table[courseId];
    std::cout << "Students in " << c.title << ": ";
    for (int sid : c.enrolledStudents)
        std::cout << sid << " ";
    std::cout << "\n";
}
