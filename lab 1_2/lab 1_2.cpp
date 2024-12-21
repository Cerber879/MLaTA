// 1.2.Колорадский жук (4)
//     Прямоугольный садовый участок длиной M ×N метров(1≤ M, N ≤5) разбит на квадраты со стороной 1 метр. 
// На этом участке вскопана грядка картошки.Грядкой является связанное множество квадратов.Иными словами, 
// из любого квадрата этой грядки можно попасть в любой другой квадрат этой же грядки, последовательно 
// переходя по грядке из квадрата в квадрат через их общую сторону.
//     В некоторых квадратах грядки растут кусты картошки. Колорадский жук прилетел на один из кустов. 
// Съев все листья, он переходит через общую сторону к какому - либо соседнему свежему кусту той же грядки. 
// Жук не возвращается к тому кусту, на котором он уже был, и не приходит в те квадраты, где картошка 
// не посажена.Определить наибольшее количество кустов картошки, которые сможет съесть колорадский жук.
// 
// Ввод. В первой строке файла INPUT.TXT находятся числа M и N через пробел. Далее идут M строк по N символов. 
// Квадраты грядки с кустами картошки обозначаются символами '#', свободные квадраты – символами '.'.
// 
// Вывод. В единственной строке файла OUTPUT.TXT вывести одно число - наибольшее возможное количество съеденных кустов картошки.

// VS 2022  Афанасьев Никита Андреевич  ПС 23

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

const std::string INPUT_FILE("input.txt");
const std::string OUTPUT_FILE("output.txt");

void readPlot(std::vector<std::vector<char>> &garden) {
    std::ifstream inFile(INPUT_FILE);

    int countRows, countColumns;
    inFile >> countRows >> countColumns;
    garden.resize(countRows, std::vector<char>(countColumns));
    inFile.get();

    char ch;
    for (int i = 0; i < countRows; i++) {
        for (int j = 0; j < countColumns; j++) {
            inFile >> ch;
            garden[i][j] = ch;
        }
        inFile.get();
    }

    inFile.close();
}

void findMaxWay(std::vector<std::vector<char>> &visited, std::vector<std::vector<char>> &garden, int i, int j, int &len) {

    if (visited [i][j] != '.' && i >= 0 && j >= 0 && i < garden.size() && j < garden[i].size() && garden[i][j] == '#') {
        len += 1;
        visited[i][j] = '.';
    }

    findMaxWay(visited, garden, i, j + 1, len);
    findMaxWay(visited, garden, i + 1, j, len);
    findMaxWay(visited, garden, i, j - 1, len);
    findMaxWay(visited, garden, i - 1, j, len);

}

int main()
{
    setlocale(LC_ALL, "RU");
    
    int maxLen = 0;
    std::vector<std::vector<char>> garden;
    readPlot(garden);

    for (int i = 0; i < garden.size(); i++) {
        for (int j = 0; j < garden[0].size(); j++) {
            if (garden[i][j] == '#') {
                std::vector<std::vector<char>> visited(garden.size(), std::vector<char>(garden[0].size()));
                findMaxWay(visited, garden, i, j, maxLen);
            }
        }
    }

    std::cout << maxLen;

    return 0;
}
