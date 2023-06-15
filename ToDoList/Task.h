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
	inline const std::string& getName() const { return m_name; }
	inline const std::string& getDescription() const { return m_description;};
	inline const std::string& getDate() const { return m_date; };
	inline void setName(const std::string& name) { m_name = name; }
	inline void setDescription(const std::string& description) { m_description = description; }
	inline void setDate(const std::string& date) { m_date = date; }
	inline friend std::ostream& operator<<(std::ostream& out, const Task& task) { out << task.m_name << ", " << task.m_description << ", " << task.m_date; return out;}
	inline friend std::fstream& operator<<(std::fstream& out, const Task& task) { out << task.m_name << "-" << task.m_description << "-" << task.m_date; return out; }
	inline std::string toString() const { return m_name + "-" + m_description + "-" + m_date; }
};