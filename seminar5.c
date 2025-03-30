// examen grila probabil - grila multipla plus secvente de cod de completat, intrebari rasp unic, multiplu, intrebari drag and drop, de facut perechi

// test peste 2 saptamani - functii, vectori, fisiere, liste simple inlantuite, dublu inlantuite, hashtable
// de citit din fisier sau de la tastatura, inserare intr o structura, de procesat ceva(media), o afisare, o dezalocare
// se poate si combinatii intre structuri, de luat din vector si pus in lista sau hashtable
// fara teste unitare

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// lista simplu inlantuita in care memoram si adresa nodului precedent
// primul contine adresa null
//
// trebuie sa folositi fisierul masini.txt
// sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};

typedef struct StructuraMasina Masina;

struct Nod {
	Masina info;
	struct Nod* urmator;
	struct Nod* precedent;

};

typedef struct Nod Nod;

struct Lista {
	Nod* prim;
	Nod* ultim;
};

typedef struct Lista Lista;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasiniInceput(Lista list) {
	// afiseaza toate elemente de tip masina din lista dublu inlantuita
	// prin apelarea functiei afisareMasina()
	Nod* p = list.prim;
	while (p)
	{
		afisareMasina(p->info);
		p = p->urmator;
	}

}

void adaugaMasinaInLista(Lista* list, Masina masinaNoua) {
	// adauga la final in lista primita o noua masina pe care o primim ca parametru
	// la orice adaugare in lista, ne creem nodul
	Nod* p = (Nod*)malloc(sizeof(Nod));
	p->info = masinaNoua;
	p->precedent = list->ultim;
	p->urmator = NULL;
	if (list->ultim != NULL)
	{
		list->ultim->urmator = p;
	}
	else
	{
		list->prim = p;
	}
	list->ultim = p;
}


void adaugaLaInceputInLista(Lista* list, Masina masinaNoua) {
	Nod* p = (Nod*)malloc(sizeof(Nod)); //creez nod nou si initializez toate componentele
	p->urmator = list->prim;
	p->precedent = NULL;
	p->info = masinaNoua;
	if (list->prim)
	{
		list->prim->precedent = p;
	}
	else
	{
		list->ultim = p;
	}
	list->prim = p;

}

Lista citireLDMasiniDinFisier(const char* numeFisier) {
	// functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	// prin apelul repetat al functiei citireMasinaDinFisier()
	// ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	Lista list;
	list.prim = NULL;
	list.ultim = NULL;
	while (!feof(f))
	{
		adaugaLaInceputInLista(&list, citireMasinaDinFisier(f));
	}
	fclose(f);

	return list;
}
void afisareListaMasiniSF(Lista list)
{
	Nod* p = list.ultim;
	while (p)
	{
		afisareMasina(p->info);
		p = p->precedent;
	}

}

void dezalocareLDMasini(Lista* list) {
	Nod* p = list->prim;
	while (p->urmator)
	{
		free(p->info.model);
		free(p->info.numeSofer);
		p = p->urmator;
		free(p->precedent);

	}
	free(p->info.model);
	free(p->info.numeSofer);
	free(p);
	list->prim = NULL;
	list->ultim = NULL;
}

float calculeazaPretMediu(Lista list) {
	Nod* p = list.prim;
	float pretMediu = 0;
	int contor = 0;
	while (p)
	{
		pretMediu = pretMediu + p->info.pret;
		p = p->urmator;
		contor++;
	}
	if (contor)
		return pretMediu / contor;
	else
		return 0;
}

void stergeMasinaDupaID(/*lista masini*/ int id) {
	// sterge masina cu id-ul primit.
	// tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

char* getNumeSoferMasinaScumpa(/*lista dublu inlantuita*/) {
	// cauta masina cea mai scumpa si 
	// returneaza numele soferului acestei maasini.
	return NULL;
}

int main() {

	Lista list;
	list = citireLDMasiniDinFisier("masini.txt");
	afisareListaMasiniInceput(list);
	afisareListaMasiniSF(list);
	printf("pretul mediu este: %3.2f", calculeazaPretMediu(list));
	dezalocareLDMasini(&list);
	return 0;
}