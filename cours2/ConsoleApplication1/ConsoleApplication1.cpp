
#include "pch.h"
#include <iostream>
#include "intArray.hpp"

int main()
{
	//printf("%d", intArray::TEST)
	auto nametab0 = "tab0";
	auto nametab1 = "tab1";
	{
		intArray montableau = intArray(16, nametab0); // = variable locale
	}

	{
		intArray * tab1 = new intArray(16, nametab1); // = variable dynamique
	}
}
