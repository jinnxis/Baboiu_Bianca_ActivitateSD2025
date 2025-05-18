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
//pt coada adaugarea enque, extragere deque, ordinea e FIFO
//pt stiva adaugare push, extragere pull, ordinea e LIFO

//STACK
//Alegeti prin ce veti reprezenta stiva si creati structura necesara acestei stive
//putem reprezenta o stiva prin LSI, LDI sau vector

typedef struct Nod Nod;
struct Nod {
	Masina info;
	Nod* urm;
};


void pushStack(Nod** stiva, Masina masina) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->urm = (*stiva);
	nou->info = masina;
	(*stiva) = nou;

}

Masina popStack(Nod** stiva) {
	if (*stiva) {
		Masina nou = (*stiva)->info;
		Nod* aux = (*stiva);
		(*stiva) = (*stiva)->urm;
		free(aux);
		return nou;
	}
	else
	{
		Masina m;
		m.id = -1;
		return m;
	}
}

unsigned char emptyStack(Nod* stiva) {
	return (stiva == NULL);
}

Nod* citireStackMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* stiva = NULL;

	while (!feof(f))
	{
		pushStack(&stiva, citireMasinaDinFisier(f));
	}
	fclose(f);
	return stiva;
}

void dezalocareStivaDeMasini(Nod** stiva) {
	Nod* aux;
	while (*stiva)
	{
		aux = (*stiva)->urm;
		free((*stiva)->info.model);
		free((*stiva)->info.numeSofer);
		free(*stiva);
		(*stiva) = aux;
	}

}

int stackSize(Nod* stiva) {
	int nr = 0;
	if (stiva) {
		while (stiva->urm)
		{
			nr++;
			stiva = stiva->urm;
		}
	}
	return nr;
}

//QUEUE
//Alegeti prin ce veti reprezenta coada si creati structura necesara acestei cozi
//putem reprezenta o coada prin LSI, LDI sau vector

typedef struct NodDublu NodDublu;
struct NodDublu {
	NodDublu* prev;
	NodDublu* urm;
	Masina info;
};
typedef struct Lista Lista;
struct Lista {
	NodDublu* prim;
	NodDublu* ultim;
};
void enqueue(Lista* coada, Masina masina) {
	NodDublu* nou = (NodDublu*)malloc(sizeof(NodDublu));
	nou->info = masina;
	nou->prev = NULL;
	if (coada->prim)
	{
		coada->prim->prev = nou;
		nou->urm = coada->prim;


	}
	else
	{
		coada->ultim = nou;

	}
	coada->prim = nou;
}

Masina dequeue(Lista* coada) {
	Masina m;
	if (coada->ultim)
	{
		NodDublu* aux = coada->ultim;
		m = aux->info;
		coada->ultim = aux->prev;
		if (coada->ultim)
			coada->ultim->urm = NULL;
		else
			coada->prim = NULL;
		free(aux);
	}
	else
	{
		m.id = -1;
	}
	return m;
}

Lista citireCoadaDeMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Lista coada;
	coada.prim = NULL;
	coada.ultim = NULL;

	while (!feof(f))
	{
		enqueue(&coada, citireMasinaDinFisier(f));
	}
	fclose(f);
	return coada;
}

void dezalocareCoadaDeMasini(Lista* coada) {
	NodDublu* aux = coada->ultim;
	while (aux)
	{
		NodDublu* temp = aux;
		aux = aux->prev;
		free(temp->info.model);
		free(temp->info.numeSofer);
		free(temp);
	}
	free(aux);
	coada->prim = NULL;
	coada->ultim = NULL;
}


//metode de procesare
Masina getMasinaByID(/*stiva sau coada de masini*/int id);

float calculeazaPretTotal(Lista coada)
{
	float suma = 0;
	Lista nou;
	nou.prim = NULL;
	nou.ultim = NULL;
	while (coada.prim)
	{
		Masina m = dequeue(&coada);
		suma += m.pret;
		enqueue(&nou, m);
	}
	coada.prim = nou.prim;
	coada.ultim = nou.ultim;

}

int main() {
	Nod* stiva = citireStackMasiniDinFisier("masini.txt");
	Masina m = popStack(&stiva);
	afisareMasina(m);
	Masina n = popStack(&stiva);
	afisareMasina(n);
	dezalocareStivaDeMasini(&stiva);
	printf("Stiva e goala? da=1, nu=0: %u\n", emptyStack(stiva));
	printf("Avem %d Masini in stiva.\n\n", stackSize(stiva));
	citireCoadaDeMasiniDinFisier("masini.txt");
	Lista coada = citireCoadaDeMasiniDinFisier("masini.txt");
	afisareMasina(dequeue(&coada));
	printf("Suma este: %.2f", calculeazaPretTotal(coada));
	//dezalocareCoadaDeMasini(&coada);
	return 0;
}