#include "CList.h"

int main()
{
	CList a{ 4, 5, 6 };

	a.PushBack(3);
	a.PushBack(9);
	a.PushBack(7);

	a.Erase(4);

	a.Display();

	return 0;
}