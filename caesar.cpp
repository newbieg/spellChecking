#include "setWords.h"
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <sstream>

/*	Ceasar - takes input and either encyphers it or decyphers it based on a caesar-cypher character shift.
 *		Does not convert numbers to characters. Not because this is a hard task, but because I want to 
 *		keep things simple (how do you deal with spaces, punctuation, etc. This program does not deal with punctuation.
 *
 *	compile: 
 *		$ g++ -std=c++11 setWords.cpp caesar.cpp
 *
 *
 */


using namespace std;

string debugString; /* If you find a problem (usually with user input), just set this string to describe it. 
			Should be fully descriptive, since it will also halt any atempt at encode/decode. */

int wordsToGuess = 0; /* set with the -n command
			 if decoding a large-content file then set this to any number to reduce guessing time.
			Usually 5 to 10 is accurate enough. I added this in because I tried to encode and decode a
			full book and it took 3 seconds to run the code, which was an eternity in computer time.*/

bool isNum(char* arg)
{
	bool answer = true;
	for(int i = 0; i < strlen(arg); i ++)
	{
		if(!(arg[i] >= '0' && arg[i] <= '9'))
		{
			answer = false;
			break;
		}
	}
	return answer;
}

string strFromFile(char* fileName)
{
	ifstream inFile(fileName);
	stringstream ss;
	ss << inFile.rdbuf();
	inFile.close();
	string temp;
	string returnable;
	
	returnable = " ";
	getline(ss, temp);
	returnable += temp;
	while(getline(ss, temp))
	{
		returnable += '\n';
		returnable += temp;
	}

	return returnable;

}

void displayHelp()
{
	cout << "I don't have things really working at this time, but my idea is that the program will take" << endl << " -escaped commands like a lot of \"Nix\" command line programs do. So far I've decided on the following:\n\n" << endl;
	cout <<  "-f fileName = load the content from fileName.\n " 
	<< "-fd = load a file-dictionary other than the default, smaller dictionaries will speed up the decode, \n"
	<< "\tbut may affect accuracy of guesses about how to decode.\n"
	<< "\tyour library should have a single word per line, no non-alphabetical characters.\n"
	<< "-d = specify the action as decode, cancels out -e \n"
	<< "-e Number = specify that the content should be encoded using a shift of \"Number\", 26 being the most common\n" 
	<< "-n Number = Reduce guessing time by making a guess about offset in the first Number of words encountered.\n"
	<< "-o fileName = output goes to fileName instead of standard output.\n"
	<< "-a = Show all possible matching cypher shifts, it's possible that the best guess is the wrong one I guess...\n"
	<< "-h = Help content\n"
	<< "Note: all non-commands are taken as content to be (en/de)coded.\n"
	<< "\tfiles will be added between content in the order typed in.\n\n"
	<< "Example usage:\n\t./a.out I want to encode -f fileName.txt the end. -o fileName.out -e 10\n"
	<< "\t./a.out -f fileName.out \n\n";

}

string basicShift(string input, int offset)
{
	string tempShiftString = "";
	for(int k = 0; k < input.length(); k ++)
	{
		if(input[k] >='A' && input[k] <= 'Z')
		{
			tempShiftString += 'A' + ((input[k] - 'A' + offset) % 26);
		}
		else if(input[k] >= 'a' && input[k] <= 'z')
		{
			tempShiftString += 'a' + ((input[k] - 'a' + offset) % 26);
		}
		else
		{
			tempShiftString += input[k];
		}
	}
	return tempShiftString;
}

//return 0 if no matching words were found for any words. 
//foundWith is going to contain the number of matches found for each shift, just in case there's a possibility of multiple matches we want the best,
// 	but if there's a lot of non-characters or junk to throw off guessing we might want all possible matching, we may also get false-matches.
//input is the text we want to test on a per-word basis.
//dictionary is the set of words that we want to test against. It should be preloaded with words before running this function.
bool testShift(string &input, setWords &dictionary, vector <int> & foundWith)
{
	bool possibleMatch = false;
	foundWith.clear();
	stringstream ss;
	ss.str(input);
	
	string temp;
	string testShiftString;
	for(int i = 0; i <= 26; i ++)
	{
		foundWith.push_back(0);
	}
	if(wordsToGuess == 0)
	{
		while(ss >> temp)
		{
			for(int i = 0; i <= 26; i ++)
			{
				if(dictionary.checkSpell(strLower(basicShift(temp, i))) == true)
				{
					possibleMatch = true;
					foundWith[i] ++;
				}
			}
		}
	}
	else
	{
		while(ss >> temp && wordsToGuess > 0)
		{
			wordsToGuess --;
			for(int i = 0; i <= 26; i ++)
			{
				if(dictionary.checkSpell(strLower(basicShift(temp, i))) == true)
				{
					possibleMatch = true;
					foundWith[i] ++;
				}
			}
		}
	}
	return possibleMatch;
}

