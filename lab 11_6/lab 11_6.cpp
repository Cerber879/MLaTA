// 11.6. Длина линии (6)
// Имеется круг радиуса R с центром в начале координат. Заданы две точки(X1, Y1) и(X2, Y2). 
// Требуется найти минимальную длину линии, соединяющей эти точки, но не пересекающей внутренность круга.
// 
// Ввод из файла INPUT.TXT. В первой строке находится целое число N – количество блоков входных данных. 
// Далее следуют N строк, каждая из которых содержит пять вещественных чисел через пробел – X1, Y1, X2, Y2 и R.
// 
// Вывод в файл OUTPUT.TXT. Для каждого блока входных данных выводится одно вещественное число 
// с тремя знаками после запятой - минимальная длина линии.

// VS 2022  Афанасьев Никита Андреевич  ПС 23

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <chrono>

const std::string INPUT_FILE = "input2.txt";
const std::string OUTPUT_FILE = "output.txt";

const double RADIAN = 57.2958;
const double PI = 3.14159265;
const double MAX_ANGLE = 180;

struct Point
{
	double x, y;
};

struct Data
{
	Point p1;
	Point p2;
	double r;
};

std::vector<Data> ReadInputFile()
{
	std::ifstream inFile(INPUT_FILE);
	
	int N;
	inFile >> N;
	std::vector<Data> vecData(N);

	for (size_t i = 0; i < N; ++i)
	{
		inFile >> vecData[i].p1.x >> vecData[i].p1.y
			>> vecData[i].p2.x >> vecData[i].p2.y >> vecData[i].r;
	}

	inFile.close();

	return vecData;
}

double Round(double value, int precision)
{
	double scale = std::pow(10.0, precision);
	return std::abs(std::round(value * scale) / scale);
}

bool Sign(double num)
{
	bool signX = num >= 0 ? 1 : 0;
	return signX;
}

