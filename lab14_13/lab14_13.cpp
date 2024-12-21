// 14.13. Ремонт улицы (7)
//    Под главной улицeй города S проложен водопровод. Трубы уже старые и нуждаются в ремонте. Улица состоит из n участков,
// пронумерованных последовательно от 1 до n. 
//    Для каждого i - го участка комиссия определила предельно допустимый срок 
// ремонта – di дней. Это означает, что если трубы на i - м участке не будут отремонтированы к концу дня di, то водопровод 
// на этом участке выйдет из строя. 
//    Решено нанять несколько бригад для ремонта водопровода.В начале первого дня каждая 
// бригада начинает работу на своем собственном участке. Каждая бригада ремонтирует за день ровно один участок. Ночью 
// бригада перемещает всю необходимую технику на один из двух соседних участков, чтобы на следующий день работать на нем. 
// Не разрешается переходить на участок, который уже отремонтирован.Разные бригады могут работать разное число дней.
//    Требуется определить минимальное число бригад, достаточное для того чтобы отремонтировать все участки вовремя.
// 
// Ввод. В первой строке содержится целое значение n(1 ≤ n ≤ 3×10^5). Вторая строка содержит n значений di, через пробел(1 ≤ di ≤ 10^6).
// 
// Вывод. В первой строке вывести минимальное число бригад, достаточное для ремонта водопровода.Затем для каждой бригады выводятся 
// 2 целых числа : номер участка, на котором бригада начинает работать, и номер, на котором она заканчивает работу. 
// Если есть несколько вариантов ответа, вывести любой из них.

// VS 2022  Афанасьев Никита Андреевич  ПС 23

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>

const std::string INPUT_FILE("input.txt");
const std::string OUTPUT_FILE("output.txt");

const std::string ERROR_FAILED_TO_OPEN = "Failed to open '";
const std::string ERROR_FOR_READING = "' for reading\n";
const std::string FAILED_READ_DATA = "Failed to read data from input file\n";
const std::string ERROR_FOR_READ_COUNT_PLOTS = "Error when reading the number of plots\n";

std::vector<int> ReadRepairTime(std::ifstream& inputFile) 
{
    std::vector<int> repairTime;
    std::ifstream file(INPUT_FILE);

    int countPlots;
    try
    {
        file >> countPlots;
        file.get();
    }
    catch (const std::runtime_error& e) 
    {
        std::cout << ERROR_FOR_READ_COUNT_PLOTS << std::endl;
        return std::vector<int>();
    }

    repairTime.resize(countPlots);

    std::string line;
    getline(file, line);

    if (!line.empty()) 
    {
        std::istringstream iss(line);
        int time;
        for (int i = 0; i < countPlots; i++) 
        {
            iss >> time;
            repairTime[i] = time;
        }
    }

    file.close();

    return repairTime;
}

void PrintRepairScheme(std::vector<std::pair<int, int>>& scheme) {
    std::ofstream file(OUTPUT_FILE);

    file << scheme.size() << std::endl;

    for (int i = 0; i < scheme.size(); i++) 
    {
        file << scheme[i].first + 1 << " " << scheme[i].second + 1 << std::endl;
    }
}

std::vector<std::pair<int, int>>& AddFirstPair(std::vector<std::pair<int, int>>& scheme, int& i, int& j, const int& first, const int& second) 
{
    if (first >= second) 
    {
        scheme.push_back({ 0, first });
        i++;
    }
    else 
    {
        scheme.push_back({ second, 0 });
        j--;
    }

    return scheme;
}

void ReplacePairs(std::vector<std::pair<int, int>>& scheme, const std::vector<std::pair<int, int>>& schemeToLine, int indx, bool isForward) 
{
    int position = scheme.size() - 1;
    int el = std::max(scheme[position].first, scheme[position].second) + 1;

    while (position > 0 && std::min(scheme[position - 1].first, 
        scheme[position - 1].second) >= std::min(schemeToLine[indx].first, schemeToLine[indx].second)) 
    {
        position--;
        el = std::max(scheme[position].first, scheme[position].second) + 1;
    }

    if (std::min(scheme[position].first, scheme[position].second) >= std::min(schemeToLine[indx].first, schemeToLine[indx].second)) 
    {
        el = std::min(scheme[position].first, scheme[position].second);
    }

    if (std::min(scheme[position].first, scheme[position].second) >= std::min(schemeToLine[indx].first, schemeToLine[indx].second)) 
    {
        while (position + 1 <= scheme.size() && std::max(schemeToLine[indx].first, schemeToLine[indx].second)
            >= std::max(scheme[position].first, scheme[position].second)) 
        {
            scheme.erase(scheme.begin() + position);
            position++;
        }
        position = scheme.size() - 1;
    }

    if (std::max(schemeToLine[indx].first, schemeToLine[indx].second) > std::max(scheme[position].first, scheme[position].second)) 
    {
        if (isForward) 
        {
            scheme.push_back({ el, schemeToLine[indx].second });
        }
        else {
            scheme.push_back({ schemeToLine[indx].first, el });
        }
    }
}

