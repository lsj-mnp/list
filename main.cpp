#include "CList.h"
#include <list>

int main()
{
	using std::list;

	list<int> b{ 2, 3, 4, 7 };

	for (auto it : b)
	{
		std::cout << it;
	}

	for (auto it = b.begin(); it != b.end(); ++it)
	{
		std::cout << *it;
	}

	CList a{3, 5, 6, 7};

	for (auto it : a)
	{
		std::cout << std::endl << it;
	}

	return 0;
}