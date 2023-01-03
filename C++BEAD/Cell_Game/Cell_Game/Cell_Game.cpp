#include <iostream>
#include "Matrix.h"
#include<vector>

int main()
{

	//ARNÓCZY LÁSZLÓ - YKQEYD
	std::vector<std::vector<int>> v
	{
	{1,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1},
	{1,0,1,0,1,0,1,1,1,1,1,0,0,0,0,1},
	{1,1,1,1,0,1,1,0,0,1,1,0,0,1,1,0},
	{1,0,1,0,0,0,1,1,0,0,1,1,0,0,0,1},

	};

	//Matrix CellGame1(9,0.8);
	//Matrix CellGame2(16, 6);
	//Matrix CellGame3(10, 0.4);
	//Matrix CellGame4(15, 20, 0.4);
	Matrix CellGame5(17, 17, 0, 0, v);
}
