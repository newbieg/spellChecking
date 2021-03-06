/*	HINT: the unordered list type requires a c++11 compile
 *	wrather than the normal version.
 * */

#ifndef SETMYDICTIONARYWORDS
#define SETMYDICTIONARYWORDS

#include <vector>
#include <unordered_set>
#include <string>

std::string dropNonChar(std::string input);
std::string strLower(std::string input);
std::string dumpChars(std::string &input, std::string dropList);

class setWords
{
	public:
	setWords();
	bool load(std::string fileName);
	bool save(std::string fileName);
	bool checkSpell(std::string word);
	void addWord(std::string word);
	void remove(std::string word);
	void toLower(); // converts all strings to lowerCase.
	void dropNonChars(); // drops all non-alphabetical and non-numeric characters
	void print();
	std::vector<std::string> wildCard(std::string start, std::string stop);
	
	
	

	private:

	std::unordered_set <std::string> uol; //short for un-ordered list

};

#endif
