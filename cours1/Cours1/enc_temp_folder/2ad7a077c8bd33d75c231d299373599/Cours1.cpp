// Cours1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>

static void TestRec();

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


int Max(int a, int b) {
	return(a < b ? a : b);
}

int Min(int a, int b) {
	return(a > b ? a : b);
}

int StrCmp(char* meule, char* aiguille)
{
int lenMeule = strlen(meule);
int lenAiguille = strlen(aiguille);

int maxLen = Max(lenMeule, lenAiguille);
int minLen = Min(lenMeule, lenAiguille);

for (int i = 0; i < minLen; i++)
{

	if (meule[i] < aiguille[i]) return -1;
	else if (meule[i] > aiguille[i])
		return 1;
}
if (minLen == maxLen) return 0;
if (maxLen == lenMeule) return 1;

return -1;
}




char* strstr3(char* meule, char* aiguille) 
{
	int length = strlen(meule);
	int length2 = strlen(aiguille);

	for (int i = 0; i < length; i++) {
		bool found = true;
		for (int j = 0; j < length2; j++) {
			if (meule[j] != aiguille[j]) {
				found = false;
				break;
			}
		}
		if (found) {
			return meule;
		}
			meule++;
	}
	return nullptr;
}





int main()
{
	/*char licorne[32] = "licorne";
	char vomi[32] = "vomit";
	Memcpy2(licorne, vomi, strlen(licorne) + 1);
	printf("licorne %s\n", licorne);

	char chateau[32] = "chateau";
	char soldat = 'e';
	printf("position : %i\n", StrChr4(chateau, soldat));

	char texte[32] = "lorem ipsum dolor sit amet";
	char token[32] = "dolor";

	char * tokenInText = strstr3(texte, token);

	int pos = (int)(tokenInText - texte);
	printf("le token est en position %d\n", pos);
	printf("length : %i\n", StrLen(texte));*/

	TestRec();
}



int StrLen(char* src) {
	if (*src == 0) return 0;
	else return 1 + StrLen(src + 1);
}


int addrec(int a, int b) {
	if (b == 0) return a;
	else {  return addrec(a + 1, b - 1);  }
}

int addrec2(int a, int b) {
	if (b == 0) return 1;
	else {  return 1 + addrec2(a, b - 1); }
}



int subrec(int a, int b) {
	printf("a = %i  b = %i\n", a, b);
	if (b == 0) return a;
	else if(b>0)return subrec(a, b - 1) - 1;
	else if (b < 0)return subrec(a, b + 1) + 1;
}

int byrec(int a, int b) {
	if (b == 0) return 0;	
	else if (b > 0) 
		return byrec(a, b - 1) + a; 
	else if (b < 0) 
		return byrec(a, b + 1) - a; 
}

int onrec(int a, int b)
{
	if (a == 0) return 0;
	if (b < 0 && a < 0) return -onrec(a, b);
	if (a < 0) return -onrec(-a, b);
	if (b < 0) return -onrec(a, -b);
	if (a < b)  return 0;
	return 1 + onrec(a - b, b);
}

int reste(int a, int b) 
{
	return a - b*onrec(a, b);
}

int StrCpy(const char* src, char* dest) 
{
	*dest = *src;
	if (*src == 0) return 0;
	else StrCpy(src+1, dest+1);
}


int ZeroMemory(char* dest, int size)
{
	if (size == 0) return 0;
	else { *dest = 0;  ZeroMemory(dest + 1, size - 1); }
}

int MemCpy(char* dest, const char* src, int size) 
{
	if (size == 0) return 0;
	*dest = *src;
	MemCpy(dest + 1, src + 1, size - 1);
}

int StrCmpRec(const char* a, const char* b) 
{
	if (*a != *b) { if (*a < *b) return -1; else return 1; }
	if (*a == 0 || *b == 0) return 0;
	return StrCmpRec(a + 1, b + 1);
}

int StrcatRec(char * str0, char * str1) 
{
	if (*str1 == 0) return 0;
	if (*str0 == 0) { MemCpy(str0, str1, StrLen(str1)); return 0; }
	return StrcatRec(str0 + 1, str1);
}

char * StrChrRec(char * str, char tok) 
{
	if (*str == 0) return nullptr;
	if (*str == tok) return str;
	return StrChrRec(str + 1, tok);
}

char * StrStrRec(char * str, char * look) 
{
	if (*look == 0) return look;
	else if (*str == 0 ) return nullptr;
	if (*str == *look) 
	{ 
		char * ptr = StrStrRec(str + 1, look + 1);
		if (ptr != nullptr) return str;
	}
	return StrStrRec(str + 1, look);
}

void TestRec() 
{
	int foo = addrec(5, 6);
	int foo2 = addrec2(6, 9);
	int foo3 = byrec(5, 9);
	int foo4 = byrec(5, -9);
	int foo32 = byrec(-5, 9);
	int foo42 = byrec(-5, -9);
	int foo5 = byrec(0, -9);
	int foo52 = byrec(-6, 0);
	int foo10 = onrec(6, 3);
	int foo11 = onrec(-6, 3);
	int foo12 = reste(15, 4);
	char destination [32] = "azertyuiop";
	char src [10] = "qsdfg";
	int szBuf = 32;
	char * buffer = (char*)malloc(szBuf + 1);
	buffer[32] = 'x';
	ZeroMemory(buffer, szBuf);
	StrcatRec(destination, src);
	const char * char1 = "bulle";
	const char * char2 = "boule";
	int z = StrCmpRec(char1, char2);
	z;
	char * bitou = StrStrRec(destination,src);
	*bitou;
	
	system("pause");
}