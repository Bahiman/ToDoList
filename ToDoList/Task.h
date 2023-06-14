#pragma once

#include<string>
class Task
{
private:
	std::string m_name;
	std::string m_description;
	std::string m_date;
public:
	Task(std::string& name, std::string& description, std::string& date) : m_name{ name }, m_description{ description }, m_date{ date } {};
	inline const std::string& getName() const { return m_name; }
	inline const std::string& getDescription() const { return m_description;};
	inline const std::string& getDate() const { return m_date; };
	inline void setName(const std::string& name) { m_name = name; }
	inline void setDescription(const std::string& description) { m_description = description; }
	inline void setDate(const std::string& date) { m_date = date; }
};