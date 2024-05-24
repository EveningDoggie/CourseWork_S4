#include "Words.h"


Words::Words(int undoSize)
{
    std::string line;
    std::string name, value;
    std::stringstream ss;
    _undoSize = undoSize;

    std::ifstream in(_pathToDictionary);
    if (!in.is_open())
    {
        throw std::logic_error("File is not opened");
    }

    while (std::getline(in, line))
    {
        ss << line;
        std::getline(ss, name, ';');
        std::getline(ss, value, ';');
        
        if(name!="" && value!="")
            words[name] = value;

        ss.str("");
        ss.clear();
    }
    
    in.close(); 
}

Words::~Words()
{
    try
    {
        saveDictionary(_pathToDictionary);
        for (auto x : undodeque)
        {
            delete x;
        }
    }
    catch(std::logic_error e)
    {
        std::cout << e.what();
    }
}

void Words::saveDictionary(std::string pathToDictionary)
{
    std::ofstream outFile(pathToDictionary);

    if (!outFile.is_open())
    {
        throw std::logic_error("File is not opened");
    }

    for (auto v : words)
    {
        outFile << v.first << ";" << v.second << std::endl;
    }

    outFile.close();
}

void Words::saveToDeque(std::string* path, std::vector<std::string>* vector)
{
    auto *pair = new std::pair<std::string, std::vector<std::string>>();
    pair->first = *path;
    pair->second = *vector;
    undodeque.push_back(pair);

    if (undodeque.size() > _undoSize)
        undodeque.pop_front();
}

void Words::undo()
{
    std::ofstream outFile(undodeque.back()->first);
    if (!outFile.is_open())
    {
        throw std::logic_error("File is not opened");
    }

    for (auto v : undodeque.back()->second)
    {
        outFile << v;
    }

    outFile.close();
    undodeque.pop_front();
}



void Words::wordsReplace(std::string path, TypeOfReplacement type)
{
    std::string word, line, endsymb, replace;
    std::ifstream in(path);
    std::stringstream ss;
    std::vector<std::string> replacementWords;
    std::vector<std::string> originalWords;
    if (!in.is_open())
    {
        throw std::logic_error("File is not opened");
    }

    if (Words::TypeOfReplacement::Auto)
    {
        while (std::getline(in, line))
        {
            ss << line;
            while (std::getline(ss, word, ' '))
            {
                replace = "";
                for (auto x : words)
                {
                    if (x.second.find("," + word + ",") != std::string::npos)
                    {
                        replace = x.first;
                        break;
                    }
                }

                if (type==Words::TypeOfReplacement::Learning && replace == "")
                {
                    replace = addValueToDictionary(word);
                }

                replacementWords.push_back(replace!="" ? replace : word);
               

                originalWords.push_back(word);
                originalWords.push_back(" ");
                replacementWords.push_back(" ");
            }

            ss.str();
            ss.clear();
            replacementWords.push_back("\n");
            originalWords.push_back("\n");
        }
       
    }

    in.close();


    std::ofstream outFile(path);
    if (!outFile.is_open())
    {
        throw std::logic_error("File is not opened");
    }

    for (auto v : replacementWords)
    {
        outFile << v;
    }

    outFile.close();

    saveToDeque(&path, &originalWords);
}


void Words::printDictionary()
{
    for (auto v : words)
    {
        std::cout << v.first << ";" << v.second << std::endl;
    }
}

std::string Words::addValueToDictionary(std::string word)
{

    std::map<std::string, std::string>::iterator It = words.find(word);
    if (It != words.end()) return "";

    std::cout << "For word '"<<word<<"' reference value is not finded. Enter a reference word for this word. Enter - for skip\n";
    std::string referenceWord;
    std::cin >> referenceWord;
    if (referenceWord == "-") return "";


    if (words.find(referenceWord) != words.cend())
    {
        words[referenceWord] = "," + word + ",";
    }
    else
    {
        words[referenceWord] += "," + word + ",";
    }
    std::cout << "Saved";
    return referenceWord;
}
