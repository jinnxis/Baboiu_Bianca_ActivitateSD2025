#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Baboiu Bianca -> B si B. Articolul Biblioteca:
struct Biblioteca {
	int id;
	char* denumire;
	int nrCarti;
	float timp;
};

struct Biblioteca citire() {
	struct Biblioteca b;

	printf("Introduceti ID-ul bibliotecii: ");
	scanf_s("%d", &b.id);
	getchar();

	char temp[100];
	printf("Introduceti denumirea bibliotecii: ");
	scanf_s("%[^\n]", temp, (unsigned)_countof(temp));
	getchar();
	b.denumire = (char*)malloc(strlen(temp) + 1);
	strcpy_s(b.denumire, strlen(temp) + 1, temp);

	printf("Introduceti nr. de carti: ");
	scanf_s("%d", &b.nrCarti);

	printf("Introduceti vechimea bibliotecii: ");
	scanf_s("%f", &b.timp);

	return b;
}

struct Biblioteca initializare(int id, const char* denumire, int nrCarti, float timp) {
	struct Biblioteca b;
	b.id = id;
	b.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy_s(b.denumire, strlen(denumire) + 1, denumire);
	b.nrCarti = nrCarti;
	b.timp = timp;
	return b;
}

void afisare(struct Biblioteca b) {
	printf("ID biblioteca: %d\nDenumirea bibliotecii: %s\nNr. de carti: %d\nDe cat timp functioneaza: %.2f ani\n\n", b.id, b.denumire, b.nrCarti, b.timp);
}

void modifica_nrCarti(struct Biblioteca* b, int nrCartiNou) {
	if (nrCartiNou > 0) {
		b->nrCarti = nrCartiNou;
	}
}

float medie_nrCarti(struct Biblioteca b1, struct Biblioteca b2, struct Biblioteca b3) {
	float suma = b1.nrCarti + b2.nrCarti + b3.nrCarti;
	float medie = suma / 3;
	return medie;
}

void dezalocare(struct Biblioteca* b) {
	free(b->denumire);
}

struct Biblioteca* copiazaBiblioteciDupaNrCarti(struct Biblioteca* vector, int dim, int* dimNoua, int prag) {
	*dimNoua = 0;
	for (int i = 0; i < dim; i++) {
		if (vector[i].nrCarti > prag) {
			(*dimNoua)++;
		}
	}
	struct Biblioteca* rezultat = (struct Biblioteca*)malloc((*dimNoua) * sizeof(struct Biblioteca));
	int k = 0;
	for (int i = 0; i < dim; i++) {
		if (vector[i].nrCarti > prag) {
			rezultat[k++] = initializare(vector[i].id, vector[i].denumire, vector[i].nrCarti, vector[i].timp);
		}
	}
	return rezultat;
}

struct Biblioteca* mutaBiblioteciDupaTimp(struct Biblioteca** vector, int* dim, int* dimNoua, float prag) {
	*dimNoua = 0;
	for (int i = 0; i < *dim; i++) {
		if ((*vector)[i].timp > prag) {
			(*dimNoua)++;
		}
	}
	struct Biblioteca* rezultat = (struct Biblioteca*)malloc((*dimNoua) * sizeof(struct Biblioteca));
	int k = 0, j = 0;
	struct Biblioteca* temp = (struct Biblioteca*)malloc((*dim - *dimNoua) * sizeof(struct Biblioteca));
	for (int i = 0; i < *dim; i++) {
		if ((*vector)[i].timp > prag) {
			rezultat[k++] = initializare((*vector)[i].id, (*vector)[i].denumire, (*vector)[i].nrCarti, (*vector)[i].timp);
			dezalocare(&(*vector)[i]);
		}
		else {
			temp[j++] = (*vector)[i];
		}
	}
	free(*vector);
	*vector = temp;
	*dim = j;
	return rezultat;
}

struct Biblioteca* concateneazaVectori(struct Biblioteca* v1, int dim1, struct Biblioteca* v2, int dim2) {
	struct Biblioteca* rezultat = (struct Biblioteca*)malloc((dim1 + dim2) * sizeof(struct Biblioteca));
	for (int i = 0; i < dim1; i++) {
		rezultat[i] = initializare(v1[i].id, v1[i].denumire, v1[i].nrCarti, v1[i].timp);
	}
	for (int i = 0; i < dim2; i++) {
		rezultat[dim1 + i] = initializare(v2[i].id, v2[i].denumire, v2[i].nrCarti, v2[i].timp);
	}
	return rezultat;
}

void afisareVector(struct Biblioteca* vector, int dim) {
	for (int i = 0; i < dim; i++)
		afisare(vector[i]);
}

int main() {
	/*struct Biblioteca biblioteca1 = initializare(1, "Biblioteca Nationala", 2500, 103.5);
	struct Biblioteca biblioteca2 = initializare(2, "Biblioteca Judeteana Iasi", 1350, 55.5);

	afisare(biblioteca1);
	afisare(biblioteca2);

	struct Biblioteca biblioteca3 = citire();
	printf("\n");
	afisare(biblioteca3);

	float medie = medie_nrCarti(biblioteca1, biblioteca2, biblioteca3);

	printf("Cele 3 biblioteci au, in medie, %.2f carti\n\n", medie);
	modifica_nrCarti(&biblioteca1, 2200);
	afisare(biblioteca1);*/

	int dim = 5;
	struct Biblioteca* biblioteci = (struct Biblioteca*)malloc(dim * sizeof(struct Biblioteca));
	biblioteci[0] = initializare(1, "Biblioteca Nationala", 2500, 103.5);
	biblioteci[1] = initializare(2, "Biblioteca Judeteana", 1400, 60.0);
	biblioteci[2] = initializare(3, "Biblioteca Comunala", 900, 20.0);
	biblioteci[3] = initializare(4, "Biblioteca Universitara", 1800, 45.0);
	biblioteci[4] = initializare(5, "Biblioteca Liceului", 700, 15.0);

	printf("Vectorul initial: \n");
	afisareVector(biblioteci, dim);

	int dimCopiate = 0;
	struct Biblioteca* copiate = copiazaBiblioteciDupaNrCarti(biblioteci, dim, &dimCopiate, 1500);
	printf("\nBiblioteci cu peste 1500 de carti: \n");
	afisareVector(copiate, dimCopiate);

	int dimMutate = 0;
	struct Biblioteca* mutate = mutaBiblioteciDupaTimp(&biblioteci, &dim, &dimMutate, 50.0);
	printf("\nBiblioteci cu o vechime mai mare de 50 de ani: \n");
	afisareVector(mutate, dimMutate);

	printf("\nVectorul ramas dupa mutare: \n");
	afisareVector(biblioteci, dim);

	struct Biblioteca* concatenat = concateneazaVectori(copiate, dimCopiate, mutate, dimMutate);
	printf("\nVector concatenat (copiate + mutate): \n");
	afisareVector(concatenat, dimCopiate + dimMutate);

	for (int i = 0; i < dim; i++) {
		dezalocare(&biblioteci[i]);
	}
	for (int i = 0; i < dimCopiate; i++) {
		dezalocare(&copiate[i]);
	}
	for (int i = 0; i < dimMutate; i++) {
		dezalocare(&mutate[i]);
	}
	for (int i = 0; i < dimCopiate + dimMutate; i++) {
		dezalocare(&concatenat[i]);
	}

	free(biblioteci);
	free(copiate);
	free(mutate);
	free(concatenat);

	return 0;
}