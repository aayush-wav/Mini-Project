#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QString>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      nextStudentId(1001),
      nextTeacherId(2001),
      nextCourseId(3001)
{
    ui->setupUi(this);
    setupConnections();
    refreshStudentTable();
    refreshTeacherTable();
    refreshCourseTable();
    refreshFeeQueue();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupConnections() {
    connect(ui->btnAddStudent, &QPushButton::clicked, this, &MainWindow::onAddStudent);
    connect(ui->btnRemoveStudent, &QPushButton::clicked, this, &MainWindow::onRemoveStudent);
    connect(ui->btnSearchStudent, &QPushButton::clicked, this, &MainWindow::onSearchStudent);
    connect(ui->btnUndoAdmission, &QPushButton::clicked, this, &MainWindow::onUndoAdmission);
    connect(ui->btnAddTeacher, &QPushButton::clicked, this, &MainWindow::onAddTeacher);
    connect(ui->btnRemoveTeacher, &QPushButton::clicked, this, &MainWindow::onRemoveTeacher);
    connect(ui->btnSearchTeacher, &QPushButton::clicked, this, &MainWindow::onSearchTeacher);
    connect(ui->btnAddCourse, &QPushButton::clicked, this, &MainWindow::onAddCourse);
    connect(ui->btnEnrollStudent, &QPushButton::clicked, this, &MainWindow::onEnrollStudent);
    connect(ui->btnAddFeeRecord, &QPushButton::clicked, this, &MainWindow::onAddFeeRecord);
    connect(ui->btnProcessFee, &QPushButton::clicked, this, &MainWindow::onProcessFee);
}

void MainWindow::onAddStudent() {
    bool ok;
    QString name = QInputDialog::getText(this, "Add Student", "Name:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;
    int age = QInputDialog::getInt(this, "Add Student", "Age:", 10, 5, 30, 1, &ok);
    if (!ok) return;
    QString grade = QInputDialog::getText(this, "Add Student", "Grade:", QLineEdit::Normal, "", &ok);
    if (!ok || grade.isEmpty()) return;

    Student* s = new Student(nextStudentId++, name.toStdString(), age, grade.toStdString());
    studentList.insert(s);
    undoStack.push(s);
    feeQueue.enqueue(s->id, s->name, 5000.0f);

    refreshStudentTable();
    refreshFeeQueue();
    showMessage("Student added with ID: " + QString::number(s->id));
}

void MainWindow::onRemoveStudent() {
    bool ok;
    int id = QInputDialog::getInt(this, "Remove Student", "Enter Student ID:", 1001, 1, 99999, 1, &ok);
    if (!ok) return;
    if (!studentList.find(id)) {
        showMessage("Student not found.");
        return;
    }
    studentList.remove(id);
    refreshStudentTable();
    showMessage("Student removed.");
}

void MainWindow::onSearchStudent() {
    bool ok;
    int id = QInputDialog::getInt(this, "Search Student", "Enter Student ID:", 1001, 1, 99999, 1, &ok);
    if (!ok) return;
    Student* s = studentList.find(id);
    if (!s) {
        showMessage("Student not found.");
        return;
    }
    QString info = "ID: " + QString::number(s->id) +
                   "\nName: " + QString::fromStdString(s->name) +
                   "\nAge: " + QString::number(s->age) +
                   "\nGrade: " + QString::fromStdString(s->grade);
    QMessageBox::information(this, "Student Found", info);
}

void MainWindow::onUndoAdmission() {
    if (undoStack.empty()) {
        showMessage("Nothing to undo.");
        return;
    }
    Student* s = undoStack.top();
    undoStack.pop();
    studentList.remove(s->id);
    refreshStudentTable();
    showMessage("Admission of " + QString::fromStdString(s->name) + " undone.");
    delete s;
}

void MainWindow::onAddTeacher() {
    bool ok;
    QString name = QInputDialog::getText(this, "Add Teacher", "Name:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;
    QString subject = QInputDialog::getText(this, "Add Teacher", "Subject:", QLineEdit::Normal, "", &ok);
    if (!ok || subject.isEmpty()) return;

    teacherBST.insert(nextTeacherId++, name.toStdString(), subject.toStdString());
    refreshTeacherTable();
    showMessage("Teacher added with ID: " + QString::number(nextTeacherId - 1));
}

void MainWindow::onRemoveTeacher() {
    bool ok;
    int id = QInputDialog::getInt(this, "Remove Teacher", "Enter Teacher ID:", 2001, 1, 99999, 1, &ok);
    if (!ok) return;
    if (!teacherBST.search(id)) {
        showMessage("Teacher not found.");
        return;
    }
    teacherBST.remove(id);
    refreshTeacherTable();
    showMessage("Teacher removed.");
}

void MainWindow::onSearchTeacher() {
    bool ok;
    int id = QInputDialog::getInt(this, "Search Teacher", "Enter Teacher ID:", 2001, 1, 99999, 1, &ok);
    if (!ok) return;
    Teacher* t = teacherBST.search(id);
    if (!t) {
        showMessage("Teacher not found.");
        return;
    }
    QString info = "ID: " + QString::number(t->id) +
                   "\nName: " + QString::fromStdString(t->name) +
                   "\nSubject: " + QString::fromStdString(t->subject);
    QMessageBox::information(this, "Teacher Found", info);
}

void MainWindow::onAddCourse() {
    bool ok;
    QString title = QInputDialog::getText(this, "Add Course", "Course Title:", QLineEdit::Normal, "", &ok);
    if (!ok || title.isEmpty()) return;
    int teacherId = QInputDialog::getInt(this, "Add Course", "Assign Teacher ID:", 2001, 1, 99999, 1, &ok);
    if (!ok) return;

    courseTable.addCourse(nextCourseId++, title.toStdString(), teacherId);
    refreshCourseTable();
    showMessage("Course added with ID: " + QString::number(nextCourseId - 1));
}

void MainWindow::onEnrollStudent() {
    bool ok;
    int courseId = QInputDialog::getInt(this, "Enroll Student", "Course ID:", 3001, 1, 99999, 1, &ok);
    if (!ok) return;
    int studentId = QInputDialog::getInt(this, "Enroll Student", "Student ID:", 1001, 1, 99999, 1, &ok);
    if (!ok) return;

    courseTable.enrollStudent(courseId, studentId);
    refreshCourseTable();
    showMessage("Student enrolled.");
}

void MainWindow::onAddFeeRecord() {
    bool ok;
    int studentId = QInputDialog::getInt(this, "Fee Record", "Student ID:", 1001, 1, 99999, 1, &ok);
    if (!ok) return;
    Student* s = studentList.find(studentId);
    if (!s) {
        showMessage("Student not found.");
        return;
    }
    double amount = QInputDialog::getDouble(this, "Fee Record", "Amount:", 1000, 0, 100000, 2, &ok);
    if (!ok) return;

    feeQueue.enqueue(studentId, s->name, static_cast<float>(amount));
    refreshFeeQueue();
    showMessage("Fee record added to queue.");
}

void MainWindow::onProcessFee() {
    if (feeQueue.isEmpty()) {
        showMessage("No pending fee records.");
        return;
    }
    FeeRecord* rec = feeQueue.dequeue();
    showMessage("Processed fee of " + QString::number(rec->amount) +
                " for " + QString::fromStdString(rec->studentName));
    delete rec;
    refreshFeeQueue();
}

void MainWindow::refreshStudentTable() {
    ui->tableStudents->setRowCount(0);
    ui->tableStudents->setColumnCount(4);
    ui->tableStudents->setHorizontalHeaderLabels({"ID", "Name", "Age", "Grade"});
    Student* cur = studentList.head;
    int row = 0;
    while (cur) {
        ui->tableStudents->insertRow(row);
        ui->tableStudents->setItem(row, 0, new QTableWidgetItem(QString::number(cur->id)));
        ui->tableStudents->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(cur->name)));
        ui->tableStudents->setItem(row, 2, new QTableWidgetItem(QString::number(cur->age)));
        ui->tableStudents->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(cur->grade)));
        cur = cur->next;
        row++;
    }
}

