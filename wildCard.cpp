#include <iostream>
#include <string>

using namespace std;

bool cmpWildCard(string wild, string input)
{
	bool answer = true;
	bool done = false;
	size_t next = wild.find("*");
	size_t old = 0;
	size_t lastFound = 0;
	if(wild != input)
	{
		string subwrd = wild.substr(old, next - old);
		lastFound = input.find(subwrd, lastFound);
		if(next != 0 && lastFound != 0)
		{
			answer = false;
			done = true;
		}
		lastFound = 0;
		while(answer && !done)
		{
			string subwrd = wild.substr(old, next - old);
			lastFound = input.find(subwrd, lastFound);

			if(string::npos != lastFound)
			{
				cout << subwrd << " is in " << input << endl;
				old = next + 1;
				next = wild.find("*", old);
				if(string::npos == next)
				{
					if(next < wild.length())
					{
// need to test the final bit of the code...
					}
					done = true;
				}
			}
			else
			{
				done = true;
				answer = false;
			}
			
		}
	}

	return answer;
}


int main()
{
	if(cmpWildCard("thr*x*y","thrtxasdfyy"))
	{
		cout << "Found!\n";
	}
	else
	{
		cout << "Not Good.\n";
	}
}

