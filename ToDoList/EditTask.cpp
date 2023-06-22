#include "EditTask.h"
#include <iostream>
#include "Task.h"
#include <QStandardItemModel>
#include "TaskWriter.h"
#include "TaskReader.h"



class Timer
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;

public:

	void Stop()
	{
		auto endTimePoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();

		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

		auto duration = end - start;

		double ms = duration * 0.001;

		std::cout << duration << "us (" << ms << "ms)\n";
	}

	Timer()
	{
		m_StartTimePoint = std::chrono::high_resolution_clock::now();

	}
	~Timer()
	{
		Stop();
	}
};

void EditTask::setUpTheFields()
{
	//Timer timer;
	QStandardItemModel* model = qobject_cast<QStandardItemModel*>(m_ref.ui.task_view->model());
	std::string data = model->itemData(m_ref.getSelectedTask()).values().at(0).toString().toStdString();
	auto [name, description, date] = m_ref.getParams(data);
	ui.old_name_browser->setText(QString::fromStdString(name));
	ui.old_description_browser->setText(QString::fromStdString(description));
	ui.old_date_browser->setText(QString::fromStdString(date));
	m_column = m_ref.getSelectedTask().row();
	std::cout << m_column << std::endl;
}

EditTask::EditTask(ToDoList& ref, QWidget* parent) : QMainWindow{parent}, m_ref{ref}
{
	ui.setupUi(this);
	connect(ui.submit_btn, &QPushButton::clicked, this, &EditTask::on_submit_btn_clicked);
	setUpTheFields();
}


void EditTask::on_submit_btn_clicked()
{
	try 
	{ 
		std::string new_name = ui.new_name_line->text().toStdString();
		std::string new_description = ui.new_description_line->text().toStdString();
		std::time_t curr_time = std::time(nullptr);
		std::string new_time = std::ctime(&curr_time);
		TaskReader task_reader;
		std::cout << task_reader.getLines().at(m_column) << "??" << std::endl;
		TaskWriter task_writer;
		std::string data_to_send = new_name + '-' + new_description + '-' + new_time;
		task_writer.overrideTask(m_column, data_to_send);
		m_ref.updateTasks();
		this->close();
	}
	catch (const std::runtime_error& err)
	{
		std::cout << err.what() << " :(" << std::endl;
	}
}
