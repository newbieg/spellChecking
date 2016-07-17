/*	HINT: the unordered list type requires a c++11 compile
 *	wrather than the normal version.
 * */

#include "setWords.h"
#include <iostream>
#include <fstream>



using namespace std;

string strLower(string input)
{
	for(int i = 0; i < input.length(); i ++)
	{
		if(input[i] >= 'A' && input[i] <= 'Z')
		{
			input[i] = input[i] - 'A';
			input[i] += 'a';
		}
	}
	return input;
}

string dropNonChar(string input)
{
	string modified = "";
	for(int i = 0; i < input.length(); i ++)
	{
		if(input[i] >= 'a' && input[i] <= 'z')
		{
			modified += input[i];
		}
		else if(input[i] >= 'A' && input[i] <= 'Z')
		{
			modified += input[i];
		}
		else if(input[i] >= '0' && input[i] <= '9')
		{
			modified += input[i];
		}
		else if(input[i] == '\'' && !(i == 0) && i != input.size() - 1)
		{
			modified += input[i];
		}
		else
		{
			modified += " ";
		}
	}
	return modified;
}

setWords::setWords()
{

}

bool setWords::load(string fileName)
{
	string word;
	bool result = false;
	ifstream inFile(fileName.c_str());
	if(inFile.good())
	{
		result = true;
		while(!(inFile.eof()) && inFile.good())
		{
			inFile >> word; 
			addWord(word);
		}
	}
	
	inFile.close();
	return result;
}

bool setWords::save(string fileName)
{
	bool notDone = true;
	ofstream outFile(fileName.c_str());
	if(outFile.good())
	{
		for(const string& nextWord: uol)
		{
			outFile << nextWord << endl;
		}
	}	

	return !(notDone);
}


void setWords::addWord(string word)
{
	uol.emplace(word);
}

void setWords::remove(string word)
{
	uol.erase(word);
}

void setWords::print()
{
	for(const string& nextWord: uol)
	{
		cout << nextWord << endl;
	}
}

void setWords::toLower()
{
	unordered_set <string> newLibrary;
	for(const string& nextWord: uol)
	{
		newLibrary.emplace(strLower(nextWord));
	}
	uol = newLibrary;
}

void setWords::dropNonChars()
{
	unordered_set <string> newLibrary;
	for(const string& nextWord: uol)
	{
		newLibrary.emplace(dropNonChar(nextWord));
	}
	uol = newLibrary;
}


bool setWords::checkSpell(string testWord)
{
	return uol.find(testWord) != uol.end();
}

/*
int main()
{
	setWords bob;
	bob.load("linux.setWords");
//	bob.print();
	bob.save("linux.setWords.txt");	
}
*/
