#include "ToDoList.h"
#include"ui_ToDoList.h"
#include <iostream>
#include <filesystem>
#include<fstream>

ToDoList::ToDoList(QWidget *parent): QMainWindow(parent) 
{
    ui.setupUi(this); 
}

ToDoList::~ToDoList()
{
    
}

void ToDoList::on_addBTN_clicked()
{
    double first = ui.first_txt->text().toDouble();
    double second = ui.second_txt->text().toDouble();
    double result = first + second;
    ui.result_txt->setText(QString::number(result));
}

void ToDoList::on_subtractBTN_clicked()
{
    double first = ui.first_txt->text().toDouble();
    double second = ui.second_txt->text().toDouble();
    double result = first - second;
    ui.result_txt->setText(QString::number(result));
}

void ToDoList::on_divideBTN_clicked()
{
    double first = ui.first_txt->text().toDouble();
	double second = ui.second_txt->text().toDouble();
	double result = first / second;
	ui.result_txt->setText(QString::number(result));
}

void ToDoList::on_multiplyBTN_clicked()
{
    double first = ui.first_txt->text().toDouble();
	double second = ui.second_txt->text().toDouble();
	double result = first * second;
	ui.result_txt->setText(QString::number(result));
}

