//
// Created by rmesz on 2022. 11. 26..
//

#ifndef TELEFONKONYV_MENU_H
#define TELEFONKONYV_MENU_H

#include "adatok.h"

void nevjegy_modositasa(Nevjegyek *lista, char *fajlnev);

void nevjegy_torlese_listabol(Nevjegy* elem);

Nevjegy* nevjegyek_kiir(Nevjegyek *lista);

void nevjegyek_almenu(Nevjegyek* lista);

void nevjegy_hozzaadasa_programbol(Nevjegyek *lista, char *fajlnev);

void nevjegy_torlese_programbol(Nevjegyek *lista, char *fajlnev);

#endif //TELEFONKONYV_MENU_H
