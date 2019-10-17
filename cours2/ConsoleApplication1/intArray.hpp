#pragma once
#include <cstdio>
#include <cstdlib>
#include <string>
#include <Windows.h>


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
		printf("construction %s\n", this->name.c_str());

		//C old school
		// array = (int *)malloc(size*sizeof(int)); memset(array,0,size * sizeof(int));

		//C new school
		//array = (int * )calloc(size, sizeof(int)); (calloc mets les 0)

		//C++
		array = new int[size];
		for (int i = 0; i < size; i++) array[i] = 0;

		maxSize = size;
	}

	~intArray();

	void ensure(int size);

	void set(int pos, int elem);

	void pushfirst(int elem);

	void pushback(int elem);


	void insert(int elem, int pos);

	int operator[] (int i) 
	{
		ensure(i);
		return array[i];
	}

	void remove(int pos) 
	{
		for (int i = 0; i < curSize - 1; i++) 
		{
			if (i < pos) array[i] = array[i];
			else array[i] = array[i + 1];
		}
		curSize = curSize - 1;
	}
	
	void RaNdOmIzE() 
	{
		std::srand(GetTickCount());
		for (int i = 0; i < curSize; i++) 
		{	
			array[i] = std::rand()%100;
		}
	}

	void tri() 
	{
		int * array2 = new int[curSize];
		int size = curSize;
		for (int i = 0; i < size; i++) 
		{
			int z = array[0];
			int jref = 0;
			for (int j = 0; j < curSize; j++)
			{
				if (z > array[j]) 
				{
					z = array[j];
					jref = j;
				}
			}
			remove(jref);
			array2[i] = z;
		}
		delete(array);
		array = array2;
		curSize = size;
	}
 
	int searchposition(int elem) 
	{
		for (int i = 0; i < curSize; i++) 
		{
			if (elem <= array[i])
				return i;
			else if (i == curSize - 1) return -1;
		}
	}

	int searchpositiondich(int elem) 
	{
		tri();
		int min = 0;
		int max = curSize;
		int i = (int)(min + ((max - min) / 2)); 

		while(array[i] != elem)
		{
			if (elem > array[i] && min != i)
				min = i;
			else 
				max = i;

			if(max != min) 
				i = (int)(min + ((max - min) / 2));
			else 
				break;
		}
		if (array[i] != elem) return -1;
		else return i;
	}
};



/*

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

	void ensure(int size)
	{
		if (size <= maxSize) {
			return;
		}
		else {
			int * array2 = new int[size];
			for (int i = 0; i < size; i++)
			{
				if (i < maxSize) array2[i] = array[i];
				else array2[i] = 0;
			}
			maxSize = size;
			delete(array);
			array = array2;
		}
	}

	void set(int pos, int elem)
	{
		ensure(pos + 1);
		array[pos] = elem;
		curSize = pos + 1;
	}

	void pushfirst(int elem)
	{
		if (curSize >= maxSize) ensure(maxSize + 1);
		int * array2 = new int[maxSize];
		for (int i = 0; i < maxSize; i++)
		{
			array2[i] = array[i];
		}

		for (int i = 0; i < maxSize; i++)
		{
			if (i > 0) { array[i] = array2[i - 1]; }
		}
		array[0] = elem;
		curSize = curSize + 1;
	}

	void pushback(int elem)
	{
		if (curSize >= maxSize) ensure(maxSize + 1);
		if (curSize < maxSize) array[curSize] = elem;
		curSize = curSize + 1;
	}


	void insert(int elem, int pos)
	{
		if(curSize >= maxSize) ensure(maxSize + 1);
		int * array2 = new int[maxSize];
		for (int i = 0; i < maxSize; i++)
		{
			array2[i] = array[i];
		}

		for (int i = pos; i < maxSize; i++)
		{
			if (i > pos) { array[i] = array2[i - 1]; }
		}
		array[pos] = elem;
		if (curSize < maxSize) curSize = curSize + 1;
	}

*/
