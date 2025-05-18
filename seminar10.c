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
typedef struct Nod Nod;
struct Nod {
    Nod* stg;
    Nod* drp;
    Masina info;
};
//creare structura pentru un nod dintr-un arbore binar de cautare

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

int calculeazaInaltimeArbore(Nod* radacina) {
    if (radacina) {
        int inaltimeStg = calculeazaInaltimeArbore(radacina->stg);
        int inaltimeDrp = calculeazaInaltimeArbore(radacina->drp);
        return 1 + (inaltimeStg > inaltimeDrp ? inaltimeStg : inaltimeDrp);
    }
    else return 0;
}

//ALTE FUNCTII NECESARE:
void rotireStanga(Nod** radacina)
{
    Nod* aux;
    aux = (*radacina)->drp;
    (*radacina)->drp = aux->stg;
    aux->stg = *radacina;
    *radacina = aux;

}
void rotireDreapta(Nod** radacina)
{
    Nod* aux;
    aux = (*radacina)->stg;//intai in aux imi salvez nodul de sub radacina pe care vreau sa il mut
    (*radacina)->stg = aux->drp;
    aux->drp = *radacina;//mut radacina in dreapta aux-ului care va fi noua
}
int gradEchilibru(Nod* radacina)
{
    if (radacina)
        return(calculeazaInaltimeArbore(radacina->stg) - calculeazaInaltimeArbore(radacina->drp));
    else
        return 0;
}
void adaugaMasinaInArboreEchilibrat(Nod** radacina, Masina masinaNoua) {
    if ((*radacina))
    {
        if ((*radacina)->info.id > masinaNoua.id)
            adaugaMasinaInArboreEchilibrat(&((*radacina)->stg), masinaNoua);
        else
            adaugaMasinaInArboreEchilibrat(&((*radacina)->drp), masinaNoua);
        int grad = gradEchilibru(*radacina);
        if (grad == 2) //dezechilibru stanga
        {
            if (gradEchilibru((*radacina)->stg) == 1)
                rotireDreapta(radacina);//pt ca radacina e deja de tip dublu pointer
            else {
                rotireStanga(&((*radacina)->stg));
                rotireDreapta(radacina);
            }

        }
        else
            if (grad == -2)
            {
                if (gradEchilibru((*radacina)->drp) == 1)
                    rotireDreapta(&((*radacina)->drp));
                rotireStanga(radacina);

            }

    }
    else
    {
        Nod* nou = (Nod*)malloc(sizeof(Nod));
        nou->drp = NULL;
        nou->stg = NULL;
        nou->info = masinaNoua;
        (*radacina) = nou;
    }



}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
    //functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
    //prin apelul repetat al functiei citireMasinaDinFisier()
    //ATENTIE - la final inchidem fisierul/stream-ul
    FILE* file = fopen(numeFisier, "r");
    Nod* radacina = NULL;
    while (!feof(file)) {
        Masina m = citireMasinaDinFisier(file);
        adaugaMasinaInArboreEchilibrat(&radacina, m);
        ;
    }
    fclose(file);
    return radacina;
}
void afisareArborePreOrdine(Nod* radacina) {
    if (radacina != NULL) {
        afisareMasina(radacina->info);
        afisareArborePreOrdine(radacina->stg);
        afisareArborePreOrdine(radacina->drp);
    }
}


void dezalocareArboreDeMasini(Nod** arbore) {
    //sunt dezalocate toate masinile si arborele de elemente
    if (*arbore) {
        dezalocareArboreDeMasini(&(*arbore)->stg);
        dezalocareArboreDeMasini(&(*arbore)->drp);
        free((*arbore)->info.model);
        free((*arbore)->info.numeSofer);
        free(*arbore);
        (*arbore) = NULL;

    }
}


Masina getMasinaByID(Nod* arbore, int id) {
    Masina m;
    m.id = -1;
    if (arbore) {
        if (arbore->info.id < id) {
            return getMasinaByID(arbore->drp, id);

        }
        else
            if (arbore->info.id > id) {
                return getMasinaByID(arbore->stg, id);

            }
            else {
                return arbore->info;
            }
    }


    return m;
}

int determinaNumarNoduri(/*arborele de masini*/) {
    //calculeaza numarul total de noduri din arborele binar de cautare
    return 0;
}
float calculeazaPretTotal(Nod* arbore) {
    //calculeaza pretul tuturor masinilor din arbore.
    if (arbore == NULL) {
        return 0;
    }
    float totalStanga = calculeazaPretTotal(arbore->stg);
    float totalDreapta = calculeazaPretTotal(arbore->drp);
    return arbore->info.pret + totalStanga + totalDreapta;
}

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer)
{
    float pretSubarboreStg = 0;
    return 0;
}

int main() {
    Nod* arbore = citireArboreDeMasiniDinFisier("masini.txt");
    afisareArborePreOrdine(arbore);
    printf("Pretul total al masinilor este: %.2f", calculeazaPretTotal(arbore));
    return 0;
}