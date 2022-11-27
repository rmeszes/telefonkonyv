//
// Created by rmesz on 2022. 11. 27..
//

#include "vcard_export.h"
//#include "debugmalloc.h"
#include <malloc.h>
#ifdef WIN32
#include <windows.h>
#endif
#include "menu.h"
#include "stdio.h"


/*!
 * Bekéri, hogy milyen fájlnéven mentse a fájlt, majd ezt megnyitja olvasásra.
 * @return A megnyitott FILE*, vagy NULL.
 */
static FILE* fajl_megnyitas() {
#ifdef WIN32
    system("cls");
#endif
    char fajlnev[501];
    printf("A cél fájl helye/neve: (max. 500 karakter)");
    while(getchar() != '\n');
    gets(fajlnev);

    int hossz = strlen(fajlnev);
    if (fajlnev[hossz-4] != '.' | fajlnev[hossz-3] != 'v' | fajlnev[hossz-2] != 'c' | fajlnev[hossz-1] != 'f') strcat(fajlnev, ".vcf");

    FILE* fp;
    fp = fopen(fajlnev, "w");
    if(fp == NULL){
        perror("Nem sikerült a fájl létrehozása");
        while(getchar() != '\n');
        return NULL;
    }
    return fp;
}

void vcard_export(Nevjegyek* lista) {
    Nevjegy* temp = nevjegyek_kiir(lista);
    FILE *fp = fajl_megnyitas();
    if(fp == NULL) {
        return;
    }
    fprintf(fp,"BEGIN:VCARD\n"
               "VERSION:4.0\n"
               "FN:%s\n"
               "TEL;TYPE=voice:%s\n"
               "EMAIL:%s\n"
               "END:VCARD\n",
            temp->nev, temp->telefonszam, temp->email);
    fclose(fp);
}