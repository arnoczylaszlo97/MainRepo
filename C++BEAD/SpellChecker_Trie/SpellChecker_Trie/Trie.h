#pragma once
#include<iostream>
#include<vector>
#include<map>
#include "Node.h"

using namespace std;

class Trie {
private:
	static string  mAlphabet;
	static map<char, int> CreateDictionary();
	static map <char, int> mDictionary;

	shared_ptr<Node> mRoot;
public:
	int mAllWords;
	Trie();
	Trie& Insert(string word); 
	bool Search(string& word) ;
};


