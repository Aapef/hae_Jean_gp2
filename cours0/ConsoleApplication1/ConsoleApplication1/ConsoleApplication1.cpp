// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include "MonHeader.hpp"
//#include <iostream>
#include <cstdlib>
#include <cstdio>


Vec3 incrX(Vec3 _in){
	_in.x++;
	return _in;
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

	printf("xval : %f\n", toto.x);
	//std::string labelcpp = "";  // en c++
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
