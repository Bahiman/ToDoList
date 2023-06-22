#pragma once
#include <QtWidgets/QMainWindow>
#include"ui_EditTask.h"
#include"ToDoList.h"

QT_BEGIN_NAMESPACE
namespace Ui { class EditTask; }
QT_END_NAMESPACE

class EditTask : public QMainWindow
{
	Q_OBJECT
private:
	ToDoList& m_ref;
	Ui::EditTaskClass ui;
	void setUpTheFields();
	unsigned int m_column;
public:
	EditTask(ToDoList& ref, QWidget* parent = nullptr);
	virtual ~EditTask() = default;
private slots:
	void on_submit_btn_clicked();

};