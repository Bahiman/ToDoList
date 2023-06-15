#pragma once
#include<fstream>
#include<filesystem>
#include"Task.h"


class TaskWriter
{
private:
	const std::filesystem::path m_path = "tasks.txt";	
	unsigned int getRowCount();
public:
	void addTask(const Task& task);
	void overrideTask(unsigned int column, const Task& new_task);
	void deleteTask(unsigned int column);
	void deleteTask(const Task& task);
	void deleteTask(Task&& task);
	void deleteAllTasks();
};