#include "Matrix.h"
#include <iostream>
#include<vector>
#include<random>
#include <windows.h>
#include <thread>


// !!!Valamiért az operatornak nem enged 3 parametert átadni ezért a körszám kiíratás nem szerepel az operatoros kiírássban, csak a Display() metódusban.
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<int>>& matrix)
{
	system("cls");
	//std::cout << "CYCLE: #" << count++ << std::endl;
	for (size_t i = 0; i < matrix.size(); i++)
	{
		for (size_t j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] == 1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				os << (char)254u << ' ';
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				os << (char)254u << ' ';
			}
		}
		os << "\n";
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	return os;
}

Matrix::Matrix(const int edgeLength)
	:mWidth(edgeLength),
	mHeight(edgeLength),
	mPvalue(0.1)
{
	std::cout << "Square 10%" << std::endl;
	Create(mWidth, mHeight, mPvalue);
	//Display(GameTable);
	std::cout << GameTable << std::endl;
	ModifyCells();
}
Matrix::Matrix(const int height, const int width)
	:mWidth(width),
	mHeight(height),
	mPvalue(0.1)
{
	std::cout << "#Rectangle with 10% created" << std::endl;
	Create(mWidth, mHeight, mPvalue);
	//Display(GameTable);
	std::cout << GameTable << std::endl;
	ModifyCells();
}
Matrix::Matrix(const int edgeLength, const double Pvalue)
	:mWidth(edgeLength),
	mHeight(edgeLength),
	mPvalue(Pvalue)
{
	std::cout << "#Square with Pvalue created!" << std::endl;
	Create(mWidth, mHeight, mPvalue);
	//Display(GameTable);
	std::cout << GameTable << std::endl;
	ModifyCells();
}
Matrix::Matrix(const int height, const int width, const  double Pvalue)
	:mWidth(width),
	mHeight(height),
	mPvalue(Pvalue)
{
	std::cout << "#Rectangle with Pvalue created!" << std::endl;
	Create(mWidth, mHeight, mPvalue);
	Display(GameTable);
	//std::cout << GameTable << std::endl;
	ModifyCells();
}
Matrix::Matrix(const int height, const int width, const int top, const int left, const std::vector<std::vector<int>> pattern)
	:mWidth(width),
	mHeight(height),
	mTop(top),
	mLeft(left),
	mPattern(pattern)
{
	std::cout << "#Rectangle with included cell pattern created!" << std::endl;
	Create2(mHeight, mWidth, mTop, mLeft, mPattern);
	Display(GameTable);
	//std::cout << GameTable << std::endl;
	ModifyCells();
}

void Matrix::Create(const int width, const int height, const double Pvalue)
{
	std::random_device rD;
	std::default_random_engine rE(rD());
	std::uniform_int_distribution<int> uniform_dist(1, 1000);

	for (size_t i = 0; i < height; i++)
	{
		std::vector<int> row;
		for (size_t j = 0; j < width; j++)
		{
			int random = uniform_dist(rE);
			if (random <= 1000 * Pvalue)
			{
				row.push_back(1);
			}
			else
			{
				row.push_back(0);
			}
		}
		GameTable.push_back(row);
	}
}
void Matrix::Create2(const int height, const int width, const int top, const int left, const std::vector<std::vector<int>> pattern)
{
	GameTable.resize(height, std::vector<int>(width, 0));
	if (height < top || width < left)
	{
		std::cout << "Invalid parameter!: top or left" << std::endl;
	}
	else
	{
		for (size_t i = 0; i < pattern.size(); i++)
		{
			for (size_t j = 0; j < pattern[i].size(); j++)
			{
				//if (GameTable[i + top].size() >= pattern[i].size() + left)
				if (GameTable.size() >= pattern.size() + top && GameTable[i].size() >= pattern[i].size() + left)
				{
					GameTable[i + top][j + left] = pattern[i][j];
				}
				else if (GameTable[i + top].size() >= pattern[i].size() + left)
				{
					GameTable[i][j + left] = pattern[i][j];
				}
				else if (GameTable.size() + left >= pattern.size() + top)
				{
					GameTable[i + top][j] = pattern[i][j];
				}
			}
		}
	}
}
void Matrix::Display(const std::vector<std::vector<int>> matrix,  int count) const // <<operatorral
{
	system("cls");
	std::cout << "CYCLE: #" << count++ << std::endl;
	for (size_t i = 0; i < matrix.size(); i++)
	{
		for (size_t j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] == 1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				std::cout << (char)254u << ' ';
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				std::cout << (char)254u << ' ';
			}
		}
		std::cout << "\n";
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

} 

