#include <unordered_set>
#include <string>
#include <iostream>


using namespace std;


int main()
{
	unordered_set <string> bob;
	bob.emplace("hello");
	bob.emplace("helliop");

	if(bob.end() != bob.find("hell"))
	{
		cout << "word found...\n";
	}

}
