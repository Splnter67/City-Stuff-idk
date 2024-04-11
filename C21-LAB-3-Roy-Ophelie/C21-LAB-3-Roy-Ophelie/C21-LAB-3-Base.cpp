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
		if (pro->r2[r] == 0 && inf[r].r8 == 1 && inf[r].r9 == 1) {
			d += rep[r].scolarite;
			m++;
		}
	}
	full = d / m;
	return full;
}

string stat10(Infection* inf, Repondant rep[])
{
	int r, lg = 0, mtl = 0, lc = 0, vd = 0, bs = 0, bc = 0, tb = 0, aj = 0, lv = 0;
	for (r = 0; r <= nb_repondants; r++) {
		if (rep[r].ville == "Longueuil") {
			lg += inf[r].r10;
		}
		else if (rep[r].ville == "Montréal") {
			mtl += inf[r].r10;
		}
		else if (rep[r].ville == "Lachine") {
			lc += inf[r].r10;
		}
		else if (rep[r].ville == "Vaudreuil") {
			vd += inf[r].r10;
		}
		else if (rep[r].ville == "Brossard") {
			bs += inf[r].r10;
		}
		else if (rep[r].ville == "Boucherville") {
			bc += inf[r].r10;
		}
		else if (rep[r].ville == "Terrebonne") {
			tb += inf[r].r10;
		}
		else if (rep[r].ville == "Anjou") {
			aj += inf[r].r10;
		}
		else if (rep[r].ville == "Laval") {
			lv += inf[r].r10;
		}
	}
	if (lg >= mtl && lg >= lc && lg >= vd && lg >= bs && lg >= bc && lg >= tb && lg >= aj && lg >= lv) {

	}
	else if (mtl >= lg && mtl >= lc && mtl >= vd && mtl >= bs && mtl >= bc && mtl >= tb && mtl >= aj && mtl >= lv) {

	}
	else if (lc >= lg && lc >= mtl && lc >= vd && lc >= bs && lc >= bc && lc >= tb && lc >= aj && lc >= lv) {

	}
	else if (vd >= lg && vd >= mtl && vd >= lc && vd >= bs && vd >= bc && vd >= tb && vd >= aj && vd >= lv) {

	}
	else if (bs >= lg && bs >= mtl && bs >= lc && bs >= vd && bs >= bc && bs >= tb && bs >= aj && bs >= lv) {

	}
	else if (bc >= lg && bc >= mtl && bc >= lc && bc >= vd && bc >= bs && bc >= tb && bc >= aj && bc >= lv) {

	}
	else if (tb >= lg && tb >= mtl && tb >= lc && tb >= vd && tb >= bs && tb >= bc && tb >= aj && tb >= lv) {

	}
	else if (aj >= lg && aj >= mtl && aj >= lc && aj >= vd && aj >= bs && aj >= bc && aj >= tb && aj >= lv) {

	}
	else if (lv >= lg && lv >= mtl && lv >= lc && lv >= vd && lv >= bs && lv >= bc && lv >= tb && lv >= aj) {

	}

	return "o";
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
	cout << fixed << setprecision(1) << stat01(r1) << endl << stat02(pro) << endl << stat03(pro, rep) << endl << stat04(pro, rep) << endl << stat05(pro, rep) << endl
		<< stat06(inf) << endl << stat07(inf) << endl << stat08(pro, inf) << endl << stat09(pro, inf, rep);
	



	_getch();

	// C - Recycler les allocations dynamiques
	delete[] r1;
	delete pro;
	delete[] inf;
	delete[] rep;
}
