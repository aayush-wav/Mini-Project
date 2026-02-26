#include "teacher.h"
#include <iostream>
#include <iomanip>

Teacher::Teacher(int i, std::string n, std::string s)
    : id(i), name(n), subject(s), left(nullptr), right(nullptr) {}

TeacherBST::TeacherBST() : root(nullptr) {}

Teacher* TeacherBST::insert(Teacher* node, int id, std::string name, std::string subject) {
    if (!node)
        return new Teacher(id, name, subject);
    if (id < node->id)
        node->left = insert(node->left, id, name, subject);
    else if (id > node->id)
        node->right = insert(node->right, id, name, subject);
    return node;
}

void TeacherBST::insert(int id, std::string name, std::string subject) {
    root = insert(root, id, name, subject);
}

Teacher* TeacherBST::search(Teacher* node, int id) {
    if (!node || node->id == id)
        return node;
    if (id < node->id)
        return search(node->left, id);
    return search(node->right, id);
}

Teacher* TeacherBST::search(int id) {
    return search(root, id);
}

Teacher* TeacherBST::minNode(Teacher* node) {
    while (node->left)
        node = node->left;
    return node;
}

Teacher* TeacherBST::deleteNode(Teacher* node, int id) {
    if (!node)
        return nullptr;
    if (id < node->id)
        node->left = deleteNode(node->left, id);
    else if (id > node->id)
        node->right = deleteNode(node->right, id);
    else {
        if (!node->left) {
            Teacher* tmp = node->right;
            delete node;
            return tmp;
        }
        if (!node->right) {
            Teacher* tmp = node->left;
            delete node;
            return tmp;
        }
        Teacher* succ = minNode(node->right);
        node->id = succ->id;
        node->name = succ->name;
        node->subject = succ->subject;
        node->right = deleteNode(node->right, succ->id);
    }
    return node;
}

void TeacherBST::remove(int id) {
    root = deleteNode(root, id);
}

void TeacherBST::inorder(Teacher* node) {
    if (!node)
        return;
    inorder(node->left);
    std::cout << std::left << std::setw(6) << node->id
              << std::setw(20) << node->name
              << std::setw(15) << node->subject << "\n";
    inorder(node->right);
}

void TeacherBST::displayAll() {
    if (!root) {
        std::cout << "No teachers on record.\n";
        return;
    }
    std::cout << std::left << std::setw(6) << "ID"
              << std::setw(20) << "Name"
              << std::setw(15) << "Subject" << "\n";
    std::cout << std::string(41, '-') << "\n";
    inorder(root);
}
