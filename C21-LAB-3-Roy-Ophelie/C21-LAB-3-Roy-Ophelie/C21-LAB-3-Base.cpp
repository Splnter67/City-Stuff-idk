#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>
#include <fstream>
#include <windows.h>

#include "../C21-LAB-3-Roy-Ophelie/cvm 23.h"

using namespace std;

// LA CONSTANTE DU PROGRAMME

const size_t REPONDANTS_MAX = 500; // nombre maximun de répondants du sondage


// LES STRUCTURES DE DONNÉES IMPOSÉES

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

size_t nb_repondants;	// le nombre réel de répondants: nb_repondants = lireLesDonnéesDuSondage(...)


// DÉCALRATIONS DES FONCTIONS  -- écrire vos déclarations ici ...

size_t lireLesDonnéesDuSondage(bool r1[], Protection* pro, Infection inf[], Repondant rep[]);

int stat01(bool r1[]);
int stat02(Protection* pro);
double stat03(Protection* pro, Repondant rep[]);
double stat04(Protection* pro, Repondant rep[]);
double stat05(Protection* pro, Repondant rep[]);
double stat06(Infection* inf);
string stat07(Infection* inf);
int stat08(Protection* pro, Infection* inf);
double stat09(Protection* pro, Infection* inf, Repondant rep[]);
string stat10(Infection* inf, Repondant rep[]);



// DÉFINITIONS DES FONCTIONS  --  écrire vos définitions ici ...




size_t lireLesDonnéesDuSondage(bool r1[], Protection* pro, Infection inf[], Repondant rep[])
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
	for (r = 0; r < REPONDANTS_MAX; ++r)											// lire les réponses de chaque répondant
	{
		f >> c;	if (c == 'O') r1[r] = true; else r1[r] = false;						// r1
		f >> pro->r2[r] >> pro->r3[r] >> pro->r4[r] >> pro->r5[r] >> pro->r6[r];	// r2 à r6
		f >> c; if (c == 'O') inf[r].r7 = true; else inf[r].r7 = false;				// r7
		f >> inf[r].r8 >> inf[r].r9 >> inf[r].r10;									// r8 à r10
		f >> rep[r].ville >> rep[r].age >> rep[r].scolarite;						// ville, age, scolarité
		if (f.fail()) { f.clear(); break; }
	}
	f.close();
	return r; // r = le nombre de répondants lus
}

int stat01(bool r1[])
{
	int r, t;
	t = 0;
	for (r = 0; r <= nb_repondants; r++) {
		if (r1[r] == true) {
			t++;
		}
	}
	return t;
}

int stat02(Protection* pro)
{
	int r, a = 0;
	for (r = 0; r <= nb_repondants; r++) {
		if (pro->r3[r] == 'O') {
			a++;
		}
	}
	return a;
}

double stat03(Protection* pro, Repondant rep[])
{
	int r, n = 0;
	double mm = {};
	double m;
	for (r = 0; r <= nb_repondants; r++) {
		if (rep[r].age > 29 && rep[r].age < 40) {
			mm += pro->r2[r];
			n++;
		}
	}
	m = mm / n;
	return m;
}

double stat04(Protection* pro, Repondant rep[])
{
	int r;
	double m = 0, d = 0, mm = 0;
	for (r = 0; r <= nb_repondants; r++) {
		if (pro->r5[r] == 'O' || pro->r6[r] == 'O') {
			m++;
			d += rep[r].age;
		}
	}
	mm = d / m;
	return mm;
}

double stat05(Protection* pro, Repondant rep[])
{
	int r;
	double nv = 0, nm = 0, v = 0;
	for (r = 0; r <= nb_repondants; r++) {
		if (rep[r].ville == "Vaudreuil") {
			v++;
			if (pro->r2[r] > 1) {
				nv++;
			}
		}
	}
	nm = (nv / v) * 100;
	return nm;
}

double stat06(Infection* inf)
{
	int r;
	double lp = 0, l = 0;
	for (r = 0; r <= nb_repondants; r++) {
		if (inf[r].r7 == true) {
			l++;
		}
	}
	lp = (l / nb_repondants) * 100;
	return lp;
}

