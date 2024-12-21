// 2.10.Шестеренки (7)
// 
// Имеется система сцепленных шестеренок, пронумерованных от 1 до N. Заданы пары номеров сцепленных шестеренок. 
// Первая должна двигаться по часовой стрелке. Определить характер движения всех шестеренок.
// 
// Варианты движения:
// clockwise - по часовой;
// unclockwise - против;
// immovable - шестеренка неподвижна;
// block - заклинивание.
// 
// Ввод из файла INPUT.TXT. В первой строке записаны через пробел число N - количество шестеренок(2 ≤ N ≤ 10000)
// и M - количество пар(1 ≤ M ≤ 100000). В следующих M строках указаны пары шестеренок в виде двух номеров через пробел.
// 
// Вывод в файл OUTPUT.TXT. В i - й строке должна быть информация о движении i - й шестеренки: 
// clockwise - по часовой, against - против, immovable – шестеренка неподвижна. Если система заклинивается, то выдать block.

// VS 2022  Афанасьев Никита Андреевич  ПС 23

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <chrono>

const std::string FILE_OF_GEAR_SYSTEM = "input.txt";
const std::string FILE_OF_DIRECTION_GEARS = "output.txt";

void readGearSystem(std::vector<std::vector<int>> &gearSystem, std::vector<std::string> &dir) {
	std::ifstream file(FILE_OF_GEAR_SYSTEM);

	if (!file) {
		std::cout << "Не удалось открыть файл " << FILE_OF_GEAR_SYSTEM << std::endl;
		return;
	}
	else {
		std::cout << "Файл " << FILE_OF_GEAR_SYSTEM << " успешно открыт" << std::endl;
	}

	int countGear, countPair;
	file >> countGear >> countPair;

	dir.resize(countGear);
	gearSystem.resize(countGear);

	int firstGear, secondGear;
	for (int i = 0; i < countPair; i++) {
		file >> firstGear >> secondGear;
		gearSystem[firstGear - 1].push_back(secondGear);
		gearSystem[secondGear - 1].push_back(firstGear);
	}

	file.close();
}

void printDirectonGears(std::vector<std::string>& dir) {
	std::ofstream file(FILE_OF_DIRECTION_GEARS);
	if (!dir.empty()) {
		for (int i = 0; i < dir.size(); i++) {
			if (dir[i].empty()) {
				file << "immovable" << std::endl;
			}
			else {
				file << dir[i] << std::endl;
			}
		}
	}
	else {
		file << "block" << std::endl;
	}
}

void movementOfGears(std::vector<std::vector<int>>& gearSystem, std::vector<std::string>& dir) {
	std::queue<int> queOfGears;
	queOfGears.push(1);

	dir[0] = "clockwise";

	while (!queOfGears.empty()) {

		int currGear = queOfGears.front() - 1;
		queOfGears.pop();

		for (int i = 0; i < gearSystem[currGear].size(); i++) {
			int bondGear = gearSystem[currGear][i] - 1;
			if (dir[bondGear].empty()) {
				if (dir[currGear] == "clockwise") {
					dir[bondGear] = "unclockwise";
				}
				else {
					dir[bondGear] = "clockwise";
				}
				queOfGears.push(bondGear + 1);
			}
			else if (dir[currGear] == dir[bondGear]) {
				dir.clear();
				return;
			}
		}
	}
}

int main() {
	auto start = std::chrono::high_resolution_clock::now();
	setlocale(LC_ALL, "RU");

	std::vector<std::vector<int>> gearSystem;
	std::vector<std::string> dir;

	readGearSystem(gearSystem, dir);
	movementOfGears(gearSystem, dir);
	printDirectonGears(dir);

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "Время выполнения программы: " << duration.count() << " секунд" << std::endl;

	return 0;
}