std::vector<std::pair<int, int>> ConstructionScheme(const std::vector<std::pair<int, int>>& schemeForward,
    const std::vector<std::pair<int, int>>& schemeBack) 
{
    std::vector<std::pair<int, int>> scheme;
    int i = 0, j = schemeBack.size() - 1;
    scheme = AddFirstPair(scheme, i, j, schemeForward[i].second, schemeBack[j].first);

    while (i < schemeForward.size() || j >= 0) 
    {
        if (i < schemeForward.size() && schemeForward[i].first < schemeBack[j].second) 
        {
            ReplacePairs(scheme, schemeForward, i, true);
            i++;
        }
        else if (j >= 0) 
        {
            ReplacePairs(scheme, schemeBack, j, false);
            j--;
        }
        else 
        {
            break;
        }
    }

    return scheme;
}

void FindNextStart(std::vector<int>& repairTime, int end, int& time, int& first, bool isForward)
{
    while (repairTime[end] <= time)
    {
        time--;
        isForward ? first++ : first--;
    }

    time++;
}

std::pair<int, int> FindNextMaxPair(std::vector<int>& repairTime, int lastElement, int end, int& time, int& first)
{
    bool isForward = lastElement != 0 ? true : false;

    if (repairTime[end] > time)
    {
        time++;
    }
    else
    {
        int secondElement = isForward ? end - 1 : end + 1;
        return { first, secondElement };
    }

    return { -1, -1 };
}

std::vector<std::pair<int, int>> PassageOfSite(std::vector<int>& repairTime, bool isForward)
{
    std::vector<std::pair<int, int>> scheme;
    int time = 0;
    if (isForward) 
    {
        int lastElement = repairTime.size() - 1;
        int first = 0;

        for (int i = first; i <= lastElement; i++)
        {
            std::pair<int, int> newPair = FindNextMaxPair(repairTime, lastElement, i, time, first);
            if (newPair.first != -1)
            {
                scheme.push_back(newPair);
                FindNextStart(repairTime, i, time, first, isForward);
            }
        }

        scheme.push_back({ first, repairTime.size() - 1 });
    }
    else
    {
        int lastElement = 0;
        int first = repairTime.size() - 1;

        for (int i = first; i >= lastElement; i--)
        {
            std::pair<int, int> newPair = FindNextMaxPair(repairTime, lastElement, i, time, first);
            if (newPair.first != -1)
            {
                scheme.push_back(newPair);
                FindNextStart(repairTime, i, time, first, isForward);
            }
        }
        scheme.push_back({ first, 0 });
    }

    return scheme;
}

std::vector<std::pair<int, int>> CalcConstruction(std::vector<int>& repairTime)
{
    if (!repairTime.empty()) 
    {
        typedef std::pair<int, int> pair;
        std::vector<pair> scheme;

        std::vector<pair> schemeForward = PassageOfSite(repairTime, true);
        std::vector<pair> schemeBack = PassageOfSite(repairTime, false);
        scheme = ConstructionScheme(schemeForward, schemeBack);

        return scheme;

    }

    return std::vector<std::pair<int, int>>();
}

int main() 
{
    auto start = std::chrono::high_resolution_clock::now();
    setlocale(LC_ALL, "RU");

    std::ifstream inputFile;
    inputFile.open(INPUT_FILE);

    if (!inputFile.is_open())
    {
        std::cout << ERROR_FAILED_TO_OPEN << INPUT_FILE << ERROR_FOR_READING;
        return 1;
    }

    std::vector<int> repairTime = ReadRepairTime(inputFile);

    if (inputFile.bad())
    {
        std::cout << FAILED_READ_DATA;
        return 1;
    }

    std::vector<std::pair<int, int>> scheme = CalcConstruction(repairTime);
    PrintRepairScheme(scheme);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Время выполнения программы: " << duration.count() << " секунд" << std::endl;

    return 0;
}
