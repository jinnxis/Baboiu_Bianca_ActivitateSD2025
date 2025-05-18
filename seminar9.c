#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//creare structura pentru un nod dintr-un arbore binar de cautare
typedef struct Nod Nod;
struct Nod {
	Nod* stg;
	Nod* drp;
	struct StructuraMasina info;
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


void adaugaMasinaInArbore(struct Nod** cap, Masina masinaNoua) {
	if ((*cap) != NULL)
	{
		if (masinaNoua.id < (*cap)->info.id)
			adaugaMasinaInArbore(&((*cap)->stg), masinaNoua);
		else if (masinaNoua.id > (*cap)->info.id)
			adaugaMasinaInArbore(&((*cap)->drp), masinaNoua);
		else
		{
			(*cap)->info.nrUsi = masinaNoua.nrUsi;
			(*cap)->info.pret = masinaNoua.pret;
			(*cap)->info.serie = masinaNoua.serie;
			(*cap)->info.id = masinaNoua.id;
			free((*cap)->info.numeSofer);
			(*cap)->info.numeSofer = (char*)malloc(strlen(masinaNoua.numeSofer) + 1);
			strcpy_s((*cap)->info.numeSofer, strlen(masinaNoua.numeSofer) + 1, masinaNoua.numeSofer);
			free((*cap)->info.model);
			(*cap)->info.model = (char*)malloc(strlen(masinaNoua.model) + 1);
			strcpy_s((*cap)->info.model, strlen(masinaNoua.model) + 1, masinaNoua.model);


		}

	}
	else
	{
		(*cap) = (Nod*)malloc(sizeof(Nod));
		(*cap)->stg = NULL;
		(*cap)->drp = NULL;
		(*cap)->info.nrUsi = masinaNoua.nrUsi;
		(*cap)->info.pret = masinaNoua.pret;
		(*cap)->info.serie = masinaNoua.serie;
		(*cap)->info.id = masinaNoua.id;
		(*cap)->info.numeSofer = (char*)malloc(strlen(masinaNoua.numeSofer) + 1);
		strcpy_s((*cap)->info.numeSofer, strlen(masinaNoua.numeSofer) + 1, masinaNoua.numeSofer);
		(*cap)->info.model = (char*)malloc(strlen(masinaNoua.model) + 1);
		strcpy_s((*cap)->info.model, strlen(masinaNoua.model) + 1, masinaNoua.model);

	}

}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* cap = NULL;
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		adaugaMasinaInArbore(&cap, m);
		free(m.model);
		free(m.numeSofer);

	}

	fclose(f);
	return cap;
}

void afisareArborePreOrdine(Nod* cap)
{
	if (cap)
	{
		afisareMasina(cap->info);
		afisareArborePreOrdine(cap->stg);
		afisareArborePreOrdine(cap->drp);
	}
}


void dezalocareArboreDeMasini(Nod** cap) {
	if ((*cap) != NULL)
	{
		dezalocareArboreDeMasini(&((*cap)->stg));
		dezalocareArboreDeMasini(&((*cap)->drp));
		free((*cap)->info.model);
		free((*cap)->info.numeSofer);
		free(*cap);
	}



}

Masina getMasinaByID(Nod* radacina, int id) {
	Masina m;
	m.id = -1;
	if (id > radacina->info.id)
		return getMasinaByID(radacina->drp, id);
	else if (id < radacina->info.id)
		return getMasinaByID(radacina->stg, id);

	else {
		m = radacina->info;
		m.numeSofer = (char*)malloc(strlen(radacina->info.numeSofer) + 1);
		strcpy_s(m.numeSofer, strlen(radacina->info.numeSofer) + 1, radacina->info.numeSofer);
		m.model = (char*)malloc(strlen(radacina->info.model) + 1);
		strcpy_s(m.model, strlen(radacina->info.numeSofer) + 1, radacina->info.numeSofer);
	}


	return m;
}

int determinaNumarNoduri(/*arborele de masini*/) {
	//calculeaza numarul total de noduri din arborele binar de cautare
	return 0;
}

int calculeazaInaltimeArbore(/*arbore de masini*/) {
	//calculeaza inaltimea arborelui care este data de 
	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
	return 0;
}

float calculeazaPretTotal(/*arbore de masini*/) {
	//calculeaza pretul tuturor masinilor din arbore.
	return 0;
}

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {

	Nod* arbore = NULL;
	arbore = citireArboreDeMasiniDinFisier("masini_arbore.txt");
	afisareArborePreOrdine(arbore);
	//dezalocareArboreDeMasini(&arbore);
	Masina m = getMasinaByID(arbore, 2);
	afisareMasina(m);
	return 0;
}