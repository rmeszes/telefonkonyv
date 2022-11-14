#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif


#include "debugmalloc.h"
#include "adatok.h"

#define TESZT
int main(int argc, char **argv) { //TODO: bemenet megoldása
#ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
#endif
    char fajlnev[101];
    if (argc > 1) {
        strcpy(fajlnev,argv[1]);
    }
    else {
        printf("A megnyitandó fájl neve: (maximum 100 karakter!)\n");
        gets(fajlnev);
    }
    Nevjegyek *adatok = fajlbol_beolvas(fajlnev);
    if (adatok == NULL) {
        printf("Nyomj meg egy gombot a programból való kilépéshez!\n");
        getchar();
        return 0;
    }

#ifdef TESZT
    Nevjegy* mozgo = adatok->elso->kov;
    printf("Debug: A lista elemei:\n");
    while (mozgo->kov != NULL) {
        printf("ID: %d\n", mozgo->id);
        printf("//\tNév: %s\n//\tTelefonszám: %s\n//\tEmail: %s\n", mozgo->nev, mozgo->telefonszam, mozgo->email);
        printf("\n");
        mozgo = mozgo->kov;
    }
#endif
    lista_felszabaditasa(adatok);

    printf("Nyomj meg egy gombot a programból való kilépéshez!\n");
    getchar();
    return 0;
}
