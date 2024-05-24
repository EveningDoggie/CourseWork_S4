#pragma once
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


class Work
{
private:
	static void GetDealObject(std::string line, int* number, std::pair<size_t, size_t>* timesPair, std::pair<size_t, size_t>* workPair);
	static size_t GetTimeFromString(std::string line);
	static size_t ConvertToTime(int year, int month, int day);
	static void GetValuesFromTime(size_t time, int* year, int* month, int* day);
	static size_t GetTimeDifference(size_t first, size_t second);
public:
	static std::map<std::string, std::map<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>> Load(std::string path);
	static size_t getSumSalary(std::string user, std::map<std::string, std::map<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>>* data);
	static std::map<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>* getDealList(std::string user, std::map<std::string, std::map<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>>* data);
	static void printDealList(std::string user, std::map<std::string, std::map<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>> * data);
	static void printDeal(std::pair<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>> * deal);
	static std::pair<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>* getLongestDeal(std::string user, std::map<std::string, std::map<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>>* data);
	static std::pair<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>* getDearestDeal(std::string user, std::map<std::string, std::map<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>> * data);
	static void RemoveEmployee(std::string user, std::map<std::string, std::map<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>>* data);
};

/*
контейнер map. ключ - фио всех договоров этого сотрудника;
● выдачи списка договоров, с которыми работал заданный сотрудник;
● найти самый продолжительный договор данного сотрудника;
● найти самый дорогой договор данного сотрудника.
Необходимо также реализовать удаление информации о сотруднике.
*/