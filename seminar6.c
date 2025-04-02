#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// hash table= tabela de dispersie
// cod hash = algoritm care primeste un input, iar output ul este standardizat
// parolele sunt salvate sub forma de hash 
// particularitati: nu poate fi inversat(nu pot obtine input ul initial)
// exista prob de coliziune(2 output uri sunt la fel pt elem diferite)
// mecanism liniar probing sau quadratic probing



struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

// creare structura pentru un nod dintr-o lista simplu inlantuita
struct Nod {
	Masina info;
	struct Nod* urm;
};
typedef struct Nod Nod;
// creare structura pentru tabela de dispersie
// aceasta este un vector de liste
struct HashTable {
	Nod** adrese;
	int dim;
};
typedef struct HashTable HashTable;

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

void afisareListaMasini(Nod* cap) {

	while (cap) // daca verific cu cap -> urm nu se duce pana la final, trb sa il mai afisez pe ultimul dupa
	{
		afisareMasina(cap->info);
		cap = cap->urm;
	}
}

void adaugaMasinaInLista(Nod* cap, Masina masinaNoua) // Nod ** cap e pointerul care retine adresa pointer-ului in care am adresa primului nod
{
	if (cap)
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = masinaNoua;
		nou->urm = NULL;
		while (cap->urm != NULL)
			cap = cap->urm;
		cap->urm = nou;
	}
}


HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	ht.dim = dimensiune;
	ht.adrese = (Nod**)malloc(sizeof(Nod*) * dimensiune); // am alocat spatiu pentru vectorul de noduri, deci o sa am dimensiune noduri
	for (int i = 0; i < dimensiune; i++)
	{
		ht.adrese[i] = NULL;
	}

	return ht;
}

int calculeazaHash(char* numeSofer, int dimensiune) {
	if (dimensiune) {
		int valoare = 0;
		for (int i = 0; i < strlen(numeSofer); i++)
			valoare = valoare + numeSofer[i];
		return valoare % dimensiune;
	}
	else return 0;
}

void inserareMasinaInTabela(HashTable hash, Masina masina) {
	int pozitie = calculeazaHash(masina.numeSofer, hash.dim);
	if (hash.adrese[pozitie] == NULL) // nu avem coliziune
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = masina;
		nou->urm = NULL;
		hash.adrese[pozitie] = nou;
	}
	else // avem coliziune
	{
		adaugaMasinaInLista(hash.adrese[pozitie], masina);
	}
}

HashTable citireMasiniDinFisier(const char* numeFisier, int dim) {
	FILE* f = fopen(numeFisier, "r");
	HashTable ht = initializareHashTable(dim);
	while (!feof(f))
	{
		inserareMasinaInTabela(ht, citireMasinaDinFisier(f));

	}
	fclose(f);
	return ht;
}

void afisareTabelaDeMasini(HashTable ht) {
	for (int i = 0; i < ht.dim; i++)
	{
		printf("Cluster ul %d\n", i + 1);
		afisareListaMasini(ht.adrese[i]);
		printf("\n\n");
	}
}

void dezalocareTabelaDeMasini(HashTable* ht) {
	// sunt dezalocate toate masinile din tabela de dispersie
}

float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {
	// calculeaza pretul mediu al masinilor din fiecare cluster.
	// trebuie sa returnam un vector cu valorile medii per cluster.
	// lungimea vectorului este data de numarul de clustere care contin masini
	return NULL;
}

Masina getMasinaDupaCheie(HashTable ht, const char* nume) {
	Masina m;
	m.id = -1;
	m.nrUsi = 0;
	m.pret = 0;
	m.model = NULL;
	m.numeSofer = NULL;
	m.serie = 0;
	int hash = calculeazaHash(nume, ht.dim);
	if (ht.adrese[hash])
	{
		Nod* p = ht.adrese[hash];
		while (p && strcmp(nume, p->info.numeSofer) != 0)
		{
			p = p->urm;
		}
		if (p)
		{
			m = p->info;
			m.numeSofer = (char*)malloc(strlen(p->info.numeSofer) + 1);
			strcpy_s(m.numeSofer, strlen(p->info.numeSofer) + 1, p->info.numeSofer);
			m.model = (char*)malloc(strlen(p->info.model) + 1);
			strcpy_s(m.model, strlen(p->info.model) + 1, p->info.model);

		}

	}
	return m;
}

int main() {

	HashTable ht = citireMasiniDinFisier("masini.txt", 5);

	Masina m = getMasinaDupaCheie(ht, "Gigel3");
	printf("Cautam masina lui Gigel3: \n");
	if (m.id != -1)
	{
		afisareMasina(m);
		free(m.model);
		free(m.numeSofer);

	}
	else
	{
		printf("Nu a fost gasita\n");
	}
	afisareTabelaDeMasini(ht);

	return 0;
}