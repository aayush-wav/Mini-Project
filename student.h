#pragma once
#include <string>
#include <unordered_map>

struct Student {
    int id;
    std::string name;
    int age;
    std::string grade;
    std::unordered_map<std::string, float> marks;
    Student* next;

    Student(int i, std::string n, int a, std::string g);
};

class StudentList {
public:
    Student* head;
    int count;

    StudentList();
    void insert(Student* s);
    void remove(int id);
    Student* find(int id);
    void display();
};
