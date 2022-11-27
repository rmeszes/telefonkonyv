//
// Created by rmesz on 2022. 11. 04..
//
#include <stdbool.h>
#ifndef MAIN_C_ADATOK_H
#define MAIN_C_ADATOK_H

/*!
 * Láncolt lista egy eleme, ebben tárolom egy névjegy adatait.
 */
typedef struct Nevjegy {
    int id; //!< ID, a programon belül egy adott névjegy könnyebb azonosításához.
    char nev[301]; //!< A személy neve, 300 karakter hosszú lehet + 1 záró karakter.
    char email[321]; //!< A személy email címe, 320 karakter hosszú lehet + 1 záró karakter.
    char telefonszam[31]; //!< A személy telefonszáma, 30 karakter hosszú lehet + 1 záró karakter.

    struct Nevjegy *elozo; //!< A láncolt listában az elõzõ elem tárolására.
    struct Nevjegy *kov; //!< A láncolt listában a következõ elem tárolására.
}Nevjegy;

/*!
 * Ez a struktúra tárol két strázsa elemet, ezenkívûl egy folyamatosan növekvõ ID kiosztására is szolgál.
 * (Itt tárolódik a legnagyobb használt ID.)
 */
typedef struct Nevjegyek {
    Nevjegy *elso; //!< Kezdõ strázsaelem.
    Nevjegy *utolso; //!< Végsõ strázsaelem.
    int id; //!< Tárolja az eddig legnagyobb kiosztott ID-t.
}Nevjegyek;

/*!
 * Egy Nevjegy -ekbõl álló duplán láncolt lista törlését végzi
 * @param elem Ezt az elemet fogja törölni
 */
void nevjegy_torlese_listabol(Nevjegy* elem);

/*!
 * \brief Beolvassa a fájlból az adatokat + a listát inicializálja.
 *
 * Ez a funkció helyet foglal a láncolt listának, létrehozza a két strázsa-elemet, majd beleolvassa fájlból az adatokat, amiket talál.
 *
 * FONTOS! A funkció egy dinamikusan lefoglalt elemet ad vissza, a hívó függvény felelõssége ennek a felszabadítása!
 * @param fajlnev Beolvasandó fájl.
 * @return A kész lista pointer-e.
 */
Nevjegyek* fajlbol_beolvas(char* fajlnev);


/*!
 * Egy Nevjegy -ekbõl álló lista felszabadítását végzi.
 * @param lista Felszabadítandó lista.
 */
void lista_felszabaditasa(Nevjegyek* lista);

/*!
 * \brief Új névjegyet szúr be a láncolt listába
 *
 * Ez a funckió egy új névjegy létrehozását végzi el, a nev mezõ szerint ABC sorrendben rendezve.
 * @param lista Lista, amivel dolgozni fog.
 * @param nev  Az új névjegy neve.
 * @param telefonszam Az új névjegybe írandó telefonszám.
 * @param email Az új névjegybe írandó email cím.
 * @return Visszatér a módosított lista pointerével.
 */
Nevjegyek* uj_nevjegy(Nevjegyek* lista, char* nev, char* telefonszam, char* email);

/*!
 * \brief Egy fájl felülírását végzi egy láncolt lista alapján.
 *
 * A sikeressség visszatérése fontos lehet, hogy a fájl és programon belüli adatszerkezet perzisztens legyen.
 * @param lista Kiírandó lista.
 * @param fajlnev Fájlnév, amibe írni fog.
 * @return Visszatér a fájlbaírás sikerességével.
 */
bool fajlba_ment(Nevjegyek* lista, char* fajlnev);

#endif //MAIN_C_ADATOK_H
