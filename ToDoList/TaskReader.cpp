#include "TaskReader.h"
#include<string>
#include<sstream>
#include<iostream>

void TaskReader::m_getLines() 
{
    if (!std::filesystem::exists(m_path)) throw std::runtime_error("File path does not exist!(Trying to read)");
    std::fstream file_stream(m_path);
    if (!file_stream) throw std::runtime_error("The file could not be opened!(Trying to read)");
    lines.clear();
    for (std::string l; std::getline(file_stream, l);)
    {
		lines.emplace_back(std::move(l));
        l.clear();
	}
    file_stream.close();
}

void TaskReader::m_getTasks()
{   
    m_getLines();
    tasks.clear();
    for (auto& line : lines)
    {
        std::string name;
        std::string desc;
        std::string date;
        std::string temp;
        std::stringstream string_stream(line);
        int counter = 0;
        while (std::getline(string_stream, temp, '-'))
        {
            if(counter == 0) 
            {
                name = std::move(temp);
                temp.clear();
                counter++;
            }
            else if (counter == 1)
            {
                desc = std::move(temp); 
                temp.clear();
                counter++;
            }
            else if (counter == 2)
            {
                date = std::move(temp);
                temp.clear();
                counter++;
            }
        }

        tasks.emplace_back(name, desc, date);
    }
}

void TaskReader::insert_tasks()
{
	m_getTasks();
    m_tasks.clear();
    for (auto& task : tasks)
    {
        std::string name = std::move(std::get<0>(task));
        std::string desc = std::move(std::get<1>(task));
        std::string date = std::move(std::get<2>(task));
        m_tasks.emplace_back(name, desc, date);
	}  
}

void TaskReader::m_setTasks()
{
	insert_tasks();
}