int SignNum(double num)
{
	if (Sign(num))
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

double Distantion(double x1, double y1, double x2, double y2)
{
	double x = x1 - x2;
	double y = y1 - y2;

	double quadraHypotenuse = pow(x, 2) + pow(y, 2);
	double hypotenuse = sqrt(quadraHypotenuse);

	return hypotenuse;
}

bool Intersections(double x1, double y1, double x2, double y2, double r) 
{
	double segmentLength = Distantion(x1, y1, x2, y2);
	double dotProduct = (0 - x1) * (x2 - x1) + (0 - y1) * (y2 - y1);
	double projection = dotProduct / segmentLength;

	if (projection < 0)
	{
		return false;
	}

	if (projection > segmentLength) 
	{
		return false;
	}

	double closestX = x1 + (projection / segmentLength) * (x2 - x1);
	double closestY = y1 + (projection / segmentLength) * (y2 - y1);

	if ((closestX * closestX + closestY * closestY) <= r * r) 
	{
		return true;
	}

	return false;
}

bool SignPoint(Point p)
{
	double signPoint = p.x * p.y;

	if (Sign(signPoint))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ChangeSignCoordinatesByPoint(Point p, double& x1, double& y1, double& x2, double& y2)
{
	x1 *= SignNum(p.x);
	x2 *= SignNum(p.x);
	y1 *= SignNum(p.y);
	y2 *= SignNum(p.y);
}

void SetSignCoordinates(Point p, double& x1, double& y1, double& x2, double& y2, double r)
{
	if (std::abs(p.x) > r)
	{
		if (SignPoint(p))
		{
			y2 = -y2;
		}
		else
		{
			y1 = -y1;
		}
	}
	if (std::abs(p.y) > r)
	{
		if (SignPoint(p))
		{
			x1 = -x1;
		}
		else
		{
			x2 = -x2;
		}
	}
}

std::pair<Point, Point> IntersectionCoordinates(Point p, double r)
{
	double tgArc = p.y / p.x;
	double arcDirect = atan(tgArc);
	double arcAdjacentDirect = (PI / 2) - arcDirect;

	double d = sqrt(pow(p.x, 2) + pow(p.y, 2));
	double cosCenterArc = r / d;
	double arcTrinagle = acos(cosCenterArc);

	double alpha = PI - arcDirect - arcTrinagle;
	double betta = PI / 2.0 - (PI - arcAdjacentDirect - arcTrinagle);

	double x1 = r * Round(cos(alpha), 8);
	double y1 = r * Round(sin(alpha), 8);

	double x2 = r * Round(cos(betta), 8);
	double y2 = r * Round(sin(betta), 8);

	ChangeSignCoordinatesByPoint(p, x1, y1, x2, y2);
	SetSignCoordinates(p, x1, y1, x2, y2, r);

	if (p.x == 0 && !Sign(p.y) || p.y == 0 && !Sign(p.x))
	{
		return std::make_pair(Point(x2, y2), Point(x1, y1));
	}

	return std::make_pair(Point(x1, y1), Point(x2, y2));
}



double LengthArcCircle(double arc, double r)
{
	double corner = arc * RADIAN;
	double lenArc = (corner * PI * r) / MAX_ANGLE;

	return lenArc;
}

double MinArcCircle(double arc1, double arc2)
{
	if ((arc1 + arc2) * RADIAN > MAX_ANGLE)
	{
		return std::abs(arc1 - arc2);
	}
	else
	{
		return (arc1 + arc2);
	}
}

double CalcLeftArc(double arc1, double arc2)
{
	double parallelArc = (PI - arc1) * 2 + arc1;
	return parallelArc - arc2;
}

double ArcCircle(Point p1, Point p2, double r)
{
	double cosArc1 = p1.x / r;
	double arc1 = acos(cosArc1);

	double cosArc2 = p2.x / r;
	double arc2 = acos(cosArc2);

	if (Sign(p1.y) == Sign(p2.y))
	{
		return std::abs(arc1 - arc2);
	}
	else if (Sign(p1.x) || Sign(p2.x))
	{
		return MinArcCircle(arc1, arc2);
	}
	else
	{
		return CalcLeftArc(arc1, arc2);
	}
}

std::pair<Point, Point> SelectPoints(double arc1, double arc2, std::pair<Point, Point> points1, std::pair<Point, Point> points2)
{
	if (arc1 <= arc2)
	{
		return std::pair<Point, Point>(points1.first, points2.second);
	}
	else
	{
		return std::pair<Point, Point>(points1.second, points2.first);
	}
}

std::vector<double> ProcessCalculation(std::vector<Data>& data)
{
	std::vector<double> minLines;
	std::for_each(data.begin(), data.end(), [&minLines](const Data d)
		{
			if (Intersections(d.p1.x, d.p1.y, d.p2.x, d.p2.y, d.r))
			{
				std::pair<Point, Point> points1 = IntersectionCoordinates(d.p1, d.r);
				std::pair<Point, Point> points2 = IntersectionCoordinates(d.p2, d.r);

				double arc1 = ArcCircle(points1.first, points2.second, d.r);
				double arc2 = ArcCircle(points1.second, points2.first, d.r);

				std::pair<Point, Point> points = SelectPoints(arc1, arc2, points1, points2);
				double minArc = std::min(arc1, arc2);
				double lenArc = LengthArcCircle(minArc, d.r);

				double line1 = Distantion(d.p1.x, d.p1.y, points.first.x, points.first.y);
				double line2 = Distantion(d.p2.x, d.p2.y, points.second.x, points.second.y);

				double line = line1 + line2 + lenArc;
				minLines.push_back(line);
			}
			else
			{
				double line = Distantion(d.p1.x, d.p1.y, d.p2.x, d.p2.y);
				minLines.push_back(line);
			}
		});

	return minLines;
}

void PrintLengthLines(const std::vector<double>& minLines)
{
	std::ofstream outFile(OUTPUT_FILE);

	if (!minLines.empty())
	{
		outFile << std::fixed << std::setprecision(3);
		std::copy(minLines.begin(), minLines.end(), std::ostream_iterator<double>(outFile, "\n"));
	}				
}

int main()
{
	auto start = std::chrono::high_resolution_clock::now();
	setlocale(LC_ALL, "ru");

	std::vector<Data> data = ReadInputFile();
	std::vector<double> minLines = ProcessCalculation(data);
	PrintLengthLines(minLines);

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "Время выполнения программы: " << duration.count() << " секунд" << std::endl;

	return 0;
}