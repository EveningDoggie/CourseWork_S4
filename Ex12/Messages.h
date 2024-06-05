#pragma once
#include <set>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
class Messages
{


//Формат файла (до милисекунд): <user name> <time> : <message>
public:

	typedef struct message
	{
		std::string login;
		size_t date = 0;
		size_t time = 0;
		std::string text;

		bool operator < (const message& other) const {
			if (date != other.date) {
				return date < other.date;
			}
			if (time != other.time) {
				return time < other.time;
			}

			if (login != other.login) {
				return login < other.login;
			}
			
			return text < other.text;
		}
	};
	

	static void Load(std::string path, std::set<Messages::message>* data);

	static void printMessage(const Messages::message* val);

	static void printMessages(std::set<Messages::message>* data);

	//вывода всех сообщений заданного пользователя;
	static void printUserMessages(std::string user, std::set<message>* data);
	
	//вывода сообщений заданного пользователя для заданного временного интервала;
	static void printUserMessagesFromInterval(std::string user, size_t startdate, size_t enddate, size_t starttime, size_t endtime, std::set<Messages::message>* data);
	
	//вывод всех сообщений из заданного временного интервала.
	static void printMessagesFromInterval(size_t startdate, size_t enddate, size_t starttime, size_t endtime, std::set<Messages::message>* data);
	
	//удаление сообщения
	static void removeMessage(std::set<Messages::message>* data, std::set<Messages::message>::iterator);
	
	//удаление пользователя
	static void removeUser(std::string user, std::set<message>* data);

	static size_t ConvertToDate(int year, int month, int day);

	static size_t ConvertToTime(int hour, int minute, int second, int milisecond);

private:

	

	static void GetValuesFromDate(size_t time, int* year, int* month, int* day);

	static size_t GetDateFromString(std::string lexem);
	
	static void GetValuesFromTime(size_t time, int* hour, int* minute, int* second, int* milisecond);

	static size_t GetTimeFromString(std::string lexem);

	static message GetMessageObject(std::string line);
};
