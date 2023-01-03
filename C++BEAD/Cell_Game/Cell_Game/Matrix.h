#pragma once
#include<vector>
#include<iostream>

class Matrix {
public:
	Matrix(const int edgeLength);
	Matrix(const int height, const int width);
	Matrix(const int edgeLength, const double Pvalue);
	Matrix(const int height, int width, const  double Pvalue);
	Matrix(const int height, const int width, const int top, const  int left, const std::vector<std::vector<int>> pattern);

	void Create(const int width, const int height, const double Pvalue);
	void Create2(const int height, const int width, const int top, const int left, const std::vector<std::vector<int>> pattern);
	void Display(const std::vector<std::vector<int>> matrix, int count = 0) const;

	void ModifyCells();
	int CountingOneNeigbour(const int row_idx, const int col_idx);

private:
	const int mWidth;
	const int mHeight;
	double mPvalue;
	std::vector<std::vector<int>> GameTable;

	int mTop;
	int mLeft;
	const std::vector<std::vector<int>> mPattern;
};

