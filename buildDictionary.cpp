/* Use this program to extract unique words from a book. These words will not be saved in any order, 
 * It does not handle hyphens and other non alphabetical chars, they are simply dropped. It is suggested
 * that after collecting all your words, that you run the resulting file through this program a couple more times untill
 * the resulting file stops growing/shrinking in size.  
 *
 */
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
