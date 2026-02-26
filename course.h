#pragma once
#include <string>
#include <unordered_map>
#include <vector>

struct Course {
    int courseId;
    std::string title;
    int teacherId;
    std::vector<int> enrolledStudents;
};

class CourseTable {
    std::unordered_map<int, Course> table;

public:
    void addCourse(int id, std::string title, int teacherId);
    void removeCourse(int id);
    void enrollStudent(int courseId, int studentId);
    void dropStudent(int courseId, int studentId);
    Course* getCourse(int id);
    void displayAll();
    void displayEnrolled(int courseId);
};
