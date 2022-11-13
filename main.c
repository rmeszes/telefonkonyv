#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "debugmalloc.h"
#include "adatok.h"

int main() {
#ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
#endif
    char fajlnev[101];
    printf("A megnyitandó fájl neve: (maximum 100 karakter!)\n");
    gets(fajlnev);
    Nevjegyek *adatok = fajlbol_beolvas(fajlnev);
    if (adatok == NULL) {
        printf("Nyomj meg egy gombot a programból való kilépéshez!\n");
        getchar();
        return 0;
    }

    Nevjegy* mozgo = adatok->elso->kov;
    printf("Debug: A lista elemei:\n");
    while (mozgo != NULL) {
        printf("Név: %s\nEmail: %s\nTelefonszám: %s\n", mozgo->nev, mozgo->telefonszam, mozgo->email);
        mozgo = mozgo->kov;
    }
    printf("\n");

    printf("Debug: Teszt elem:\nNév: %s\nEmail: %s\nTelefonszám: %s\n", adatok->utolso->elozo->nev, adatok->utolso->elozo->email, adatok->utolso->elozo->telefonszam);

    lista_felszabaditasa(adatok);

    printf("Nyomj meg egy gombot a programból való kilépéshez!\n");
    getchar();
    return 0;
}
