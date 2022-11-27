//
// Created by rmesz on 2022. 11. 26..
//

#include "kereses.h"
#include "string.h"
#include "stdio.h"
#ifdef _WIN32
#include <windows.h>
#endif


bool strmatch(const char vizsgalando[], const char feltetel[])
{
    int vizsg_hossz = strlen(vizsgalando);
    int feltetel_hossz = strlen(feltetel);

    if (feltetel_hossz == 0)
        return (vizsg_hossz == 0); // �res felt�tel, csak �res adattal lehetne egyenl�

    bool eredmenyek[vizsg_hossz + 1][feltetel_hossz + 1]; //eredm�nyek t�rol�s�ra

    //felt�lt�s false-al
    for (int i = 0; i < vizsg_hossz + 1; ++i) {
        for (int j = 0; j < feltetel_hossz + 1; ++j) {
            eredmenyek[i][j] = false;
        }
    }
    eredmenyek[0][0] = true;

    for (int j = 1; j <= feltetel_hossz; j++)
        if (feltetel[j - 1] == '*')
            eredmenyek[0][j] = eredmenyek[0][j - 1];

    for (int j = 1; j <= feltetel_hossz; j++)
        if (feltetel[j - 1] == '*')
            eredmenyek[0][j] = eredmenyek[0][j - 1];


    for (int i = 1; i <= vizsg_hossz; i++) {
        for (int j = 1; j <= feltetel_hossz; j++) {

            if (feltetel[j - 1] == '*') eredmenyek[i][j] = eredmenyek[i][j - 1] || eredmenyek[i - 1][j];
            else if (feltetel[j - 1] == '?' || vizsgalando[i - 1] == feltetel[j - 1]) eredmenyek[i][j] = eredmenyek[i - 1][j - 1];
            else eredmenyek[i][j] = false;
        }
    }

    return eredmenyek[vizsg_hossz][feltetel_hossz];
}

static int kereses_darab(Nevjegyek* lista, int mezo, char *feltetel) {
    int darab = 1;
    Nevjegy *mozgo = lista->elso->kov;
    if (mezo == 1) {
        printf("Keresett n�v:");
        char input[301];
        gets(input);
        strcpy(feltetel, input);

        while (mozgo->kov != NULL) {
            if (strmatch(mozgo->nev, feltetel)) darab++;
            mozgo = mozgo->kov;
        }
    }
    else if (mezo == 2) {
        printf("Keresett telefonsz�m:");
        char input[20];
        gets(input);
        strcpy(feltetel, input);

        while (mozgo->kov != NULL) {
            if (strmatch(mozgo->telefonszam, feltetel)) darab++;
            mozgo = mozgo->kov;
        }
    }
    else {
        printf("Keresett email:");
        char input[321];
        gets(input);
        strcpy(feltetel, input);

        while (mozgo->kov != NULL) {
            if (strmatch(mozgo->email, feltetel)) darab++;
            mozgo = mozgo->kov;
        }
    }
    return darab;
}


static void kereso(Nevjegyek *source, int mezo, char *feltetel, Nevjegy** cel) {
    Nevjegy* mozgo = source->elso->kov;
    int cel_id = 1;
    if (mezo == 1) {
        while (mozgo->kov != NULL) {
            if (strmatch(mozgo->nev, feltetel)) {
                cel[cel_id++] = mozgo;
            }
            mozgo = mozgo->kov;
        }
    } else if (mezo == 2) {
        while (mozgo->kov != NULL) {
            if (strmatch(mozgo->telefonszam, feltetel)) {
                cel[cel_id++] = mozgo;
            }
            mozgo = mozgo->kov;
        }
    } else {
        while (mozgo->kov != NULL) {
            if (strmatch(mozgo->email, feltetel)) {
                cel[cel_id++] = mozgo;
            }
            mozgo = mozgo->kov;
        }
    }
}

static void kereses_almenu(Nevjegy* elem) {
#ifdef _WIN32
    system("cls");
#endif
    printf("N�VJEGY\n"
           "\tN�v: %s\n"
           "\tTelefonsz�m: %s\n"
           "\tEmail c�m: %s\n"
           "Visszal�p�s # karakterrel\n", elem->nev, elem->telefonszam, elem->email);

    char input;

    scanf(" %c", &input);
    while (input != '#') {
        printf("�rv�nytelen bemenet!\n");
        //while(getchar() != '\n');
        scanf(" %c", &input);
    }
}

void kereses(Nevjegyek * lista) {
#ifdef _WIN32
    system("cls");
#endif
    printf("Mi alapj�n szeretn�l keresni?\n"
           "\t1. N�v\n"
           "\t2. Telefonsz�m\n"
           "\t3. Email c�m\n");
    int mezo;
    scanf("%d", &mezo);
    while (getchar() != '\n') {
        if (getchar() == '#') return;
    }
    while (mezo <= 1 & mezo >= 3) {
        printf("�rv�nytelen men�pont!\n");
        scanf("%d", &mezo);
        while (getchar() != '\n') {
            if (getchar() == '#') return;
        }
    }
#ifdef _WIN32
    system("cls");
#endif
    char feltetel[321];
    int db = kereses_darab(lista, mezo, feltetel);
    Nevjegy* talalatok[db];
    kereso(lista, mezo, feltetel, talalatok);
#ifdef _WIN32
    system("cls");
#endif
    printf("KERES�SI TAL�LATOK:\n");
    for (int i = 1; i < db; ++i) {
        printf("\t%d. %s\n", i, talalatok[i]->nev);
    }
    int valasztott;
    if (scanf("%d", &valasztott) == 1) {
        if (valasztott > 0 & valasztott <= db) {
            kereses_almenu(talalatok[valasztott]);
        }
    } else {
        while(getchar() != '\n');
    }
}