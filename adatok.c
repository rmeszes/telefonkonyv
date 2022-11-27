//
// Created by rmesz on 2022. 11. 04..
//
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#include "adatok.h"
//#include "debugmalloc.h"

void nevjegy_torlese_listabol(Nevjegy* elem) {
    elem->elozo->kov = elem->kov;
    elem->kov->elozo = elem->elozo;
    free(elem);
}

bool fajlba_ment(Nevjegyek* lista, char* fajlnev) {
    FILE* fp;
    fp = fopen(fajlnev, "w");
    if (fp == NULL) {
        perror("Nem sikerült a fájlba mentés");
        printf("Továbblépés az Enter billentyûvel.");
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

/*!
 * \brief Egy sort Nevjegy elemre alakít.
 *
 * Foglal egy új Nevjegy elemet, aminek az adatszerkezetét felhasználva eltárolja benne a szükséges adatokat, miután azt a sorból kiolvasta.
 *
 * A mezo változó tárolja, hogy egy soron belül hanyadik mezõnél tartunk, amit ; karakterenként növelünk.
 * Ez egy switch-be folyik, ami ez alapján a beolvasott karaktert az uj elembe helyezi.
 *
 * FONTOS! A funkció egy dinamikusan lefoglalt elemet ad vissza, a hívó függvény felelõssége ennek a felszabadítása!
 * @param sor A feltörendõ sor.
 * @return Egy Nevjegy elem, amiben benne vannak a beolvasott adatok.
 */
static Nevjegy* sor_darabol(const char* sor) {
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
        perror("Nem sikerült a fájl megnyitása! Ok");
        return NULL;
    }

    char buffer[641]; // 640 karakter lehet egy sorban a mezõk karakterlimitjei miatt
    while (fgets(buffer,641,fp) != NULL) {
        Nevjegy *temp;
        temp = sor_darabol(buffer);
        uj_nevjegy(nevjegyek, temp->nev, temp->telefonszam, temp->email);
        free(temp);
    }

    fclose(fp);
    return nevjegyek;
}


void lista_felszabaditasa(Nevjegyek* lista) {
    Nevjegy *iter = lista->elso;
    while(iter != NULL) {
        Nevjegy *kov = iter->kov;
        free(iter);
        iter = kov;
    }
    free(lista);
}