string decodeStringAll(string input, vector <int> testedShift)
{
	string output;
	for(int h = 0; h < testedShift.size(); h ++)
	{
		if(testedShift[h] > 0)
		{
			stringstream ss;
			ss.str(input);
			
			string temp;
			while(ss >> temp)
			{
				/*
				for(int i = 0; i <= temp.length() - 1; i ++)
				{
					output += ('a' + ((temp[i] - 'a') + h)%26);
				}*/
				output += basicShift(temp, h);
				output += " ";
			}
			output += "\n";
		}
	}

	return output;
	
}

string decodeStringBest(string input, vector <int> testedShift)
{
	string output;
	int bestMatch = 0;
	int findBest = 0;
	for(int i = 0; i <= 26; i ++)
	{
		if(testedShift[i] > findBest)
		{
			findBest = testedShift[i];
			bestMatch = i;
		}
	}

	stringstream ss;
	ss.str(input);
	
	string temp;
	while(ss >> temp)
	{
		/*
		for(int i = 0; i <= temp.length() - 1; i ++)
		{
			output += ('a' + ((temp[i] - 'a') + bestMatch)%26);
		}
		*/
		
		output += basicShift(temp, bestMatch);
		output += " ";
	}
	return output;
	
}

string encodeString(string input, int offset)
{
	string output;
	for(int i = 0; i < input.length(); i ++)
	{
		output += 'a' + (input[i] - 'a' + offset)%26;
	}
	return output;
}

int main(int argc, char ** argv)
{
	setWords dictionary;
	string fileName_dictionary = "linux.words";
	string fileName_output;
	string content;
	string output;
	string action = "decode";
	bool decode = true; // default setting is for decode, changes with the -e command.
	bool fileOutput = false;
	bool showAllMatches = false;
	
	string string_shift;  // string to hold the amount to shift if encode is specified.
	
	if(argc > 1)
	{
		bool commandFound = false;
		//grab commands, load content;
		for(int i = 1; i < argc; i ++)
		{
			string temp = argv[i];
			if(temp == "-f")
			{
				content += strFromFile(argv[i + 1]);
				i ++;
			}
			else if(temp == "-fd")
			{
				fileName_dictionary = argv[i + 1];
				i ++;
			}
			else if(temp =="-d")
			{
				decode = true;
				string_shift.clear();
			}
			else if(temp == "-e")
			{
				decode = false;
				if(isNum(argv[i + 1]))
				{
					string_shift = argv[i+1];
					i ++;
				}
				else
				{
					debugString = "The argument -e requires a number to offset by:\n\t-e 13\n";
				}
			}
			else if(temp == "-n")
			{
				if(isNum(argv[i + 1]))
				{
					string temp = argv[i+1];
					wordsToGuess = stoi(temp);
					i ++;
				}
				else
				{
					debugString = "The argument -e requires a number of words to use for guessing:\n\t-n 10\nIn many cases any number greater than 4 will be pretty accurate.\n";
				}
			}
			else if(temp == "-o")
			{
				fileOutput = true;
				fileName_output = argv[i + 1];
				i ++;
			}
			else if(temp == "-a")
			{
				showAllMatches = true;
			}
			else if(temp == "-h")
			{
				displayHelp();
			}
			else
			{
				
				content += " ";
				content += argv[i];
			}
		}
		
/* all commands should be loaded by now, some have been handled, so let's get the rest working correctly. */
/*		
string fileName_output;
string content;
string action = "decode";
bool decode = true; // default setting is for decode, changes with the -e command.
bool fileOutput = false;
bool showAllMatches = false;

string string_shift;  // string to hold the amount to shift if encode is specified.
*/
		if(debugString == "")
		{
			if(decode)
			{
				dictionary.load(fileName_dictionary);
				/* try to guess the shift the words have taken. then decode. */
				vector <int> possibleShift;
				possibleShift.push_back(0);
				if(testShift(content, dictionary, possibleShift))
				{
					if(showAllMatches)
					{
						output = decodeStringAll(content, possibleShift);
					}
					else
					{
						output = decodeStringBest(content, possibleShift);
					}
				}
				else
				{
					output = "No good matches for Caesar Cypher found.";
				}
			}
			else
			{
				stringstream dropWS;
				dropWS.str(content);
				
				string temp;
				while(dropWS >> temp)
				{
					output += basicShift(temp, stoi(string_shift));
					output += " ";
				}
				/* encode the content based on the string_shift */
			}
		
	/* test that the commands are loading correctly  * /
			//dictionary.load("linux.words");
			cout << "Output to file: " << (fileOutput? ("yes " + fileName_output) : "no" ) << endl;
			cout << "Decoding: " << (decode ? "yes" : "no") << endl;
			if(!(decode))
			{
				cout << "Shift by: " << string_shift << endl;
			}
			else
			{
				cout << "Show all Matches: " << (showAllMatches ? "yes" : "no") << endl;
			}
			cout << "Dictionary FileName: " << fileName_dictionary << endl;
			cout << "Content: " << content << endl;
/**/
			if(fileOutput)
			{
				//output to file
				ofstream outFile(fileName_output.c_str());
				outFile << output;
				outFile.close();
			}
				
			else
			{
				cout << output << endl;
			}
			cout << endl;		
		}
		else
		{
			cout << debugString << endl;
		}
	}
	else
	{
		displayHelp();
	}
	

	
}
