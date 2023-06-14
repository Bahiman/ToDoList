#include "TaskReader.h"

std::vector<std::string> TaskReader::m_getLines()
{
    if (!std::filesystem::exists(m_path)) throw std::runtime_error("Error: File not found!");
    std::fstream file_stream(m_path);
    std::vector<std::string> lines;
    lines.reserve(std::count(std::istream_iterator<char>(file_stream),std::istream_iterator<char>(),'\n'));
    std::string line;
    while (std::getline(file_stream, line))
    {
        lines.emplace_back(std::move(line));
        line.clear();   
    }
    return lines;      
}

std::vector<std::tuple<std::string, std::string, std::string>> TaskReader::m_getTasks()
{   
    auto lines = m_getLines();

    std::vector<std::tuple<std::string, std::string, std::string>> tasks;

    for (auto& line : lines)
    {
        std::string name;
        std::string desc;
        std::string date;
        std::string temp;
        std::stringstream string_stream(line);
        while (std::getline(string_stream, temp, '-'))
        {
            static int counter = 0;
            if(counter == 0) 
            {
                name = std::move(temp);
                temp.clear();
            }
            else if (counter == 1)
            {
                desc = std::move(temp);
                temp.clear();
            }
            else if (counter == 2)
            {
                date = std::move(temp);
                temp.clear();
            }
        }

        tasks.emplace_back(std::move(name), std::move(desc), std::move(date));
    }
    return tasks;
}

Task&& TaskReader::operator=(const Task&& task)
{
    
}

void TaskReader::insert_tasks()
{
	auto tasks = m_getTasks();
    for (auto& task : tasks)
    {
		m_tasks.emplace_back(std::move(std::get<0>(task)), std::move(std::get<1>(task)), std::move(std::get<2>(task)));
	}
}

void TaskReader::m_setTasks()
{
	insert_tasks();
}