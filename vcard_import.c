//
// Created by rmesz on 2022. 11. 27..
//

#include "vcard_import.h"
#include "debugmalloc.h"

static void type_extractor(const char sor[], char* dest) {
    int i = 0;
    while (i < 5 & sor[i] != ':' & sor[i] != ';') {
        dest[i] = sor[i];
        i++;
    }
    dest[i] = '\0';
}

Nevjegyek* vcard_import(Nevjegyek* lista) {
#ifdef WIN32
    system("cls");
#endif
    printf("Importálni való fájl: (maximum 1000 karakter)\n");
    char fajlnev[1001];
    while(getchar() != '\n');
    gets(fajlnev);
    int hossz = strlen(fajlnev);
    if (fajlnev[hossz-4] != '.' | fajlnev[hossz-3] != 'v' | fajlnev[hossz-2] != 'c' | fajlnev[hossz-1] != 'f') strcat(fajlnev, ".vcf");

    FILE* fp;
    fp = fopen(fajlnev, "r");
    if (fp == NULL) {
        perror("Nem sikerült a fájl megnyitása, ok");
        while(getchar() != '\n');
        return lista;
    }

    char reader[501];

    fgets(reader, 501, fp);
    if (strcmp(reader, "BEGIN:VCARD\n") != 0) {
        printf("A fájl nem megfelelõ!");
        while(getchar() != '\n');
        return lista;
    }

    fgets(reader, 501, fp);
    if (strcmp(reader, "VERSION:4.0\n") != 0) {
        printf("A fájl nem vCard 4.0 verziójú!");
        while(getchar() != '\n');
        return lista;
    }
    Nevjegy *uj = malloc(sizeof(Nevjegy));
    while (fgets(reader, 501, fp) != NULL) {
        char type[6];
        type_extractor(reader, type);
        if (strcmp(type, "FN") == 0) {
            int i = 3;
            int j = 0;
            while (reader[i] != '\n') {
                uj->nev[j++] = reader[i++];
            }
            uj->nev[j] = '\0';
        } else if (strcmp(type, "TEL") == 0) {
            int i = 4;
            int j = 0;
            while (reader[i++] != ':');
            while (reader[i] != '\0') {
                uj->telefonszam[j++] = reader[i++];
            }
            uj->telefonszam[j] = '\0';
        } else if (strcmp(type, "EMAIL") == 0) {
            int i = 6;
            int j = 0;
            while (reader[i] != '\n') {
                uj->email[j++] = reader[i++];
            }
            uj->email[j] = '\0';
        }
    }

    if (strcmp(uj->nev,"") == 0 | strcmp(uj->telefonszam,"") == 0 | strcmp(uj->email,"") == 0) {
        printf("Nem sikerült a fájlbeolvasás\n");
        while(getchar() != '\n');
        return lista;
    }
    lista = uj_nevjegy(lista,uj->nev,uj->telefonszam,uj->email);
    printf("Sikerüt a beolvasás!\n"
           "A beolvasott adatok:\n"
           "\tNév: %s\n"
           "\tTelefonszám: %s\n"
           "\tEmail cím: %s\n",
           uj->nev, uj->telefonszam, uj->email);
    free(uj);
    while(getchar() != '\n');
    return lista;
}
