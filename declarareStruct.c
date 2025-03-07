#include<stdio.h>
#include<stdlib.h>

struct Angajat {
	int codAngajat;
	char* nume;
	char* prenume;
	struct {
		int an;
		char luna;
		char zi;
	}dataAngajarii;
	float salIncadrare;
};

struct Angajat initializare(int codAngajat, char* nume, char* prenume, int an, char luna, char zi, float salIncadrare) {
	struct Angajat a;
	a.codAngajat = codAngajat;
	a.nume = (char*)malloc(strlen(nume) + 1);
	strcpy_s(a.nume, strlen(nume) + 1, nume);
	a.prenume = (char*)malloc(strlen(prenume) + 1);
	strcpy_s(a.prenume, strlen(prenume) + 1, prenume);
	a.dataAngajarii.an = an;
	a.dataAngajarii.luna = luna;
	a.dataAngajarii.zi = zi;
	a.salIncadrare = salIncadrare;

	return a;
}

void afisare(struct Angajat a) {
	printf("ID angajat: %d\nAngajat: %s %s\nData angajarii: %d/%d/%d\nSalariul de incadrare: %.2f\n", a.codAngajat, a.nume, a.prenume, a.dataAngajarii.zi, a.dataAngajarii.luna, a.dataAngajarii.an, a.salIncadrare);
}

void modificaSalariu(struct Angajat* a, int salNou) {
	if (salNou > 0)
		a->salIncadrare = salNou;
}

void dezalocare(struct Angajat* a) {
	free(a->nume);
	free(a->prenume);
}

int main() {
	struct Angajat a = initializare(1000, "Popescu", "Ionel", 2000, 2, 1, 2500);

	afisare(a);

	modificaSalariu(&a, 3000);
	afisare(a);

	dezalocare(&a);
	afisare(a);

	return 0;
}