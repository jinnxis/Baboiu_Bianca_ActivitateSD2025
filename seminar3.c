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
typedef struct StructuraMasina Masina; //in loc sa scriu struct StructuraMasina am definit un alias Masina 

void afisareMasina(Masina masina) {
	printf("ID masina: %d\nNumar usi: %d \nPretul: %5.2f \nModelul: %s \nNume sofer: %s \nSerie: %c\n\n", masina.id, masina.nrUsi, masina.pret, masina.model, masina.numeSofer, masina.serie);
}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	for (int i = 0; i < nrMasini; i++)
		afisareMasina(masini[i]);

}

void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
	Masina* copie = (Masina*)malloc(((*nrMasini) + 1) * sizeof(Masina));
	for (int i = 0; i < (*nrMasini); i++)
	{
		copie[i] = (*masini)[i]; //fac shallow copy si nu modific pointerii ca sa fie legaturile bune sau daca fac deep copy, trebuie intai sterse inainte de realocare
	}
	copie[(*nrMasini)] = masinaNoua;
	free((*masini)); //free e o functie
	(*masini) = copie; //am mutat pointer ul la adresa lui copie
	(*nrMasini)++;
}

Masina citireMasinaFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	char* aux;
	fgets(buffer, 100, file);
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux); //cast din codul ASCII la int prin functia atoi()
	m1.nrUsi = atoi(strtok(NULL, sep)); //ca sa se uite/sa continue cautarea de unde a ramas 
	m1.pret = atof(strtok(NULL, sep)); //atof e importat doar in stdlib
	//trb citit intr un buffer, apoi alocam spatiu pentru char* si copiem, altfel s ar pierde valorile cum tot ce citim aici e salvat local in stack-ul functiei si nu in heap
	aux = strtok(NULL, sep);
	m1.model = (char*)malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	m1.numeSofer = (char*)malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
	m1.serie = strtok(NULL, sep)[0]; //dereferentiere sau indexare de 0 ca sa luam doar un caracter(primul)
	return m1;




}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite)
{
	FILE* f = fopen(numeFisier, "r"); //parametrii:numele fisierului+modul de descriere(r pentru read)
	(*nrMasiniCitite) = 0;
	Masina* masini = NULL;
	do
	{
		adaugaMasinaInVector(&masini, nrMasiniCitite, citireMasinaFisier(f));

	} while (!feof(f)); //feof() e functie
	fclose(f);
	return masini;
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	for (int i = 0; i < *nrMasini; i++) {
		free((*vector)[i].model);
		free((*vector)[i].numeSofer);
	}
	free(*vector);
	*vector = NULL;
	*nrMasini = 0;
}
float pretMediuDupaNrUsi(Masina* vector, int nrMasini, int nrUsi)
{
	float suma = 0;
	int index = 0;
	for (int i = 0; i < nrMasini; i++)
	{
		if (vector[i].nrUsi == nrUsi)
		{
			suma += vector[i].pret;
			index++;
		}
	}
	return suma / index;
}

int main()
{
	//in masini.txt despartitorul e virgula pentru a putea citi denumiri cu spatiu
	Masina* masini = NULL;
	int numarMasini = 0;
	masini = citireVectorMasiniFisier("masini.txt", &numarMasini);
	afisareVectorMasini(masini, numarMasini);
	float medie = pretMediuDupaNrUsi(masini, numarMasini, 5);
	printf("Media masinilor este: %2f", medie);
	dezalocareVectorMasini(&masini, &numarMasini);
	return 0;
}