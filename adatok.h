//
// Created by rmesz on 2022. 11. 04..
//

#ifndef MAIN_C_ADATOK_H
#define MAIN_C_ADATOK_H

typedef struct Nevjegy {
    int id;
    char nev[301];
    char email[321];
    char telefonszam[21];

    struct Nevjegy *elozo, *kov;
}Nevjegy;

typedef struct Nevjegyek {
    Nevjegy *elso;
    Nevjegy *utolso;
    int id;
}Nevjegyek;

Nevjegyek* fajlbol_beolvas(char* fajlnev);

void lista_felszabaditasa(Nevjegyek* lista);

Nevjegyek* uj_nevjegy(Nevjegyek* lista, char* nev, char* email, char* telefonszam);

void nevjegyek_kiir(Nevjegyek *lista);

#endif //MAIN_C_ADATOK_H
