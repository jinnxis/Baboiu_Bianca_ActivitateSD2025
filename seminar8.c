#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// e de 2 tipuri -maxheap si minheap
// arbore binar - max 2 descendenti
// arbore binar complet -  fiecare parinte are fix 2 copii(mai putin frunzele )
// pt max fiecare parinte trb sa aiba val mai mare decat copiii

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

// creare structura pentru Heap
// un vector de elemente, lungimea vectorului si numarul de elemente din vector
struct Heap {
	int lungime; // arata nr de masini vizibile
	Masina* masini;
	int nrMasini; // arata totalul de masini
};
typedef struct Heap Heap;

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

Heap initializareHeap(int lungime) {
	Heap heap;
	heap.lungime = lungime;
	heap.masini = (Masina*)malloc(sizeof(Masina) * lungime);
	heap.nrMasini = 0;
	return heap;
}

void filtreazaHeap(Heap heap, int pozitieNod) {
	// primim nodul, stabilim cu formula 2*n+1, 2*n+2 care sunt copiii, selectam maximul si interschimbam daca e cazul
	if (pozitieNod >= 0 && pozitieNod < heap.nrMasini)
	{
		int stg = 2 * pozitieNod + 1;
		int drp = 2 * pozitieNod + 2;
		int pozMaxim = pozitieNod;
		if (stg < heap.nrMasini && heap.masini[pozMaxim].id < heap.masini[stg].id) // trb si conditii de verificat sa nu mergem in partea ascunsa(daca stg sau drp e intre nrMasini si lungime atunci e pe o poz ascunsa, nu e bine asa
			pozMaxim = stg; // e esential sa pun stg<heap.nrMasini
		if (drp < heap.nrMasini && heap.masini[pozMaxim].id < heap.masini[drp].id)
			pozMaxim = drp;
		if (pozMaxim != pozitieNod)
		{
			Masina aux;
			aux = heap.masini[pozitieNod];
			heap.masini[pozitieNod] = heap.masini[pozMaxim];
			heap.masini[pozMaxim] = aux;
			if (pozMaxim < (heap.nrMasini - 1) / 2)
				filtreazaHeap(heap, pozMaxim);
		}
	}
}

Heap citireHeapDeMasiniDinFisier(const char* numeFisier) {
	Heap heap = initializareHeap(10);
	FILE* f = fopen(numeFisier, "r");

	while (!feof(f))
	{
		heap.masini[heap.nrMasini] = citireMasinaDinFisier(f);
		heap.nrMasini++;

	} // intai citim tot si apoi filtram
	fclose(f);
	// ca sa filtram pornim de jos in sus ca sa putem parcurge peste tot (deci de la ultimul parinte)
	for (int i = (heap.nrMasini - 1) / 2; i >= 0; i--)
	{
		filtreazaHeap(heap, i);
	}
	return heap;
}

void afisareHeap(Heap heap) {
	for (int i = 0; i < heap.nrMasini; i++)
		afisareMasina(heap.masini[i]);
}

void afiseazaHeapAscuns(Heap heap) {
	// afiseaza elementele ascunse din heap
	for (int i = heap.nrMasini; i < heap.lungime; i++)
		afisareMasina(heap.masini[i]);
}

Masina extrageMasina(Heap* heap) {
	// extrage si returneaza masina de pe prima pozitie
	// elementul extras nu il stergem...doar il ascundem
	Masina aux = heap->masini[0];
	heap->masini[0] = heap->masini[heap->nrMasini - 1];
	heap->masini[heap->nrMasini - 1] = aux;
	heap->nrMasini--;
	for (int i = (heap->nrMasini - 1) / 2; i >= 0; i--)
	{
		filtreazaHeap(*heap, i);
	}
	return aux;
}


void dezalocareHeap(Heap* heap) {
	for (int i = 0; i < heap->lungime; i++)
	{
		free(heap->masini[i].numeSofer);
		free(heap->masini[i].model);
	}
	free(heap->masini);
	heap->lungime = 0;
	heap->nrMasini = 0;
	heap->masini = NULL;


}

int main() {

	Heap heap = citireHeapDeMasiniDinFisier("masini_arbore.txt");
	afisareHeap(heap);
	for (int i = 0; i < 10; i++)
		extrageMasina(&heap);

	printf("\n\n\nAfisare elemente ascunse: \n\n");
	afiseazaHeapAscuns(heap); printf("\n\n\n\n\n");
	afisareHeap(heap);
	return 0;
}