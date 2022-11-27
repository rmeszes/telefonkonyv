//
// Created by rmesz on 2022. 11. 26..
//

#ifndef TELEFONKONYV_MENU_H
#define TELEFONKONYV_MENU_H

#include "adatok.h"

/*!
 * Almenü névjegyek módosítására.
 * @param lista Lista, amivel dolgozni fog.
 * @param fajlnev A fájl neve, amiben módosítani fogja a névjegyet.
 */
void nevjegy_modositasa(Nevjegyek *lista, char *fajlnev);

/*!
 * Kilistázza a névjegyeket és megkéri a felhasználót, hogy válaszzon.
 * @param lista Lista, amivel dolgozni fog.
 * @return A választott lista. Ha a felhasználó visszalépett, akkor NULL!
 */
Nevjegy* nevjegyek_kiir(Nevjegyek *lista);

/*!
 * Felsorolja a névjegyeket és egy kiválasztására kiírja annak adatait.
 * @param lista Lista, amivel dolgozni fog.
 */
void nevjegyek_almenu(Nevjegyek* lista);

/*!
 * \brief Menü új névjegy beszúrására a felhasználó számára.
 *
 * Bekéri a felhasználótól a szükséges adatokat, majd azokat fájlba írja.
 * @param lista Lista, amivel dolgozni fog.
 * @param fajlnev Ebbe a fájlba fogja írni az újonnan készített listát. (vigyázat: az egész fájlt felül írja, a rendezettség érdekében.)
 */
void nevjegy_hozzaadasa_programbol(Nevjegyek *lista, char *fajlnev);

/*!
 * \brief Menü névjegy törlésére a felhasználó számára.
 *
 * Kilistázza a névjegyeket, majd a választott névjegyet a program törli, a fájlt módosítja.
 * @param lista Lista, amivel dolgozni fog.
 * @param fajlnev Ebbe a fájlba fogja írni az újonnan készített listát. (vigyázat: az egész fájlt felül írja, a rendezettség érdekében.)
 */
void nevjegy_torlese_programbol(Nevjegyek *lista, char *fajlnev);

#endif //TELEFONKONYV_MENU_H
