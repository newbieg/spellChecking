#include "setWords.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	cout << "Loading Dictionary \n";
	setWords bob;
	bob.load("linux.words");
	bob.toLower();
	if(argc > 1)
	{
		for(int i = 1; i < argc; i ++)
		{
			string word = argv[i];
			if(bob.checkSpell(word))
			{
//				cout << "Good Spellin'\n";
			}
			else
			{
				cout << "Not Good:  " << word << "\n";
			}
		}
	}
	else
	{
		while(cin)
		{
			string word = "";
			cin >> word;
			word = dropNonChar(word);
			word = strLower(word);
			if(bob.checkSpell(word))
			{
//				cout << "Good Spellin'\n";
			}
			else
			{
				cout << "Not Good:" << word << ":\n";
			}
		}
	}
}


