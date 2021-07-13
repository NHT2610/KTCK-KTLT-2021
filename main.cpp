#include "Header.h"

int main()
{
	linkedList petList;
	int yourSelect = -1;
	while (yourSelect != 8)
	{
		yourSelect = yourSelectFunction(menu());
		runMenu(yourSelect, petList);
	}
}