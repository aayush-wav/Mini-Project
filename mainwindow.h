#pragma once
#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTabWidget>
#include <stack>
#include "student.h"
#include "teacher.h"
#include "course.h"
#include "queue.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onAddStudent();
    void onRemoveStudent();
    void onSearchStudent();
    void onAddTeacher();
    void onRemoveTeacher();
    void onSearchTeacher();
    void onAddCourse();
    void onEnrollStudent();
    void onProcessFee();
    void onAddFeeRecord();
    void onUndoAdmission();
    void refreshStudentTable();
    void refreshTeacherTable();
    void refreshCourseTable();
    void refreshFeeQueue();

private:
    Ui::MainWindow* ui;
    StudentList studentList;
    TeacherBST teacherBST;
    CourseTable courseTable;
    FeeQueue feeQueue;
    std::stack<Student*> undoStack;
    int nextStudentId;
    int nextTeacherId;
    int nextCourseId;

    void setupConnections();
    void showMessage(const QString& msg);
};
