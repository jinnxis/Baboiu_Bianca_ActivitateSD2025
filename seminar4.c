#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;
typedef struct Nod Nod;

struct Nod {
	Masina info;
	Nod* urm;
};

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
	while (cap) {
		afisareMasina(cap->info);
		cap = cap->urm;
	}

}

void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;

	nou->urm = NULL;
	if ((*cap) == NULL)
	{
		*cap = nou;
	}
	else
	{
		Nod* p = *cap;
		while (p->urm) //verific daca am unde sa ma asez
		{
			p = p->urm;
		}
		p->urm = nou;

	}
}

void adaugaLaInceputInLista(Nod** cap, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->urm = *cap;
	*cap = nou;


}

Nod* citireListaMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* lista = NULL; //trb initializat obligatoriu pentru ca altfel are o val implicita in afara de null, dar noi verificam daca e null la inceput
	while (!feof(f))
	{
		adaugaMasinaInLista(&lista, citireMasinaDinFisier(f));
	}
	fclose(f); //in C nu avem metode, doar functii
	return lista;

}

void dezalocareListaMasini(Nod** cap) {
	while ((*cap != NULL))
	{
		Nod* aux = (*cap);
		*cap = (*cap)->urm;
		free(aux->info.model);
		free(aux->info.numeSofer);
		free(aux);
	}

}

float calculeazaPretMediu(Nod* lista) {
	if (!lista)
		return 0;
	float suma = 0;
	int numar = 0;
	while (lista) //putem sa parcurgem asa pt ca nu e transmis prin adresa, deci aici e doar o copie
	{
		suma += lista->info.pret;
		numar++;
		lista = lista->urm;

	}
	return  suma / numar;
}

float calculeazaPretulMasinilorUnuiSofer(Nod* lista, const char* numeSofer) {
	float suma = 0;
	while (lista)
	{
		if (strcmp(lista->info.numeSofer, numeSofer) == 0)
		{
			suma += lista->info.pret;
		}
		lista = lista->urm;

	}
	return suma;
}

char* getCeaMaiScumpaMasina(Nod* lista)
{
	float pretMax = 0;
	char* modelScump = NULL;
	while (lista)
	{
		if (lista->info.pret > pretMax)
		{
			pretMax = lista->info.pret; modelScump = lista->info.model;

		}
		lista = lista->urm;
		if (pretMax > 0)
		{
			char* nou = malloc(strlen(modelScump) + 1);
			strcpy_s(nou, strlen(modelScump) + 1, modelScump);
			return nou;
		}
	}
	return NULL;
}

int main() {
	Nod* cap = NULL;
	cap = citireListaMasiniDinFisier("masini.txt");
	afisareListaMasini(cap);

	printf("%5.2f\n", calculeazaPretMediu(cap));
	printf("%5.2f\n", calculeazaPretulMasinilorUnuiSofer(cap, "Ionescu"));

	printf("%s", getCeaMaiScumpaMasina(cap));
	dezalocareListaMasini(&cap);
	return 0;
}