void MainWindow::refreshTeacherTable() {
    ui->tableTeachers->setRowCount(0);
    ui->tableTeachers->setColumnCount(3);
    ui->tableTeachers->setHorizontalHeaderLabels({"ID", "Name", "Subject"});
    std::function<void(Teacher*, int&)> fill = [&](Teacher* node, int& row) {
        if (!node) return;
        fill(node->left, row);
        ui->tableTeachers->insertRow(row);
        ui->tableTeachers->setItem(row, 0, new QTableWidgetItem(QString::number(node->id)));
        ui->tableTeachers->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(node->name)));
        ui->tableTeachers->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(node->subject)));
        row++;
        fill(node->right, row);
    };
    int row = 0;
    fill(teacherBST.root, row);
}

void MainWindow::refreshCourseTable() {
    ui->tableCourses->setRowCount(0);
    ui->tableCourses->setColumnCount(3);
    ui->tableCourses->setHorizontalHeaderLabels({"ID", "Title", "Teacher ID"});
}

void MainWindow::refreshFeeQueue() {
    ui->tableFees->setRowCount(0);
    ui->tableFees->setColumnCount(3);
    ui->tableFees->setHorizontalHeaderLabels({"Student ID", "Name", "Amount"});
    FeeRecord* cur = feeQueue.front;
    int row = 0;
    while (cur) {
        ui->tableFees->insertRow(row);
        ui->tableFees->setItem(row, 0, new QTableWidgetItem(QString::number(cur->studentId)));
        ui->tableFees->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(cur->studentName)));
        ui->tableFees->setItem(row, 2, new QTableWidgetItem(QString::number(cur->amount)));
        cur = cur->next;
        row++;
    }
}

void MainWindow::showMessage(const QString& msg) {
    QMessageBox::information(this, "School Management System", msg);
}
