#include "Messages.h"

void Messages::Load(std::string path, std::set<Messages::message> * data)
{
    std::string line;
    
    std::ifstream in(path);
    if (!in.is_open()) throw std::logic_error("File is not open");

    while (std::getline(in, line))
    {
        try
        {
       
            auto obj = GetMessageObject(line);
            data->insert(obj);
          
            
        }
        catch (std::exception e)
        {
            throw;
        }        
    }

    in.close();
}

Messages::message Messages::GetMessageObject(std::string line)
{
    Messages::message message;
    std::string lexem;
    std::stringstream ss;
    ss << line;

    std::getline(ss, lexem, ' ');
    message.login = lexem;

    std::getline(ss, lexem, ' ');
    try
    {
        message.date=GetDateFromString(lexem);
    }
    catch (std::invalid_argument e)
    {
        throw;
    }

    std::getline(ss, lexem, ' ');
    try
    {
        message.time = GetTimeFromString(lexem);
    }
    catch (std::invalid_argument e)
    {
        throw;
    }
    
    std::getline(ss, lexem, ':');
    message.text = lexem;

    return message;
}







void Messages::printMessages(std::set<Messages::message>* data)
{
    for (auto& val : *data)
    {
        printMessage(&val);
    }
}

void Messages::printUserMessages(std::string user, std::set<Messages::message>* data)
{
    for (auto& val : *data)
    {
        if (val.login == user)
            printMessage(&val);
    }
}

void Messages::printMessage(const Messages::message * val)
{
    int y, m, d, h, mn, s, ms;
    GetValuesFromDate(val->date, &y, &m, &d);
    GetValuesFromTime(val->time, &h, &mn, &s, &ms);

        std::cout
        << "Message from "
        << val->login
        << "\tat "
        << y << "." << m << "." << d << " " 
        << h << ":" << mn << ":" << s << ":" << ms <<" \t"
        << val->text
        <<"\n";
}

void Messages::printUserMessagesFromInterval(std::string user, size_t startdate, size_t enddate, size_t starttime, size_t endtime,  std::set<Messages::message>* data)
{
    for (auto& val : *data)
    {
        if (val.login==user && 
            (val.date > startdate && val.date < enddate ||
            val.date == startdate && val.time > starttime ||
            val.date == enddate && val.time < endtime))
        {
            printMessage(&val);
        }
    }
}

void Messages::printMessagesFromInterval(size_t startdate, size_t enddate, size_t starttime, size_t endtime, std::set<Messages::message>* data)
{

    for (auto& val : *data)
    {
        if (val.date > startdate && val.date < enddate ||
            val.date == startdate && val.time > starttime ||
            val.date ==enddate && val.time < endtime)
        {
            printMessage(&val);
        }  
            
    }
}

void Messages::removeMessage(std::set<Messages::message>* data, std::set<Messages::message>::iterator msg)
{
    data->erase(msg);
}


void Messages::removeUser(std::string user, std::set<Messages::message>* data)
{

    std::vector <std::set<Messages::message>::iterator> iterators;
    auto iter{ data->begin() };  
    while (iter != data->end())    
    {
        if (iter->login == user)
        {
            iterators.push_back(iter);
        }
        ++iter;
    }

    for (auto x : iterators)
    {
        data->erase(x);
    }
}


size_t Messages::ConvertToDate(int year, int month, int day)
{
    return year * 10000 + month * 100 + day;
}


void Messages::GetValuesFromDate(size_t time, int* year, int* month, int* day)
{
    *day = time % 100;
    time /= 100;

    *month = time % 100;
    time /= 100;

    *year = time;
}


size_t Messages::GetDateFromString(std::string lexem)
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

    return ConvertToDate(year, month, day);
}



size_t Messages::ConvertToTime(int hour, int minute, int second, int milisecond)
{
    return hour * 10000000 + minute * 100000 + second*1000 + milisecond;
}


void Messages::GetValuesFromTime(size_t time, int *hour, int* minute, int* second, int* milisecond)
{
    *milisecond = time % 1000;
    time /= 1000;

    *second = time % 100;
    time /= 100;

    *minute = time % 100;
    time /= 100;

    *hour = time;
}


size_t Messages::GetTimeFromString(std::string lexem)
{
    if (lexem == "nv") return 0;

    int hour, minute, second, milisecond;
    std::string part;
    std::stringstream ss;
    ss << lexem;

    try
    {
        std::getline(ss, part, '/');
        hour = stoi(part);

        std::getline(ss, part, '/');
        minute = stoi(part);

        std::getline(ss, part, '/');
        second = stoi(part);

        std::getline(ss, part, '/');
        milisecond = stoi(part);

    }
    catch (std::invalid_argument e)
    {
        return 0;
    }

    return ConvertToTime(hour, minute, second, milisecond);
}


