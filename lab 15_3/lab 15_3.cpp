//  15.3.Даты (6)
//  Играют двое. Задается какая - то дата високосного года, отличная от 31 декабря. Каждый игрок при своем ходе
//  называет более позднюю дату, увеличивая на 1 или 2 либо день в месяце, либо номер месяца, но не оба сразу. 
//  При этом сочетание дня и месяца должно оставаться корректной датой. Игрок, назвавший 31 декабря, проигрывает. 
//  Оба играют наилучшим образом. По заданной дате вывести, кто выиграет.
// 
//  Ввод из файла INPUT.TXT. В первой строке задано количество вариантов N(1 ≤ N ≤ 10). 
//  В каждой из следующих N строк находятся через пробел два числа, задающих очередной вариант даты и обозначающие день и месяц.
// 
//  Вывод в файл OUTPUT.TXT. Вывести через пробел N значений b1, b2, … bN. Величина bi равна 1, 
//	если при i - м варианте выигрывает первый(начинающий) игрок. В противном случае bi = 2.

// VS 2022  Афанасьев Никита Андреевич  ПС 23

#include "lab 15_3.h"

std::vector<std::pair<int, int>> ReadDates(std::istream& cin)
{
    std::ifstream input("input.txt");

    std::vector<std::pair<int, int>> dates;
    std::string line;

    int N;
    input >> N;

    int day, month;
    for (int i = 0; i < N; ++i)
    {
        input >> day >> month;
        dates.push_back(std::make_pair(day, month));
    }

    return dates;
}

bool CheckDate(int d, int m)
{
    int divider = MAX_MOTION + 1;
    int tentativeDay = 27;

    if (m < 4)
    {
        int remains = (m + 2) % divider;
        tentativeDay += remains;
        if (d > tentativeDay)
        {
            return true;
        }
    }

    return false;
}

int ResultGame(int d, int m)
{
    int divider = MAX_MOTION + 1;
    int remains = m % divider;
    int win;

    if (CheckDate(d, m))
    {
        win = (d - 1 + remains) % divider == 0 ? 2 : 1;
        return win;
    }
    else
    {
        win = (d - remains) % divider == 0 ? 2 : 1;
        return win;
    }
}

void PrintWinners(std::vector<std::pair<int, int>>& dates, std::ofstream& output)
{
    int winner;
    for (std::pair<int, int> date : dates)
    {
        winner = ResultGame(date.first, date.second);
        output << winner << std::endl;
    }
}

int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    std::vector<std::pair<int, int>> dates = ReadDates(input);
    PrintWinners(dates, output);

    input.close();
    output.close();

    return 0;
}