string stat07(Infection* inf)
{
	int r, n = 0, sv = 0, p = 0, ej = 0, af = 0;
	string sel;
	for (r = 0; r <= nb_repondants; r++) {
		switch (inf[r].r8) {
		case 1:
			n++;
			break;
		case 2:
			sv++;
			break;
		case 3:
			p++;
			break;
		case 4:
			ej++;
			break;
		case 5:
			af++;
			break;
		default:
			break;
		}
	}
	if (n >= sv && n >= p && n >= ej && n >= af) {
		sel = "Pas de désinfectant";
	}
	else if (sv >= n && sv >= p && sv >= ej && sv >= af) {
		sel = "Savon à vaisselle";
	}
	else if (p >= n && p >= sv && p >= ej && p >= af) {
		sel = "Purell";
	}
	else if (ej >= n && ej >= sv && ej >= p && ej >= af) {
		sel = "Eau de javel";
	}
	else if (af >= n && af >= sv && af >= p && af >= ej) {
		sel = "Alcool a friction";
	}
	else
		"NA";

	return sel;
}

int stat08(Protection* pro, Infection* inf)
{
	int r, pnt = 0;
	for (r = 0; r <= nb_repondants; r++) {
		if (inf[r].r7 == 'N' && inf[r].r10 == 0 && pro->r4[r] == 'O') {
			pnt++;
		}
	}
	return pnt;
}

double stat09(Protection* pro, Infection* inf, Repondant rep[])
{
	int r, d = 0;
	double full = 0, m = 0;
	for (r = 0; r <= nb_repondants; r++) {
		if ((pro->r2[r] == 0 || inf[r].r8 == 1) && inf[r].r9 == 1 && rep[r].ville == "Montréal") {
			d += rep[r].scolarite;
			m++;
		}
	}
	full = d / m;
	if (d == 0 && m == 0) {
		full = 0;
	}
	return full;
}

string stat10(Infection* inf, Repondant rep[])
{
	int r, l, v[9]{0,0,0,0,0,0,0,0,0}, w, ww;
	string ville[9]{"Longueuil", "Montréal", "Lachine", "Vaudreuil", "Brossard", "Boucherville", "Terrebonne", "Anjou", "Laval"};
	for (r = 0; r <= nb_repondants; r++) {
		for (l = 0; l < 9; l++) {
			if (rep[r].ville == ville[l]) {
				v[l]++;
			}
		}
	}
	w = 0;
	for (r = 0; r < 9; r++) {
		ww = 0;
		for (l = 0; l < 9; l++) {
			if (v[r] >= v[l]) {
				ww++;
				if (ww >= 9) {
					w = r;
				}
			}
			else {
				break;
			}
		}
	}
	return ville[w];
}







int main()
{
	setcp(1252);

	// Pour recevoir les données du sondage
	bool* r1 = new bool[REPONDANTS_MAX] {};					// pour la  réponse  1
	Protection* pro = new Protection {};					// pour les réponses 2-3-4-5-6
	Infection* inf = new Infection[REPONDANTS_MAX] {};		// pour les réponses 7-8-9-10
	Repondant* rep = new Repondant[REPONDANTS_MAX] {};		// pour les réponses ville, age, scolarité

	// A - charger les données du sondage
	nb_repondants = lireLesDonnéesDuSondage(r1,pro,inf,rep);


	// B - appeler vos fonctions statistiques et afficher ici leurs résultats
	// ...
	cout << fixed << setprecision(1) << "1. Combien de personnes toussent souvent ?  " << stat01(r1) << endl
		<< "2. Combien de personnes veulent un masque dans leur auto ?  " << stat02(pro) << endl
		<< "3. Combiens de masques, en moyenne, ont les gens qui sont dans la trentaine ?  " << stat03(pro, rep) << endl
		<< "4. Quel est l'âge moyen des gens qui se serviraient d'un masque pour décorer ou pour dormir ?  " << stat04(pro, rep) << endl
		<< "5. Quel pourcentage des gens de Vaudreuil possèdent plus d'un masque ?  " << stat05(pro, rep) << endl
		<< "6. Quel pourcentage de la population utilise un désinfectant ?  " << stat06(inf) << endl
		<< "7. Quel est le type de désinfectant le plus répandu ?  " << stat07(inf) << endl
		<< "8. Combien de gens non testés et n'utilisant pas de désinfectant ont déja emprunté un masque ?  " << stat08(pro, inf) << endl
		<< "9. Combien d'années de scolarité, en moyenne, ont les gens infectés de Montréal sans masque ou sans désinfectant ?  " << stat09(pro, inf, rep) << endl
		<< "10. Quelle est la ville ayant fait subir le plus grand nombre de tests ?  " << stat10(inf, rep);
	



	_getch();

	// C - Recycler les allocations dynamiques
	delete[] r1;
	delete pro;
	delete[] inf;
	delete[] rep;
}
