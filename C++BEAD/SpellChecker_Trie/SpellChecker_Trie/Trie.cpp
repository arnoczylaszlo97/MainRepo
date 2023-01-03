#include "Trie.h"

string Trie::mAlphabet = "abcdefghijklmnopqrstuvwxyz'";

map<char,int> Trie::CreateDictionary()
{
	map<char, int> Dictionary;
	for (size_t i = 0; i < mAlphabet.size(); i++)
	{
		Dictionary.emplace(pair<char, int>(mAlphabet[i], i));
	}
	return Dictionary;
}

map<char, int> Trie::mDictionary= Trie::CreateDictionary();

Trie::Trie()
{
	mAllWords = 0;
	mRoot = make_shared<Node>(Node());
}

Trie& Trie::Insert(string word)
{
	shared_ptr<Node> current = mRoot;
	for (size_t i = 0; i < word.size(); i++)
	{
		int idx = mDictionary.find(word[i])->second;
		//char betu = mDictionary.find(word[i])->first;

		if (current->mPointers[idx] == shared_ptr<Node>(nullptr))
		{
			current->mPointers[idx] = make_shared<Node>(Node());
		}
		current = (current->mPointers[idx]);
	}
	current->mIsWord = true;
	mAllWords++;
	return *this;
}
bool Trie::Search(string& word)
{
	shared_ptr<Node> current = mRoot;
	for (size_t i = 0; i < word.size(); i++)
	{
		int idx = mDictionary.find(word[i])->second;
		//char betu = mDictionary.find(word[i])->first;

		if (current->mPointers[idx] == shared_ptr<Node>(nullptr))
		{
			return false;
		}
		current = (current->mPointers[idx]);
	}
	if (current->mIsWord == true)
	{
		return true;
	}
	return false;
}


