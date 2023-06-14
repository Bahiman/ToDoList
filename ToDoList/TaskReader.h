#pragma once
#include<filesystem>
#include<fstream>
#include<vector>
#include<tuple>
#include"Task.h"

class TaskReader
{
private:
	std::filesystem::path m_path = "tasks.txt";
	std::vector<Task> m_tasks;
	std::vector<std::string> m_getLines();
	std::vector<std::tuple<std::string, std::string, std::string>> m_getTasks();
	Task&& operator=(const Task&& task);
	void insert_tasks();
	void m_setTasks();
public:
	TaskReader() { m_setTasks(); }
	~TaskReader() = default;
	inline std::vector<Task>& getTasks() { return m_tasks; }
};