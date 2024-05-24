#include "Work.h"


std::map<std::string, std::map<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>> Work::Load(std::string path)
{
    std::map<std::string, std::map<const int, std::pair<std::pair<size_t, size_t>,std::pair<size_t, size_t>>>> employee;
    std::map<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>> mp;

    bool recording = false;
    std::string name = "";
    std::string line;
    
    std::ifstream in(path);
    if (!in.is_open()) throw std::logic_error("File is not open");

    while (std::getline(in, line))
    {
        if (line == "{") 
        {
            recording = true; 
            continue;
        }
        if (line == "}")
        {
            recording = false;
            employee[name] = mp;
            mp.clear();
            continue;
        }
        
        if (!recording)
        {
            name = line;
        }
        else
        {
            int number;
            std::pair<size_t, size_t> timesPair;
            std::pair<size_t, size_t> workPair;
            try
            {
                GetDealObject(line, &number, &timesPair, &workPair);
            }
            catch(std::exception e)
            {
                throw;
            }

         
            std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>> pair;
            pair.first = timesPair;
            pair.second = workPair;
            mp[number] = pair;
        }
    }
    
    in.close();
    
    return employee;
}

size_t Work::GetTimeFromString(std::string lexem)
{
    if (lexem == "nv") return 0;

    int year, month, day;
    std::string part;
    std::stringstream ss;
    ss << lexem;

    try
    {   
        std::getline(ss, part, '/');
        day = stoi(part);

        std::getline(ss, part, '/');
        month = stoi(part);

        std::getline(ss, part, '/');
        year = stoi(part);

    }
    catch (std::invalid_argument e)
    {
        return 0;
    }

    return ConvertToTime(year, month, day);
}

size_t Work::ConvertToTime(int year, int month, int day)
{
    return year * 10000 + month*100 + day;
}

size_t Work::GetTimeDifference(size_t first, size_t second)
{
    if (first == 0 || second == 0) return 0;
    int y1, y2, m1, m2, d1, d2;
    GetValuesFromTime(first, &y1, &m1, &d1);
    GetValuesFromTime(second, &y2, &m2, &d2);
   
    return ConvertToTime(y1 - y2, m1 - m2, d1 - d2);
}



void Work::GetValuesFromTime(size_t time, int* year, int* month, int* day)
{
    *day = time % 100;
    time /= 100;

    *month = time % 100;
    time /= 100;

    *year = time;
}

void Work::GetDealObject(std::string line, int * number, std::pair<size_t, size_t> * timesPair, std::pair<size_t, size_t>* workPair)
{
    std::string lexem;
    std::stringstream ss;
    ss << line;
    
    std::string record;

    while (std::getline(ss, lexem, ' '))
    {
        if (lexem == "Contract")
        {
            std::getline(ss, lexem, ' ');
            lexem.erase(0,1);
            try 
            {
                *number = stoi(lexem);
            }
            catch (std::invalid_argument e)
            {
                throw;
            }
        }

        if (lexem == "beg.")
        {
            std::getline(ss, lexem, ' ');

            try
            {
                timesPair->first = GetTimeFromString(lexem);
            }
            catch (std::invalid_argument e)
            {
                throw;
            }
        }

        if (lexem == "con.")
        {
            std::getline(ss, lexem, ' ');

            try
            {
               timesPair->second = GetTimeFromString(lexem);
            }
            catch (std::invalid_argument e)
            {
                throw;
            }
        }

        if (lexem == "Work")
        {
            std::getline(ss, lexem, ' ');

            try
            {
                workPair->first = stoi(lexem);
            }
            catch (std::invalid_argument e)
            {
                throw;
            }
        }

        if (lexem == "Cost")
        {
            std::getline(ss, lexem, ' ');

            try
            {
                lexem.erase(lexem.size()-1);
                workPair->second = stoi(lexem);
            }
            catch (std::invalid_argument e)
            {
                throw;
            }
        }
    }
}


std::map<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>> * Work::getDealList(std::string user, std::map<std::string, std::map<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>> * data)
{
    return &(*data)[user];
}

void Work::printDealList(std::string user, std::map<std::string, std::map<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>> * data)
{
    
    for (auto deal : (*data)[user])
    {
        printDeal(&deal);
    }
}

void Work::printDeal(std::pair<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>> * deal)
{
    auto * pair1 = &deal->second.first;
    auto * pair2 = &deal->second.second;

    std::cout
        << "Deal number " << deal->first
        << ":\t" << (pair1->first != 0 ? std::to_string(pair1->first) : "None\t")
        << "-" << (pair1->second != 0 ? std::to_string(pair1->second) : "None\t")
        << "\tHours:" << pair2->first
        << "\tSalary:" << pair2->second
        << "\n";
}


std::pair<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>* Work::getDearestDeal(std::string user, std::map<std::string, std::map<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>> * data)
{

    auto dl = getDealList(user, data);
    std::pair<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>* maxDeal = nullptr;

    for (auto& v : *dl)
    {
        if (maxDeal==nullptr || v.second.second.first * v.second.second.second > maxDeal->second.second.first * maxDeal->second.second.second)
            maxDeal = &v;
    }
    
    return maxDeal;
}




std::pair<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>* Work::getLongestDeal(std::string user, std::map<std::string, std::map<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>>* data)
{

    auto dl = getDealList(user, data);
    size_t maxdiff = 0;
    std::pair<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>*maxDeal = nullptr;

    for (auto& v : *dl)
    {
        size_t diff = GetTimeDifference(v.second.first.second, v.second.first.first);
        if (diff > maxdiff)
        {
            maxdiff = diff;
            maxDeal = &v;
        }
    }


    return maxDeal;
}

size_t Work::getSumSalary(std::string user, std::map<std::string, std::map<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>>* data)
{
    auto dl = getDealList(user, data);
    size_t sum = 0;

    for (auto& v : *dl)
    {
        sum+=v.second.second.first * v.second.second.second;
    }

    return sum;
}


void Work::RemoveEmployee(std::string user, std::map<std::string, std::map<const int, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>>* data)
{
    data->erase(user);
}