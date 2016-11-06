#include "setWords.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	cout << "Loading Dictionary .";
	setWords bob;
	bob.load("linux.words");
	cout << " . ";
	bob.toLower();
	cout << ". Done. Type something and hit enter, no output if word is good: \n";
	if(argc > 1)
	{
		for(int i = 1; i < argc; i ++)
		{
			string word = argv[i];
			word = strLower(word);
			word = dumpChars(word, "\",./?!#$()_[]{}|\\;:<>");
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
			//word = dropNonChar(word);
			word = strLower(word);
			word = dumpChars(word, "\",./?!#$()_[]{}|\\;:<>");

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


