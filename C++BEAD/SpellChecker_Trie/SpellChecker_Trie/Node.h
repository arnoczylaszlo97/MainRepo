#pragma once
#include<iostream>
#include<vector>

using namespace std;

class Node {
public:
	bool mIsWord;
	vector<shared_ptr<Node>> mPointers;
	Node();
};

