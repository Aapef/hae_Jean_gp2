
#include "pch.h"
#include <iostream>
#include "intArray.hpp"
#include "floatArray.hpp"


void assert(bool boolou) {
	if (boolou == false)
	{
		throw new std::string("nope");
	}
}



int main()
{
	floatArray montableauf = floatArray(16, "tablo");

	montableauf.ensure(18);
	for (int i = 0; i < montableauf.maxSize; i++) 
	{
		montableauf.set(i, i);
	}
	montableauf.pushfirst(154.1f);
	montableauf.insert(141.0f, 5);
	montableauf.tri();

	int i = 0;
	/*
	//printf("%d", intArray::TEST)
	auto nametab0 = "tab0";
	auto nametab1 = "tab1";
	{
		intArray montableau = intArray(16, nametab0); // = variable locale
	}

	{
		intArray * tab1 = new intArray(16, nametab1); // = variable dynamique
	}
	intArray montableau = intArray(16, "tablo");
	for (int i = 0; i < montableau.maxSize; i++) {
		montableau.set(i, i);
	}
	montableau.set(15, 5);
	//montableau.set(16, 8);
	montableau.pushfirst(51);
	montableau.pushback(52);
	montableau.insert(40, 8);
	montableau.pushback(53);
	int i = montableau[8];

	intArray montableau3 = intArray(16, "tablo3");
	for (int i = 0; i < montableau3.maxSize - 3; i++) 
	{
		montableau3.set(i, montableau3.maxSize - i);
	}
	montableau3.RaNdOmIzE();
	montableau3.tri();
	montableau.tri();

	intArray montableau2 = intArray(0, "tablo2");
	montableau2.insert(51, 0);

	int zbeub = montableau.searchposition(50);
	int zbeub2 = montableau.searchpositiondich(50);
	*/
}


