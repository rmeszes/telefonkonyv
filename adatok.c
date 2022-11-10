//
// Created by rmesz on 2022. 11. 04..
//

#include "adatok.h"
#include "debugmalloc.h"

/*static char* elem_beolvasasa(FILE* fp) {
    char* elem =
    return elem;
}*/

Nevjegyek* uj_nevjegy(Nevjegyek* lista, char* nev, char* email, char* telefonszam) {
    Nevjegy *uj;
    uj = malloc(sizeof(Nevjegy));
    strcpy(uj->nev, nev);
    strcpy(uj->email, email);
    strcpy(uj->telefonszam, telefonszam);

    //Nevjegy* mozgo = lista->elso;

    /*while (mozgo->kov != lista->utolso) {
        mozgo = mozgo->kov;
    }*/

    uj->elozo = lista->utolso->elozo;
    uj->kov = lista->utolso;
    lista->utolso->elozo->kov = uj;
    lista->utolso->elozo = uj;
    return lista;
}

/* Visszat�r a beolvasott l�ncolt lista pointer�vel, amit a h�v�nak fel kell szabad�tani! */
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
        perror("Nem siker�lt a f�jl megnyit�sa! Ok");
        return NULL;
    }
    printf("Debug: A %s f�jl megnyit�sa siker�lt.\n", strdup(fajlnev));
    //p�lda-beolvas�s debug szempontb�l
    char buffer[101];
    fgets(buffer,100,fp);
    printf("Debug: Els� 100 karaker: %s\n", buffer);

    nevjegyek = uj_nevjegy(nevjegyek, "n�v", "email", "telefonsz�m");

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