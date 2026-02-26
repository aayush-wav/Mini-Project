#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      nextSid(1001), nextTid(2001), nextCid(3001)
{
    ui->setupUi(this);

    connect(ui->btnAddStudent,  &QPushButton::clicked, this, &MainWindow::onAddStudent);
    connect(ui->btnDelStudent,  &QPushButton::clicked, this, &MainWindow::onDelStudent);
    connect(ui->btnFindStudent, &QPushButton::clicked, this, &MainWindow::onFindStudent);
    connect(ui->btnUndo,        &QPushButton::clicked, this, &MainWindow::onUndoAdmit);
    connect(ui->btnAddTeacher,  &QPushButton::clicked, this, &MainWindow::onAddTeacher);
    connect(ui->btnDelTeacher,  &QPushButton::clicked, this, &MainWindow::onDelTeacher);
    connect(ui->btnFindTeacher, &QPushButton::clicked, this, &MainWindow::onFindTeacher);
    connect(ui->btnAddCourse,   &QPushButton::clicked, this, &MainWindow::onAddCourse);
    connect(ui->btnEnroll,      &QPushButton::clicked, this, &MainWindow::onEnroll);
    connect(ui->btnAddFee,      &QPushButton::clicked, this, &MainWindow::onAddFee);
    connect(ui->btnProcessFee,  &QPushButton::clicked, this, &MainWindow::onProcessFee);

    reloadStudents();
    reloadTeachers();
    reloadCourses();
    reloadFees();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onAddStudent() {
    bool ok;
    QString name = QInputDialog::getText(this, "Add Student", "Name:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;
    int age = QInputDialog::getInt(this, "Add Student", "Age:", 10, 5, 30, 1, &ok);
    if (!ok) return;
    QString grade = QInputDialog::getText(this, "Add Student", "Grade:", QLineEdit::Normal, "", &ok);
    if (!ok || grade.isEmpty()) return;

    Student* s = new Student(nextSid++, name.toStdString(), age, grade.toStdString());
    sList.add(s);
    undoStack.push(s);
    fQueue.push(s->id, s->name, 5000.0f);
    reloadStudents();
    reloadFees();
    msg("Student added. ID: " + QString::number(s->id));
}

void MainWindow::onDelStudent() {
    bool ok;
    int id = QInputDialog::getInt(this, "Remove Student", "Student ID:", 1001, 1, 99999, 1, &ok);
    if (!ok) return;
    if (!sList.get(id)) { msg("Not found."); return; }
    sList.del(id);
    reloadStudents();
    msg("Removed.");
}

void MainWindow::onFindStudent() {
    bool ok;
    int id = QInputDialog::getInt(this, "Find Student", "Student ID:", 1001, 1, 99999, 1, &ok);
    if (!ok) return;
    Student* s = sList.get(id);
    if (!s) { msg("Not found."); return; }
    QString info = "ID: " + QString::number(s->id) +
                   "\nName: " + QString::fromStdString(s->name) +
                   "\nAge: " + QString::number(s->age) +
                   "\nGrade: " + QString::fromStdString(s->grade);
    QMessageBox::information(this, "Student", info);
}

void MainWindow::onUndoAdmit() {
    if (undoStack.empty()) { msg("Nothing to undo."); return; }
    Student* s = undoStack.top();
    undoStack.pop();
    sList.del(s->id);
    reloadStudents();
    msg("Undid admission of " + QString::fromStdString(s->name));
    delete s;
}

void MainWindow::onAddTeacher() {
    bool ok;
    QString name = QInputDialog::getText(this, "Add Teacher", "Name:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;
    QString subject = QInputDialog::getText(this, "Add Teacher", "Subject:", QLineEdit::Normal, "", &ok);
    if (!ok || subject.isEmpty()) return;
    tBST.add(nextTid++, name.toStdString(), subject.toStdString());
    reloadTeachers();
    msg("Teacher added. ID: " + QString::number(nextTid - 1));
}

void MainWindow::onDelTeacher() {
    bool ok;
    int id = QInputDialog::getInt(this, "Remove Teacher", "Teacher ID:", 2001, 1, 99999, 1, &ok);
    if (!ok) return;
    if (!tBST.find(id)) { msg("Not found."); return; }
    tBST.del(id);
    reloadTeachers();
    msg("Removed.");
}

void MainWindow::onFindTeacher() {
    bool ok;
    int id = QInputDialog::getInt(this, "Find Teacher", "Teacher ID:", 2001, 1, 99999, 1, &ok);
    if (!ok) return;
    Teacher* t = tBST.find(id);
    if (!t) { msg("Not found."); return; }
    QString info = "ID: " + QString::number(t->id) +
                   "\nName: " + QString::fromStdString(t->name) +
                   "\nSubject: " + QString::fromStdString(t->subject);
    QMessageBox::information(this, "Teacher", info);
}

void MainWindow::onAddCourse() {
    bool ok;
    QString title = QInputDialog::getText(this, "Add Course", "Title:", QLineEdit::Normal, "", &ok);
    if (!ok || title.isEmpty()) return;
    int tid = QInputDialog::getInt(this, "Add Course", "Teacher ID:", 2001, 1, 99999, 1, &ok);
    if (!ok) return;
    cTable.add(nextCid++, title.toStdString(), tid);
    reloadCourses();
    msg("Course added. ID: " + QString::number(nextCid - 1));
}

void MainWindow::onEnroll() {
    bool ok;
    int cid = QInputDialog::getInt(this, "Enroll", "Course ID:", 3001, 1, 99999, 1, &ok);
    if (!ok) return;
    int sid = QInputDialog::getInt(this, "Enroll", "Student ID:", 1001, 1, 99999, 1, &ok);
    if (!ok) return;
    cTable.enroll(cid, sid);
    reloadCourses();
    msg("Enrolled.");
}

void MainWindow::onAddFee() {
    bool ok;
    int sid = QInputDialog::getInt(this, "Add Fee", "Student ID:", 1001, 1, 99999, 1, &ok);
    if (!ok) return;
    Student* s = sList.get(sid);
    if (!s) { msg("Student not found."); return; }
    double amt = QInputDialog::getDouble(this, "Add Fee", "Amount:", 1000, 0, 100000, 2, &ok);
    if (!ok) return;
    fQueue.push(sid, s->name, (float)amt);
    reloadFees();
    msg("Fee record added.");
}

void MainWindow::onProcessFee() {
    if (fQueue.empty()) { msg("Queue is empty."); return; }
    FeeNode* n = fQueue.pop();
    msg("Processed: " + QString::fromStdString(n->studentName) +
        " - Rs." + QString::number(n->amount));
    delete n;
    reloadFees();
}

void MainWindow::reloadStudents() {
    ui->tableStudents->setRowCount(0);
    ui->tableStudents->setColumnCount(4);
    ui->tableStudents->setHorizontalHeaderLabels({"ID", "Name", "Age", "Grade"});
    Student* cur = sList.head;
    int r = 0;
    while (cur) {
        ui->tableStudents->insertRow(r);
        ui->tableStudents->setItem(r, 0, new QTableWidgetItem(QString::number(cur->id)));
        ui->tableStudents->setItem(r, 1, new QTableWidgetItem(QString::fromStdString(cur->name)));
        ui->tableStudents->setItem(r, 2, new QTableWidgetItem(QString::number(cur->age)));
        ui->tableStudents->setItem(r, 3, new QTableWidgetItem(QString::fromStdString(cur->grade)));
        cur = cur->next;
        r++;
    }
}

void MainWindow::reloadTeachers() {
    ui->tableTeachers->setRowCount(0);
    ui->tableTeachers->setColumnCount(3);
    ui->tableTeachers->setHorizontalHeaderLabels({"ID", "Name", "Subject"});
    std::function<void(Teacher*, int&)> fill = [&](Teacher* node, int& r) {
        if (!node) return;
        fill(node->left, r);
        ui->tableTeachers->insertRow(r);
        ui->tableTeachers->setItem(r, 0, new QTableWidgetItem(QString::number(node->id)));
        ui->tableTeachers->setItem(r, 1, new QTableWidgetItem(QString::fromStdString(node->name)));
        ui->tableTeachers->setItem(r, 2, new QTableWidgetItem(QString::fromStdString(node->subject)));
        r++;
        fill(node->right, r);
    };
    int r = 0;
    fill(tBST.root, r);
}

void MainWindow::reloadCourses() {
    ui->tableCourses->setRowCount(0);
    ui->tableCourses->setColumnCount(3);
    ui->tableCourses->setHorizontalHeaderLabels({"ID", "Title", "Teacher ID"});
}

void MainWindow::reloadFees() {
    ui->tableFees->setRowCount(0);
    ui->tableFees->setColumnCount(3);
    ui->tableFees->setHorizontalHeaderLabels({"Student ID", "Name", "Amount"});
    FeeNode* cur = fQueue.front;
    int r = 0;
    while (cur) {
        ui->tableFees->insertRow(r);
        ui->tableFees->setItem(r, 0, new QTableWidgetItem(QString::number(cur->studentId)));
        ui->tableFees->setItem(r, 1, new QTableWidgetItem(QString::fromStdString(cur->studentName)));
        ui->tableFees->setItem(r, 2, new QTableWidgetItem(QString::number(cur->amount)));
        cur = cur->next;
        r++;
    }
}

void MainWindow::msg(const QString& s) {
    QMessageBox::information(this, "SMS", s);
}