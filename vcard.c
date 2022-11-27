//
// Created by rmesz on 2022. 11. 16..
//
#include "menu.h"
#include "vcard.h"
#include "stdio.h"
#include "debugmalloc.h"
#ifdef WIN32
#include <windows.h>
#endif
#include "vcard_import.h"

Nevjegyek* vcard(Nevjegyek* lista) {
#ifdef WIN32
    system("cls");
#endif
    printf("Importálni, vagy exportálni szeretnél?\n"
           "\t1. Import\n"
           "\t2. Export\n");
    int in = getchar();
    while (in != '1' & in != '2' & in != '#') {
        printf("Érvénytelen menüpont!\n");
        while (getchar() != '\n');
        in = getchar();
    }
    if (in == '1') lista = vcard_import(lista);
    else card_export();
    return lista;
}