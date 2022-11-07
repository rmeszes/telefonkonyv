//
// Created by rmesz on 2022. 11. 04..
//

#include "adatok.h"
#include "debugmalloc.h"

/*static char* elem_beolvasasa(FILE* fp) {
    char* elem =
    return elem;
}*/

Nevjegy* uj_nevjegy(Nevjegyek* lista, char* nev, char* email, char* telefonszam) {

}

/* Visszatér a beolvasott láncolt lista pointerével, amit a hívónak fel kell szabadítani! */
Nevjegyek* fajlbol_beolvas(char* fajlnev) {
    Nevjegyek *nevjegyek = (Nevjegyek*) malloc(sizeof(Nevjegyek));
    nevjegyek->elso = (Nevjegy*) malloc(sizeof(Nevjegy));
    nevjegyek->utolso = (Nevjegy*) malloc(sizeof(Nevjegy));
    nevjegyek->elso->kov = nevjegyek->utolso;
    nevjegyek->utolso->elozo = nevjegyek->elso;
    nevjegyek->utolso->kov = NULL;

    FILE* fp;
    fp = fopen(strdup(fajlnev), "r");
    if(fp == NULL) {
        perror("Nem sikerült a fájl megnyitása! Ok");
        return NULL;
    }
    printf("A %s fájl megnyitása sikerült.\n", strdup(fajlnev));
    //példa-beolvasás debug szempontból
    char buffer[101];
    fgets(buffer,100,fp);
    printf("Elsõ 100 karaker: %s", buffer);

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