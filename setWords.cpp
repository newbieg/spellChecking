/*	HINT: the unordered list type requires a c++11 compile
 *	wrather than the normal version.
 * */

#include "setWords.h"
#include <iostream>
#include <fstream>
#include <sstream>



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

string dumpChars(string &input, string dropList)
{
	for(int i = 0; i < input.length(); i ++)
	{
		for(int k = 0; k < dropList.length(); k ++)
		{
			if(input[i] == dropList[k])
			{
				input.erase(i, 1);
				i --;
			}
		}
	}
	return input;
}

setWords::setWords()
{

}

bool setWords::load(string fileName)
{
	string word;
	stringstream ss;
	bool result = false;
	ifstream inFile(fileName.c_str());
	if(inFile.good())
	{
		ss << inFile.rdbuf();
		while(ss >> word)
		{
			addWord(word);
		}
		result = true;
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

	outFile.close();
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


/** failed concept. Keep thinking about it...
vector <string> setWords::wildCard(string start, string end)
{
	uol.find(start);
		
}
/**/


/*
int main()
{
	setWords bob;
	bob.load("linux.setWords");
//	bob.print();
	bob.save("linux.setWords.txt");	
}
*/
