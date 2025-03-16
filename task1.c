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
	if (nrCartiNou > 0)
		b->nrCarti = nrCartiNou;
}

float medie_nrCarti(struct Biblioteca b1, struct Biblioteca b2, struct Biblioteca b3) {
	float suma = b1.nrCarti + b2.nrCarti + b3.nrCarti;
	float medie = suma / 3;
	return medie;
}

void dezalocare(struct Biblioteca* b) {
	free(b->denumire);
}

int main() {
	struct Biblioteca biblioteca1 = initializare(1, "Biblioteca Nationala", 2500, 103.5);
	struct Biblioteca biblioteca2 = initializare(2, "Biblioteca Judeteana Iasi", 1350, 55.5);

	afisare(biblioteca1);
	afisare(biblioteca2);

	struct Biblioteca biblioteca3 = citire();
	printf("\n");
	afisare(biblioteca3);

	float medie = medie_nrCarti(biblioteca1, biblioteca2, biblioteca3);

	printf("Cele 3 biblioteci au, in medie, %.2f carti\n\n", medie);
	modifica_nrCarti(&biblioteca1, 2200);
	afisare(biblioteca1);
	return 0;
}