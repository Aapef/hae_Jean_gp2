#pragma once
#include <cstdio>
#include <cstdlib>
#include <string>

class intArray 
{

public: 
	std::string name;
	int * array;
	int maxSize = 0;
	int curSize = 0;

	intArray(int size, const char * name = nullptr)
	{
		this->name = name;
		printf("construction %s\n", this ->name.c_str());

		//C old school
		// array = (int *)malloc(size*sizeof(int)); memset(array,0,size * sizeof(int));

		//C new school
		//array = (int * )calloc(size, sizeof(int)); (calloc mets les 0)

		//C++
		array =  new int[size];
		for(int i = 0; i < size; i++) array[i] = 0;

		maxSize = size;
	}

	~intArray() 
	{
		printf("destruction %s\n", name.c_str());
	}
};
