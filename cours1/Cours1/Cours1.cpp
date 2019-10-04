// Cours1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>

int StrChr(char * grange, char chat) {
	int pos = -1;
	int size = strlen(grange);
	for (int i = 0; i < size + 1; i++) {
		if (grange[i] == chat) {
			pos = i;
		}
	}
	return pos;
}

/*
int length = strlen(grange);
for(int i = 0; i<length; ++i )  // ++i ou i++ ne change rien dans le for (parenthèses implicite)
{
	if(grange[i] == chat) return i;
}
return -1;
*/

int StrChr2(char * grange, char chat) {
	int pos = -1;
	int size = strlen(grange);
	int ref = size;
	while (size != 0)
	{
		if (grange[ref + 1 - size] == chat)
		{
			pos = (ref + 1 - size);
		}
		size--;
	}
	return pos;
}



int StrChr2Cor(char * grange, char chat) {
	char* oldGrange = grange;
	while (*grange)
	{
		if (*grange == chat) {
			return (int)(grange - oldGrange);
		}
		grange++;
	}
	return -1;
}

int StrChr3(char * grange, char chat) 
{
	int counter = 0;
	while (grange[counter] != 0) {
		if (grange[counter] == chat) { return counter; }

		counter++;
	}
	return -1;
}

int StrChr4(char* grange, char chat) 
{
	static int i = 0;
	if (*grange == '0') { i = 0; return -1; }
	else if (*grange == chat) { int ii = i;  i = 0; return ii; }
	++i;
	StrChr4(++grange, chat);
}

void Memcpy(char * dest, char * src, int size) {
	for (int i = 0; i < size; i++) {
		*dest = *src;
		dest++;
		src++;
	}
}

void Memcpy2(char * dest, char * src, int size) {
	while (size != 0) {
		*dest = *src;
		dest++;
		src++;
		size--;
	}
}


int main()
{
	char licorne[32] = "licorne";
	char vomi[32] = "vomit";
	Memcpy2(licorne, vomi, strlen(licorne) + 1);
	printf("licorne %s\n", licorne);

	char chateau[32] = "chateau";
	char soldat = 'e';
	printf("position : %i\n", StrChr4(chateau, soldat));
}