// 3.3. Распил бруса (6)
//   На пилораму привезли брус длиной L метров. Известны места, в которых необходимо сделать распилы. 
// Стоимость одного распила равна длине распиливаемого бруса. Различный порядок распилов приводит к 
// различным итоговым ценам. Например, брус длиной 10 метров, который нужно распилить на расстоянии 
// 2, 4 и 7 метров можно пилить разными способами.Можно распилить сначала на отметке 2, потом 4 и потом 7. 
// Стоимость будет 10 + 8 + 6 = 24. А если сначала распилить на отметке 4, потом 2 и затем 7, то стоимость 
// составит 10 + 4 + 6 = 20. Требуется написать программу, которая определяла бы минимальную стоимость распила.
// 
//   Ввод из файла INPUT.TXT. В первой строке   содержатся   через пробел натуральные числа 
// L и N(1 ≤ L ≤ 500, N < L) – длина бруса и число разрезов. Вторая строка содержит N натуральных 
// чисел Ci(0 < Ci < L) через пробел, задающих в строго возрастающем порядке места, в которых нужно сделать распилы.
// 
//   Вывод в файл OUTPUT.TXT.В единственной строке вывести минимальную стоимость распилов.

// VS 2022  Афанасьев Никита Андреевич  ПС 23

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>

const std::string INPUT_FILE("input.txt");
const std::string OUTPUT_FILE("output.txt");

void readCutsScheme(std::vector<int>& cutsScheme, int& lenBalk) {
    std::ifstream inputFile(INPUT_FILE);

    int countCuts;
    inputFile >> lenBalk >> countCuts;
    cutsScheme.resize(countCuts + 2);
    inputFile.get();

    cutsScheme[0] = 0;
    cutsScheme[countCuts + 1] = lenBalk;

    std::string line;
    std::getline(inputFile, line);
    if (!line.empty()) {
        int num;
        std::istringstream iss(line);
        for (int i = 1; i < countCuts + 1; i++) {
            iss >> num;
            cutsScheme[i] = num;
        }
    }

    inputFile.close();
}

void printMinPrice(int price) {
    std::ofstream outputFile(OUTPUT_FILE);
    outputFile << price << std::endl;
}

int calcMinPrice(std::vector<int>& cutsScheme) {
    std::vector<std::vector<int>> minPrice(cutsScheme.size());

    for (int i = 0; i < cutsScheme.size() - 2; i++) {
        minPrice[i].push_back(cutsScheme[i+2] - cutsScheme[i]);
    }

    int diff = 3;
    while (diff < cutsScheme.size()) {
        for (int i = 0; i < cutsScheme.size() - diff; i++) {
            int minCut = std::min(minPrice[i][minPrice[i].size() - 1], minPrice[i+1][minPrice[i].size() - 1]);
            for (int j = 0; j < diff - 3 ; j++) {
                int x = (cutsScheme.size() - i - j - 5) - (cutsScheme.size() - 1 - (i + diff));
                minCut = std::min(minPrice[i][j] + minPrice[j + i + 2][x], minCut);
            }
            minPrice[i].push_back(minCut + (cutsScheme[i+diff] - cutsScheme[i]));
        }
        diff++;
    }

    for (int i = 0; i < minPrice.size(); i++) {
        for (int j = 0; j < minPrice[i].size(); j++) {
        }
    }

    return minPrice[0][minPrice[0].size() - 1];
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    setlocale(LC_ALL, "RU");

    int lenBalk;
    std::vector<int> cutsScheme;

    readCutsScheme(cutsScheme, lenBalk);

    int price = calcMinPrice(cutsScheme);
    printMinPrice(price);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Время выполнения программы: " << duration.count() << " секунд" << std::endl;

    return 0;
}
