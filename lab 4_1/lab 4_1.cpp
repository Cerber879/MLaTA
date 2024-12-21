// 4.1. Прогрессия (6)
//	  Король Камбузии с детства боится несчастливых арифметических прогрессий с разностью 13. 
// Однажды ему представили список расходов на нужды подданных, состоящий из N чисел. Король 
// потребовал оставить только такую начальную часть списка, в которой не скрывается несчастливая 
// арифметическая прогрессия.Либеральная общественность, считаясь с мнением короля, настаивает, 
// тем не менее, на сохранении как можно большей части списка. Найти максимальное значение K такое, 
// что из первых K чисел списка невозможно выделить M чисел, следующих в порядке их нахождения в 
// списке и образующих последовательные члены несчастливой арифметической прогрессии.Выдать члены 
// первой обнаруженной несчастливой прогрессии.
//	  Ввод из файла INPUT.TXT.Первая строка содержит два целых положительных числа N и M, разделенных 
// пробелом : N – количество чисел в списке, а M – недопустимое число членов прогрессии. Вторая 
// строка содержит список расходов в виде целых положительных чисел.
//    Ограничения : 2 ≤ N, M ≤ 5000, 1 ≤ Xi ≤ 65000, время 1 с.
//    Вывод в файл OUTPUT.TXT.В первой строке выводится единственное число K - максимальное количество
// начальных чисел списка, не содержащих в качестве подсписка M последовательных членов несчастливой 
// арифметической прогрессии.Во второй строке выводятся через пробел члены первой обнаруженной несчастливой
// прогрессии. Если ее не обнаружено, вывести No.

// VS 2022  Афанасьев Никита Андреевич  ПС 23

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <chrono>

const std::string INPUT_FILE("input.txt");
const std::string OUTPUT_FILE("output.txt");

void readListOfExpenses(std::vector<int>& expenses, int& maxLen) {
	std::ifstream inFile(INPUT_FILE);

	if (!inFile) {
		std::cout << "Не удалось открыть файл " << INPUT_FILE << std::endl;
	}
	else {
		std::cout << "Файл " << INPUT_FILE << " успешно открыт!" << std::endl;
	}

	int countExpenses;
	inFile >> countExpenses >> maxLen;
	expenses.resize(countExpenses);
	inFile.get();

	std::string line;
	std::getline(inFile, line);
	if (!line.empty()) {
		std::istringstream iss(line);
		int num;
		for (int i = 0; i < countExpenses; i++) {
			iss >> num;
			expenses[i] = num;
		}
	}
	inFile.close();
}

std::unordered_map<int, int> findUnluckSequens(std::vector<int>& expenses, int& maxLen) {
	std::unordered_map<int, int> sequens;
	for (int i = 0; i < expenses.size(); i++) {
		if (expenses[i] > 13 && sequens.count(expenses[i] - 13) > 0) {
			int lenSequen = sequens[expenses[i] - 13] + 1;
			if (lenSequen == maxLen) {
				sequens[expenses[i]] = lenSequen;
				sequens[0] = i;
				break;
			}
			else {
				sequens[expenses[i]] = lenSequen;
			}
		}
		else {
			sequens[expenses[i]] = 1;
		}
	}
	if (sequens[0] == 0) {
		sequens[0] = -1;
	}
	return sequens;
}

void printUnluckSequen(std::unordered_map<int, int>& sequens, int endSequen, int &maxLen) {
	std::ofstream outFile(OUTPUT_FILE);

	if (sequens[0] == -1) {
		outFile << "No";
	}
	else {
		outFile << sequens[0] << std::endl;

		int firstSequen = endSequen - 13 * (maxLen - 1);
		for (int i = 0; i < maxLen; i++) {
			outFile << firstSequen << " ";
			firstSequen += 13;
		}
	}
	outFile << std::endl;
}

int main()
{
	auto start = std::chrono::high_resolution_clock::now();
	setlocale(LC_ALL, "RU");

	int maxLen;
	std::vector<int> expenses;

	readListOfExpenses(expenses, maxLen);
	std::unordered_map<int, int> sequens = findUnluckSequens(expenses, maxLen);

	printUnluckSequen(sequens, expenses[sequens[0]], maxLen);

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "Время выполнения программы: " << duration.count() << " секунд" << std::endl;

	return 0;
}
