#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>
#include <fstream>
#include <windows.h>

#include "../cvm 23.h"

using namespace std;

// LA CONSTANTE DU PROGRAMME

const size_t REPONDANTS_MAX = 500; // nombre maximun de r�pondants du sondage


// LES STRUCTURES DE DONN�ES IMPOS�ES

struct Protection
{
	int  r2[REPONDANTS_MAX];
	char r3[REPONDANTS_MAX];
	char r4[REPONDANTS_MAX];
	char r5[REPONDANTS_MAX];
	char r6[REPONDANTS_MAX];
};

struct Infection
{
	bool r7;
	int	r8, r9, r10;
};

struct Repondant
{
	string ville;
	int age;
	int scolarite;
};


// L'UNIQUE VARIABLE GLOBALE

size_t nb_repondants;	// le nombre r�el de r�pondants: nb_repondants = lireLesDonn�esDuSondage(...)


// D�CALRATIONS DES FONCTIONS  -- �crire vos d�clarations ici ...

size_t lireLesDonn�esDuSondage(bool r1[], Protection* pro, Infection inf[], Repondant rep[]);



// D�FINITIONS DES FONCTIONS  --  �crire vos d�finitions ici ...




size_t lireLesDonn�esDuSondage(bool r1[], Protection* pro, Infection inf[], Repondant rep[])
{
	string name = "C21-LAB-3-Sondage.txt";											// exemple avec un path "C:/dossier/C21-LAB-3-Sondage.txt"
	fstream f(name, ios::in);

	if (f.fail()) // fichier ouvert ?
	{
		MessageBoxA(NULL, "Impossible d'ouvrir le fichier, Fin du programme", "Erreur", MB_OK | MB_ICONSTOP);
		exit(EXIT_FAILURE); // fin abrupte
	}

	char c;
	size_t r;
	for (r = 0; r < REPONDANTS_MAX; ++r)											// lire les r�ponses de chaque r�pondant
	{
		f >> c;	if (c == 'O') r1[r] = true; else r1[r] = false;						// r1
		f >> pro->r2[r] >> pro->r3[r] >> pro->r4[r] >> pro->r5[r] >> pro->r6[r];	// r2 � r6
		f >> c; if (c == 'O') inf[r].r7 = true; else inf[r].r7 = false;				// r7
		f >> inf[r].r8 >> inf[r].r9 >> inf[r].r10;									// r8 � r10
		f >> rep[r].ville >> rep[r].age >> rep[r].scolarite;						// ville, age, scolarit�
		if (f.fail()) { f.clear(); break; }
	}
	f.close();
	return r; // r = le nombre de r�pondants lus
}


int main()
{
	setcp(1252);

	// Pour recevoir les donn�es du sondage
	bool* r1 = new bool[REPONDANTS_MAX] {};					// pour la  r�ponse  1
	Protection* pro = new Protection {};					// pour les r�ponses 2-3-4-5-6
	Infection* inf = new Infection[REPONDANTS_MAX] {};		// pour les r�ponses 7-8-9-10
	Repondant* rep = new Repondant[REPONDANTS_MAX] {};		// pour les r�ponses ville, age, scolarit�

	// A - charger les donn�es du sondage
	nb_repondants = lireLesDonn�esDuSondage(r1,pro,inf,rep);


	// B - appeler vos fonctions statistiques et afficher ici leurs r�sultats
	// ...




	_getch();

	// C - Recycler les allocations dynamiques
	delete[] r1;
	delete pro;
	delete[] inf;
	delete[] rep;
}