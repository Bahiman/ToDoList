#include "ToDoList.h"
#include<qabstractitemmodel.h>
#include"TaskReader.h"
#include"TaskWriter.h"
#include"ui_ToDoList.h"
#include<sstream>
#include <filesystem>
#include <iostream>
#include<execution>
#include<fstream>
#include<ctime>
#include <QStandardItemModel>

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

ToDoList::ToDoList(QWidget *parent): QMainWindow(parent) 
{
    ui.setupUi(this); 
    connect(ui.task_view, &QListView::doubleClicked, this, &ToDoList::handleItemDoubleClicked);
    updateTasks();
}
    
ToDoList::~ToDoList()
{
    
}

void ToDoList::showContextMenu(const QModelIndex& index)
{
    // so baby pull me closer to the back seat of ur rover that I know you can
}

void ToDoList::on_erase_all_clicked()
{
    TaskWriter task_writer;
	task_writer.deleteAllTasks();
	updateTasks();
	QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui.task_view->model());
    if (model)
    {
		model->clear();
        ui.task_view->update();
	}
	else
		throw std::runtime_error("Erase all failed!");
}

void ToDoList::handleItemDoubleClicked(const QModelIndex& index)
{
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui.task_view->model());
    if (model)
    {
        try
        {
            std::string data = model->itemData(index).values().at(0).toString().toStdString();
            auto [name, description, date] = getParams(data);
            Task task(name, description, date);
            TaskWriter task_writer;
            task_writer.deleteTask(task);
            updateTasks();
            model->removeRow(index.row());
        }
        catch (const std::runtime_error& e)
        {
			std::cout << e.what() << std::endl;
		}

    } 
    else
        throw std::runtime_error("Double Click handling failed!");
}

void ToDoList::updateTasks()
{
    std::vector<std::string> file_lines;

    auto getLines = [this,&file_lines]() {
    TaskReader task_reader; 

    for (auto& k : task_reader.getTasks())
    {
    std::string data_to_set = k.getName() + " " + k.getDescription() + " " + k.getDate();
    file_lines.emplace_back(std::move(data_to_set));
    data_to_set.clear();
    }
    };
    {
        Timer timer;
        std::thread thread(getLines);
        QStandardItemModel* model = new QStandardItemModel(this);
        ui.task_view->setModel(model);
        thread.join();
        std::for_each(file_lines.begin(), file_lines.end(), [&model](std::string& str) {QStandardItem* item = new QStandardItem(QString::fromStdString(str)); model->appendRow(item); });
    }
}

std::tuple<std::string, std::string, std::string> ToDoList::getParams(const std::string& line) {
    std::istringstream iss(line);
    std::string first, second, third;
    // Extract values using formatted input
    if (iss >> first >> second) {
        std::getline(iss >> std::ws, third);
    }

    return std::make_tuple(first, second, third);
}

void ToDoList::on_add_btn_clicked()
{ 
    try
    {
        TaskWriter task_writer;
        std::time_t currentTime = std::time(nullptr);
        std::string currentDate = std::ctime(&currentTime);
        std::string input_string = ui.task_name_input->text().toStdString();
        std::string desc_string = ui.task_desc_input->text().toStdString();
        Task task(input_string, desc_string, currentDate);
        std::thread thread_one(&TaskWriter::addTask, &task_writer, task);
        QStandardItemModel* model = new QStandardItemModel(this);
        ui.task_view->setModel(model);
        ui.task_name_input->clear();
        ui.task_desc_input->clear();
        ui.task_name_input->setFocus();
        std::string dataToSet = input_string + " " + desc_string + " " + currentDate;
        QStandardItem* item = new QStandardItem(QString::fromStdString(dataToSet));
        thread_one.join();
        updateTasks();
        model->appendRow(item);
    }
    catch (const std::runtime_error& error)
    {
        std::cout << "Error thrown trying to add task: " << error.what() << "\n";
    }
    // Hi do you know QT?
}
 