void Matrix::ModifyCells()
{
	int ALllivingCells = -1, CycleCount = 0;
	while (ALllivingCells != 0 && CycleCount++ < 100)
	{
		std::cout << "Press ENTER to continue . . . ." << std::endl;
		//std::cin.ignore();
		//system("pause");
		ALllivingCells = 0;
		for (size_t i = 0; i < GameTable.size(); i++)
		{
			for (size_t j = 0; j < GameTable[i].size(); j++)
			{
				if (GameTable[i][j] == 1)
				{
					ALllivingCells++;
				}
			}
		}
		if (ALllivingCells == 0)
		{
			break;
		}
		for (size_t i = 0; i < GameTable.size(); i++)
		{
			for (size_t j = 0; j < GameTable[i].size(); j++)
			{
				int row_idx = i;
				int col_idx = j;
				int CountOfLivingCells = CountingOneNeigbour(row_idx, col_idx);
				if (GameTable[i][j] == 1 && (CountOfLivingCells < 2))
				{
					GameTable[i][j] = 0;
				}
				else if (GameTable[i][j] == 1 && (CountOfLivingCells == 2 || CountOfLivingCells == 3))
				{
					GameTable[i][j] = 1;
				}
				else if (GameTable[i][j] == 1 && (CountOfLivingCells > 3))
				{
					GameTable[i][j] = 0;
				}
				else if ((GameTable[i][j] == 0) && (CountOfLivingCells == 3))
				{
					GameTable[i][j] = 1;
				}
				//Display(GameTable, CycleCount);
				//Sleep(10);
			}
		}
		Display(GameTable, CycleCount);
		Sleep(100);
		//std::cout << GameTable << std::endl;
	}
	std::cout << ":: SZIMULACIO VEGE ::" << std::endl;
}
int Matrix::CountingOneNeigbour(const int row_idx, const int col_idx)
{

	int count = 0;
	if ((row_idx > 0) && (col_idx > 0))
	{
		if (GameTable[row_idx - 1][col_idx - 1]) {
			count++;
		}
	}

	if (row_idx > 0)
	{
		if (GameTable[row_idx - 1][col_idx]) {
			count++;
		}
	}

	if ((row_idx > 0) && (col_idx < GameTable[row_idx].size() - 1))
	{
		if (GameTable[row_idx - 1][col_idx + 1]) {
			count++;
		}
	}

	if ((col_idx > 0))
	{
		if (GameTable[row_idx][col_idx - 1]) {
			count++;
		}
	}

	if (col_idx < GameTable[row_idx].size() - 1)
	{
		if (GameTable[row_idx][col_idx + 1]) {
			count++;
		}
	}

	if ((col_idx > 0) && (row_idx < GameTable.size() - 1))
	{
		if (GameTable[row_idx + 1][col_idx - 1]) {
			count++;
		}
	}

	if (row_idx < GameTable.size() - 1)
	{
		if (GameTable[row_idx + 1][col_idx]) {
			count++;
		}
	}

	if ((row_idx < GameTable.size() - 1) && (col_idx < GameTable[row_idx].size() - 1))
	{
		if (GameTable[row_idx + 1][col_idx + 1]) {
			count++;
		}
	}

	return count;
}
