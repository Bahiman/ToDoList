#pragma once

#include <QtWidgets/QMainWindow>
#include"ui_ToDoList.h"
#include<tuple>

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
    void on_add_btn_clicked();
    void on_erase_all_clicked();
    void handleItemDoubleClicked(const QModelIndex& index);
private:
    Ui::ToDoListClass ui;
    void updateTasks();
    std::tuple<std::string, std::string, std::string> getParams(const std::string& data);
    void showContextMenu(const QModelIndex& index);
};
