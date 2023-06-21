#pragma once
#include<iostream>
class Task
{
private:
	std::string m_name;
	std::string m_description;
	std::string m_date;
public:
	template<typename T> Task(T&& name, T&& desc, T&& date) : m_name{ std::forward<T>(name) }, m_description{ std::forward<T>(desc) }, m_date{ std::forward<T>(date) } {}
	Task(const Task& task) : m_name{task.m_name}, m_description{task.m_description}, m_date{task.m_date} {}
	const std::string& getName() const { return m_name; }
	const std::string& getDescription() const { return m_description;};
	const std::string& getDate() const { return m_date; };
	void setName(const std::string& name) { m_name = name; }
	void setDescription(const std::string& description) { m_description = description; }
	void setDate(const std::string& date) { m_date = date; }
	static Task lineToTask(const std::string& line){std::string name, description, date;unsigned int i = 0;while (line[i] != '-'){name += line[i];i++;}i++;while (line[i] != '-'){description += line[i];i++;}i++;while (i < line.size()){date += line[i];i++;}return Task(name, description, date);}
	friend std::ostream& operator<<(std::ostream& out, const Task& task) { out << task.m_name << ", " << task.m_description << ", " << task.m_date; return out;}
	friend std::fstream& operator<<(std::fstream& out, const Task& task) { out << task.m_name << "-" << task.m_description << "-" << task.m_date; return out; }
	std::string toString() const { return m_name + "-" + m_description + "-" + m_date; }
};