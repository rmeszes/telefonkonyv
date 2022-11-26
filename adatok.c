//
// Created by rmesz on 2022. 11. 04..
//
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#include "adatok.h"
#include "debugmalloc.h"

void nevjegy_torlese_listabol(Nevjegy* elem) {
    elem->elozo->kov = elem->kov;
    elem->kov->elozo = elem->elozo;
    free(elem);
}

bool fajlba_ment(Nevjegyek* lista, char* fajlnev) {
    FILE* fp;
    fp = fopen(fajlnev, "w");
    if (fp == NULL) {
        perror("Nem siker�lt a f�jlba ment�s");
        printf("Tov�bbl�p�s az Enter billenty�vel.");
        while (getchar() != '\n');
        return false;
    }
    Nevjegy *mozgo = lista->elso->kov;
    while (mozgo->kov != NULL) {
        fprintf(fp, "%s;%s;%s;\n", mozgo->nev, mozgo->telefonszam, mozgo->email);
        mozgo = mozgo->kov;
    }
    fclose(fp);
    return true;
}

/*
 * Besz�r egy �j n�vjegyet a list�ba, abc sorrend szerinti hely�re (n�v mez� alapj�n).
 */
Nevjegyek* uj_nevjegy(Nevjegyek* lista, char* nev, char* telefonszam, char* email) {
    Nevjegy *uj;
    uj = malloc(sizeof(Nevjegy));
    strcpy(uj->nev, nev);
    strcpy(uj->email, email);
    strcpy(uj->telefonszam, telefonszam);
    uj->id = ++lista->id;

    Nevjegy *mozgo = lista->elso->kov;

    while (strcmp(mozgo->nev, uj->nev) <= 0 && mozgo->kov != NULL) {
        mozgo = mozgo->kov;
    }

    uj->elozo = mozgo->elozo;
    uj->kov = mozgo;
    mozgo->elozo->kov = uj;
    mozgo->elozo = uj;
    return lista;
}

/*
 * L�trehoz egy Nevjegy elemet egy f�jlb�l beolvasott sorb�l (sztringb�l).
 */

static Nevjegy* uj_elem_fajlbol(const char* sor) {
    Nevjegy* uj = malloc(sizeof(Nevjegy));
    int mezo = 0;
    int sor_szamlalo = 0;
    int mezo_szamlalo = 0;
    while (mezo != 3){
        if(sor[sor_szamlalo] == ';') {
            mezo++;
            sor_szamlalo++;
            mezo_szamlalo = 0;
        }
        else {
            switch(mezo) {
                case 0:
                    uj->nev[mezo_szamlalo++] = sor[sor_szamlalo++];
                    uj->nev[mezo_szamlalo] = '\0';
                    break;
                case 1:
                    uj->telefonszam[mezo_szamlalo++] = sor[sor_szamlalo++];
                    uj->telefonszam[mezo_szamlalo] = '\0';
                    break;
                case 2:
                    uj->email[mezo_szamlalo++] = sor[sor_szamlalo++];
                    uj->email[mezo_szamlalo] = '\0';
                    break;
                default:
                    return NULL;
            }
        }
    }
    return uj;
}

/*
 * Visszat�r a beolvasott l�ncolt lista pointer�vel, amit a h�v�nak fel kell szabad�tani!
 */
Nevjegyek* fajlbol_beolvas(char* fajlnev) {
    Nevjegyek *nevjegyek = (Nevjegyek*) malloc(sizeof(Nevjegyek));
    nevjegyek->elso = (Nevjegy*) malloc(sizeof(Nevjegy));
    nevjegyek->utolso = (Nevjegy*) malloc(sizeof(Nevjegy));
    nevjegyek->elso->kov = nevjegyek->utolso;
    nevjegyek->utolso->elozo = nevjegyek->elso;
    nevjegyek->utolso->kov = NULL;
    nevjegyek->elso->elozo = NULL;
    nevjegyek->id = 0;

    FILE* fp;
    fp = fopen(strdup(fajlnev), "r");
    if (fp == NULL) {
        lista_felszabaditasa(nevjegyek);
        perror("Nem siker�lt a f�jl megnyit�sa! Ok");
        return NULL;
    }

    char buffer[641]; // 640 karakter lehet egy sorban a mez�k karakterlimitjei miatt
    while (fgets(buffer,641,fp) != NULL) {
        Nevjegy *temp;
        temp = uj_elem_fajlbol(buffer);
        uj_nevjegy(nevjegyek, temp->nev, temp->telefonszam, temp->email);
        free(temp);
    }

    fclose(fp);
    return nevjegyek;
}


/*
 * lista felszabad�t�s.
 */
void lista_felszabaditasa(Nevjegyek* lista) {
    Nevjegy *iter = lista->elso;
    while(iter != NULL) {
        Nevjegy *kov = iter->kov;
        free(iter);
        iter = kov;
    }
    free(lista);
}

