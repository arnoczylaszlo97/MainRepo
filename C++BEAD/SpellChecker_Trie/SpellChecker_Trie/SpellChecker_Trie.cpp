#include <iostream>
using namespace std;
#include "Trie.h"
#include<fstream>
#include <string>
#include<vector>
#include<sstream>
#include<algorithm>

int main()
{
	// ARNÓCZY LÁSZLÓ VINCE : YKQEYD
	// READING WORDS FROM TXT FILE AND INSERT ALL WORDS TO THE TRIE DATASTRUCTURE. 
	Trie trie = Trie();

	ifstream inputFile("wordsEn.txt");
	while (!inputFile.eof()) {
		string s;
		getline(inputFile, s);
		trie.Insert(s);

	}
	inputFile.close();

	// READ FROM USER INPUT TO STRING
	cout << " [ * ] :: WRITE  AN ENGLISH  SENTENCE! ::" << endl;
	string sentence;
	getline(cin, sentence);

	//CONSOLE CLEAR
	system("cls");
	map <int, pair<string, bool>> WordsxCorrect; // NUMBER-WORD-BOOL(SEARCH METHOD IN TRIE)
	char space_char = ' ';
	stringstream sstream(sentence);
	int number = 0; //NUMBER FOR KEY IN MAP
	while (!sstream.eof())
	{
		string word;
		getline(sstream, word, space_char); //READ WORD TO WHITESPACE

		word.erase(remove_if(word.begin(), word.end(), [](unsigned char c) {
			if (c != '\'' && ispunct(c)) {
				return true;
			}
			return false; }), 
		word.end()); // REMOVE ISPUNCT CHARACTERS EXCEPT APHOSTROPH

		word.erase(remove_if(word.begin(), word.end(), isdigit), word.end()); // REMOVE NUMBER CHARACTERS

		transform(word.begin(), word.end(), word.begin(), [](unsigned char c)
			{return tolower(c);
			});	// TRANSFORM LETTERS TO LOWERCASE

		WordsxCorrect.emplace(make_pair(number++, make_pair(word, trie.Search(word)))); // ADD WORD TO WORDxCORRECT DICTIONARY
	}

	cout << "Number of words in the trie: " << trie.mAllWords << endl; // HOW MANY WORDS IN THE TRIE
	cout << "-> " << sentence << endl;

	// ::ALL WORDS IN THE SENTENCE
	for (const auto& item : WordsxCorrect)
	{
		cout << "[ " << item.first << " ] -> " << item.second.first << " -> " << item.second.second << endl;
	}

	// :: ALL CORRECT
	if (all_of(WordsxCorrect.begin(), WordsxCorrect.end(), [](pair<int, pair<string, bool>> item) {return item.second.second == 1; }))
	{
		cout << ":: All words are CORRECT! ::" << endl;
	}
	// :: ALL INCORRECT
	else if (all_of(WordsxCorrect.begin(), WordsxCorrect.end(), [](pair<int, pair<string, bool>> item) {return item.second.second == 0; }))
	{
		cout << ":: All words are INCORRECT! ::" << endl;
	}

	// :: IF SOME OF THE GIVEN WORDS ARE INCORRECT DISPLAY THE WRONG WORDS
	else
	{
		cout << ":: NOT all words are correct! ::" << endl;
		cout << ":: Incorrect words : ";

		for_each(WordsxCorrect.begin(), WordsxCorrect.end(), [](pair<int, pair<string, bool>> item) {
			if (item.second.second == 0) {
				cout << "[ " << item.second.first << " ], ";
			}});
	}

}