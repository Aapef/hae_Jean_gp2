#include "pch.h"
#include <iostream>
#include "floatArray.hpp"
#include "intArray.hpp"
#include "Util.hpp"
#include "Tree.hpp"
#include "List.hpp"

int main()
{
	
	FloatTree* tree = new FloatTree();

	Node<float> * leaf = new Node<float>(8.0f);

	leaf->insert(10.0f);
	leaf->insert(6.0f);
	leaf->insert(4.0f);

	//leaf->Remove(6.0f);

	int foniafeoniafe = leaf->getLength();

	bool z = leaf->Contains(10.0f);

	leaf->bfsprint();
	
	
	/*
	IntList* l = new IntList(8);
	l = l->Concat(7);

	l = l->Remove(7);

	int z = l->Length();
	*/

	int toto = 0;
	
	
	
	/*auto montableau = intArray(1024, "tablo");
	
	montableau.set(montableau.maxSize - 1, 1);
	montableau.RaNdOmIzE();
	montableau.swaptri();
	double T0 = TimeUtil::getTimestamp();
	
	montableau.searchpositiondich(75);

	double T1 = TimeUtil::getTimestamp();
	printf("temps : %f\n", (T1 - T0));


	
	auto montableau2 = intArray(1024, "tablo");
	
	montableau2.set(montableau2.maxSize - 1, 1);
	montableau2.RaNdOmIzE();
	montableau2.swaptri();
	double T02 = TimeUtil::getTimestamp();
	montableau.searchpositiondichrec(75);
	double T12 = TimeUtil::getTimestamp();
	printf("temps : %f\n", (T12 - T02));

	printf("rapport : %f\n", (T12 - T02)/(T1 - T0));

	//montableau2.set(761, 120);

	auto montableau3 = intArray(0, "tablo");

	/*int a = montableau2.searchpositiondich(75);
	int b = montableau2.searchpositiondichrec(75);*/


	/*auto montableautest = intArray(10, "tablo");
	montableautest.set(montableautest.maxSize - 1, 50);
	montableautest.RaNdOmIzE();
	//montableautest.set(3, 50);
	montableautest.swaptri();

	int b = montableautest.searchpositiondich(150);


	system("pause");*/
}