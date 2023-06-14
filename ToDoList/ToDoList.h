#pragma once

#include <QtWidgets/QMainWindow>
#include"ui_ToDoList.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ToDoList : public QMainWindow
{
    Q_OBJECT

public:
    ToDoList(QWidget *parent = nullptr);
    ~ToDoList();
private slots:
    void on_addBTN_clicked();
    void on_subtractBTN_clicked();
    void on_divideBTN_clicked();
    void on_multiplyBTN_clicked();
private:
    Ui::ToDoListClass ui;
};
