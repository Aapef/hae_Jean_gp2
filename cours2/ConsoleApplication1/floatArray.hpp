#pragma once
#include <cstdio>
#include <cstdlib>
#include <string>
#include <Windows.h>

class floatArray 
{

public: float * array;
		int maxSize;
		int curSize;
		std::string name;

		float operator[] (int i)
		{
			ensure(i);
			return array[i];
		}

		floatArray(int size, std::string aname) 
		{
			name = aname;
			array = new float[size];
			curSize = 0;
			for (int i = 0; i < size; i++) array[i] = 0.0f;
			maxSize = size;
		}

		void ensure(int size) 
		{
			if (maxSize < size) 
			{
				float * array2 = new float[size];
				for (int i = 0; i < size; i++) 
				{
					if(i < curSize) array2[i] = array[i];
					else array2[i] = 0;
				}
				delete(array);
				array = array2;
				maxSize = size;
			}
		}

		void set(int pos, float elem) 
		{
			ensure(pos + 1);
			array[pos] = elem;
			curSize = pos + 1;
		}

		void pushback(float elem) 
		{
			if(curSize >= maxSize)ensure(maxSize + 1);
			array[curSize] = elem;
			curSize = curSize + 1;		
		}

		void pushfirst(float elem)
		{
			if (curSize >= maxSize) ensure(maxSize + 1);
			float * array2 = new float[maxSize];
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

		void insert(float elem, int pos)
		{
			if (pos >= maxSize) ensure(pos + 1);
			else if (curSize >= maxSize) ensure(maxSize + 1);
			float * array2 = new float[maxSize];
			for (int i = pos; i < maxSize; i++)
			{
				array2[i] = array[i];
			}

			for (int i = pos; i < maxSize; i++)
			{
				if (i > 0) { array[i] = array2[i - 1]; }
			}
			array[pos] = elem;			
			if (pos > curSize) curSize = pos + 1;
			else curSize = curSize + 1;
		}

		void remove(int pos) 
		{
			float * array2 = new float[maxSize - 1];
			for (int i = 0; i < maxSize; i++) 
			{
				if (i < pos) array2[i] = array[i];
				else array2[i] = array[i + 1];
			}
			maxSize = maxSize - 1;
			delete(array);
			array = array2;
			curSize = curSize - 1;
		}

		void tri() 
		{
			float * array2 = new float[maxSize];
			int size = curSize;
			for (int i = 0; i < maxSize; i++) 
			{
				array2[i] = 0;
			}
			for (int i = 0; i < size; i++) 
			{
				float elem = array[0];
				int pos = 0;
				for (int j = 0; j < curSize; j++)
				{
					if (elem > array[j]) { elem = array[j]; pos = j; }
				}
				array2[i] = elem;
				remove(pos);
			}
			delete(array);
			array = array2;
			curSize = size;
		}

};
