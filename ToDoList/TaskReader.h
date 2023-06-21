//#pragma once
#include<filesystem>
#include<fstream>
#include<vector>
#include<tuple>
#include"Task.h"

class TaskWriter;

class TaskReader
{
private:
	std::filesystem::path m_path = "tasks.txt";
	std::vector<Task> m_tasks;
	std::vector<std::tuple<std::string, std::string, std::string>> tasks;
	void m_getLines();
	void m_getTasks();
	std::vector<std::string> lines;
	void insert_tasks();
	void m_setTasks(); // asddssda
public:
	TaskReader() { m_setTasks(); }
	~TaskReader() = default;
	std::vector<Task>& getTasks() { return m_tasks;}
	const std::vector<std::string>& getLines() const { return lines; }
	void update() { m_setTasks();}
	friend TaskWriter;
};