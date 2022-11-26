//
// Created by rmesz on 2022. 11. 26..
//

#include "menu.h"
#include <stdio.h>

#ifdef WIN32
#include "windows.h"
#endif

void nevjegyek_almenu(Nevjegyek* lista) {
#ifdef _WIN32
    system("cls");
#endif
    Nevjegy *temp = nevjegyek_kiir(lista);
    if (temp == NULL) return;

    printf("N�VJEGY\n"
           "\tN�v: %s\n"
           "\tTelefonsz�m: %s\n"
           "\tEmail c�m: %s\n"
           "Visszal�p�s # karakterrel\n", temp->nev, temp->telefonszam, temp->email);

    char input;

    scanf(" %c", &input);
    while (input != '#') {
        printf("�rv�nytelen bemenet!\n");
        //while(getchar() != '\n');
        scanf(" %c", &input);
    }
}

Nevjegy* nevjegyek_kiir(Nevjegyek *lista) {
    Nevjegy *mozgo = lista->elso;
    int darab = 0;

    while(mozgo != NULL) {
        darab++;
        mozgo = mozgo->kov;
    }
    darab--;  //a kezd� str�zsa pointert bem�solom a t�mbbe, mert megegyszer�s�ti az indexel�st, viszont az utols�t nem.

    Nevjegy* elemek[darab];

    mozgo = lista->elso;

    for(int i = 0; mozgo->kov != NULL; i++) {
        elemek[i] = mozgo;
        mozgo = mozgo->kov;
    }

    int input;
    char in_char;
    bool kilep = false;
    bool hamis_karakter = false;
    do {
        printf("N�VJEGYEK: (%d) Kil�p�s: #\n", darab-1);
        for (int i = 1; i < darab; i++) {
            printf("\t%d. %s\n", i, elemek[i]->nev);
        }
        do  {
            if(scanf("%d", &input)  != 1) {
                scanf(" %c", &in_char);
                if(in_char == '#')
                    kilep = true;
                else {
                    hamis_karakter = true;
                    while (getchar() != '\n');
                }
            }
            if (!(input >= 1 && input <= darab || kilep) || hamis_karakter ) {
                printf("�rv�nytelen men�pont!\n");
                hamis_karakter = false;
            }
        } while (!(input >= 1 && input <= darab || kilep));

        if(kilep == false && input != darab) { //ha kil�p, nem n�zz�k melyik men�pontot v�lasztja!
            return elemek[input];
        }
    } while (kilep == false && input != darab);
    return NULL;
}

void nevjegy_hozzaadasa_programbol(Nevjegyek *lista, char *fajlnev) {
#ifdef _WIN32
    system("cls");
#endif
    printf("�J N�VJEGY HOZZ�AD�SA\n");
    printf("N�v (maximum 300 karakter):");
    char nev[301];
    gets(nev);
    while (nev[0] == '\0') {
        printf("K�rlek �rj be �rv�nyes nevet.\n");
        gets(nev);
    }
    nev[0] = toupper(nev[0]);
    printf("Telefonsz�m (maximum 20 karakter):");
    char telefonszam[21];
    gets(telefonszam);
    while (telefonszam[0] == '\0') {
        printf("K�rlek �rj �rv�nyes telefonsz�mot.\n");
        gets(telefonszam);
    }
    printf("Email c�m (maximum 320 karakter):");
    char email[321];
    gets(email);
    while (email[0] == '\0') {
        printf("K�rlek �rj �rv�nyes email c�met.\n");
        gets(email);
    }
    uj_nevjegy(lista,nev,telefonszam,email);
    if(fajlba_ment(lista,fajlnev) == false) {
        Nevjegy *mozgo = lista->elso->kov;
        while (mozgo->id != lista->id) {
            mozgo = mozgo->kov;
        }
        nevjegy_torlese_listabol(mozgo);
    }
}

void nevjegy_torlese_programbol(Nevjegyek *lista, char *fajlnev) {
#ifdef _WIN32
    system("cls");
#endif
    printf("N�VJEGY T�RL�SE\n"
           "V�lassza ki a t�rlend� n�vjegyet!\n");
    Nevjegy* temp = nevjegyek_kiir(lista);
    if (temp != NULL) {
        nevjegy_torlese_listabol(temp);
        fajlba_ment(lista, fajlnev);
    }
}

void nevjegy_modositasa(Nevjegyek *lista, char *fajlnev) {
#ifdef _WIN32
    system("cls");
#endif
    printf("N�VJEGY M�DOS�T�SA\n"
           "V�lassza ki a m�dos�tani val� n�vjegyet!\n");
    Nevjegy* temp = nevjegyek_kiir(lista);
    if (temp != NULL) {
        while(getchar() != '\n');
        nevjegy_hozzaadasa_programbol(lista, fajlnev);
        nevjegy_torlese_listabol(temp);
        fajlba_ment(lista, fajlnev);
    }
}