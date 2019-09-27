// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include "MonHeader.hpp"
//#include <iostream>
#include <cstdlib>

#include <chrono>
#include <cstdio>


Vec3 incrX(Vec3 _in){
	_in.x++;
	return _in;
}

Vec3 StackOverflow(Vec3 _in) {
	Vec3 temp = _in;
	temp.y++;
	return StackOverflow(temp);
}




int Strlen(const char* source) {
	int length = 0;
	while (*source != 0) {
		length++;
		source++;
	}
	return length;
}

int Strcpy(char * dest, const char * src) {
	while (*src != 0) {
		*dest = *src;
		dest++;
		src++;
	}
	return 0;
}

int main()
{
    //std::cout << "Hello World!\n"; // = debug.log

	int foo = 0;
	const char* label = "sapin";  //en C
	const char label2[6] = { 's', 'a', 'p', 'i', 'n', 0 }; //le 0 est obligatoire sinon l'ordinateur affichera de la mémoire
	printf("Hello world this is a test : %d label : %s\n", foo, label);

	float v = 0.5f;
	double ff = 0.5;

	Vec3 toto = { 1,2,3 };

	incrX(toto);

	printf("xval : %d\n", toto.x);

	//int * v = (int*)malloc(4);

	/*Vec3 Bob = { 1,2,3 };
	Bob = StackOverflow(Bob);*/
	//std::string labelcpp = "";  // en c++

	Vec3 vecTab[3];
	vecTab[0]= { 1,2,3 };
	vecTab[1]= { 4,5,6 };
	vecTab[2]= { 7,8,9 };
	printf("v0x %d\n", vecTab[0].x);

	Vec3 * t0 = 0;
	Vec3 * t1 = nullptr;
	Vec3 * t2 = &vecTab[1]; // & = adresse de la valeur


	//*(t2.y) = 555;
	(*t2).y = 777;
	t2->y = 888;
	int _i = 0;

	Vec3* iter = &vecTab[0];
	int i = 0;
	for (i = 0; i < 3; ++i) {
		printf("val vec x : %d\n", iter->x);
		iter++;
		//iter = iter + 1;
		//iter = (&vecTab[0] + i);
	}

	const char * ptr = &label2[0];
	ptr++;
	printf("%c\n", *ptr);

	Vec3 * t3 = t2 + 1; // donne l'adresse de l'élément suivant de vecTab
/*
	auto start = std::chrono::system_clock::now();

	int * bigBlock = (int*)malloc(1024 * 1024 * 1024);

	for (int k = 0; k < 64 * 1024 * 1024; k++) {
		bigBlock[k] = 0xdeadbeef;
	}

	printf("beef ? : %x\n", bigBlock[1024 * 1024]);
	auto end = std::chrono::system_clock::now();
	auto nano = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	printf("time : %d\n", nano);*/

	Vec3 tableau[16];
	Vec3 *tableau0 = (Vec3*)malloc(sizeof(Vec3) * 16); //en C pur
	memset(tableau, 0, sizeof(Vec3) * 16);
	Vec3 *tableau1 = (Vec3*)calloc(sizeof(Vec3), 16); //en C pur

	Vec3 *tableau2 = new Vec3[16]; //en c++
	Vec3 * unseulvec = new Vec3();
	Vec3 unsseulvecaussimaissurletas = Vec3();



	const char * source = "mon lapin est dodu";
	char * dest = (char*)calloc(1024, sizeof(char));
	Strcpy(dest, source);

	printf("dest len:%d val: %s  \n", Strlen(source), dest);

	int z = 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
