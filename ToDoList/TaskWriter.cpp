#include "TaskWriter.h"
#include<string>
#include"TaskReader.h"

unsigned int TaskWriter::getRowCount()
{
	unsigned int rowCount = 0;
	if (!std::filesystem::exists(m_path))
		throw std::runtime_error("The path does not exist(Trying to write)");
	std::fstream file_stream(m_path);
	if (!file_stream)
		throw std::runtime_error("The file was not found!(Trying to write)");

	for (std::string l; std::getline(file_stream, l);)
	{
		rowCount++;
	}

	file_stream.close();

	return rowCount;
}

void TaskWriter::addTask(const Task& task) 
{
	if (!std::filesystem::exists(m_path))
		throw std::runtime_error("The path does not exist(Trying to write)");

	std::fstream file_stream(m_path, std::ios::app);
	if (!file_stream)
		throw std::runtime_error("The file was not found!(Trying to write)");

	std::string to_append = task.toString();

	file_stream.write(to_append.c_str(), strlen(to_append.c_str()));
	file_stream.close();
}

void TaskWriter::overrideTask(unsigned int column, const Task& new_task)
{
	if (column > getRowCount())
		throw std::runtime_error("Row out of range(Trying to override)");
	TaskReader task_reader;
	auto& lines = task_reader.lines; 
	lines[static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(column) - 1] = new_task.toString();
	std::ofstream outputFile(m_path, std::ios::out | std::ios::trunc);
	for (auto& line : lines)
	{
		outputFile << line << std::endl;
	}
	outputFile.close();
}

void TaskWriter::deleteTask(unsigned int column)
{
	if (column > getRowCount())
		throw std::runtime_error("Row out of range(Trying to override)");
	TaskReader task_reader;
	auto& lines = task_reader.lines;
	lines.erase(lines.begin() + (column - 1));
	std::ofstream outputFile(m_path, std::ios::out | std::ios::trunc);
	for (auto& line : lines)
	{
		outputFile << line << std::endl;
	}
	outputFile.close();
}

void TaskWriter::deleteTask(const Task& task)
{
	TaskReader task_reader;
	auto& lines = task_reader.lines;
	if (std::find(lines.begin(), lines.end(), task.toString()) == lines.end())
		throw std::runtime_error("The task does not exist!(Deleteing the task)");
	for (auto& line : lines)
	{
		if (line == task.toString())
		{
			lines.erase(std::find(lines.begin(), lines.end(), line));
			break;
		}
	}
	std::ofstream outputFile(m_path, std::ios::out | std::ios::trunc);
	for (auto& line : lines)
	{
		outputFile << line << std::endl;
	}
	outputFile.close();
}

void TaskWriter::deleteTask(Task&& task)
{
	TaskReader task_reader;
	auto& lines = task_reader.lines;
	if (std::find(lines.begin(), lines.end(), task.toString()) == lines.end())
		throw std::runtime_error("The task does not exist!(Deleteing the task)");
	for (auto& line : lines)
	{
		if (line == task.toString())
		{
			lines.erase(std::find(lines.begin(), lines.end(), line));
			break;
		}
	}
	std::ofstream outputFile(m_path, std::ios::out | std::ios::trunc);
	for (auto& line : lines)
	{
		outputFile << line << std::endl;
	}
	outputFile.close();
}

void TaskWriter::deleteAllTasks()
{
	std::fstream outputFile(m_path, std::ios::out | std::ios::trunc);
	// try		
	outputFile.close();
}
