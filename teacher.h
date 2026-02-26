#pragma once
#include <string>
#include <vector>

struct Teacher {
    int id;
    std::string name;
    std::string subject;
    Teacher* left;
    Teacher* right;

    Teacher(int i, std::string n, std::string s);
};

class TeacherBST {
public:
    Teacher* root;

    TeacherBST();
    Teacher* insert(Teacher* node, int id, std::string name, std::string subject);
    void insert(int id, std::string name, std::string subject);
    Teacher* search(Teacher* node, int id);
    Teacher* search(int id);
    Teacher* minNode(Teacher* node);
    Teacher* deleteNode(Teacher* node, int id);
    void remove(int id);
    void inorder(Teacher* node);
    void displayAll();
};
