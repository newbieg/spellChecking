#include "setWords.h"
#include <iostream>
#include <string>

using namespace std;

bool lowcase = true;

int main(int argc, char ** argv)
{
	if(argc > 2)
	{
		string fileName;
		setWords diction;
		for(int i = 1; i < argc - 1; i ++)
		{
			fileName = argv[i];
			diction.load(fileName);
		}
		diction.dropNonChars();
		if(lowcase)
		{
			diction.toLower();
		}
		fileName = argv[argc - 1];
		diction.save(fileName);
	}

}
