//
// Created by rmesz on 2022. 11. 04..
//
#include <stdbool.h>
#ifndef MAIN_C_ADATOK_H
#define MAIN_C_ADATOK_H

/*!
 * L�ncolt lista egy eleme, ebben t�rolom egy n�vjegy adatait.
 */
typedef struct Nevjegy {
    int id; //!< ID, a programon bel�l egy adott n�vjegy k�nnyebb azonos�t�s�hoz.
    char nev[301]; //!< A szem�ly neve, 300 karakter hossz� lehet + 1 z�r� karakter.
    char email[321]; //!< A szem�ly email c�me, 320 karakter hossz� lehet + 1 z�r� karakter.
    char telefonszam[31]; //!< A szem�ly telefonsz�ma, 30 karakter hossz� lehet + 1 z�r� karakter.

    struct Nevjegy *elozo; //!< A l�ncolt list�ban az el�z� elem t�rol�s�ra.
    struct Nevjegy *kov; //!< A l�ncolt list�ban a k�vetkez� elem t�rol�s�ra.
}Nevjegy;

/*!
 * Ez a strukt�ra t�rol k�t str�zsa elemet, ezenk�v�l egy folyamatosan n�vekv� ID kioszt�s�ra is szolg�l.
 * (Itt t�rol�dik a legnagyobb haszn�lt ID.)
 */
typedef struct Nevjegyek {
    Nevjegy *elso; //!< Kezd� str�zsaelem.
    Nevjegy *utolso; //!< V�gs� str�zsaelem.
    int id; //!< T�rolja az eddig legnagyobb kiosztott ID-t.
}Nevjegyek;

/*!
 * Egy Nevjegy -ekb�l �ll� dupl�n l�ncolt lista t�rl�s�t v�gzi
 * @param elem Ezt az elemet fogja t�r�lni
 */
void nevjegy_torlese_listabol(Nevjegy* elem);

/*!
 * \brief Beolvassa a f�jlb�l az adatokat + a list�t inicializ�lja.
 *
 * Ez a funkci� helyet foglal a l�ncolt list�nak, l�trehozza a k�t str�zsa-elemet, majd beleolvassa f�jlb�l az adatokat, amiket tal�l.
 *
 * FONTOS! A funkci� egy dinamikusan lefoglalt elemet ad vissza, a h�v� f�ggv�ny felel�ss�ge ennek a felszabad�t�sa!
 * @param fajlnev Beolvasand� f�jl.
 * @return A k�sz lista pointer-e.
 */
Nevjegyek* fajlbol_beolvas(char* fajlnev);


/*!
 * Egy Nevjegy -ekb�l �ll� lista felszabad�t�s�t v�gzi.
 * @param lista Felszabad�tand� lista.
 */
void lista_felszabaditasa(Nevjegyek* lista);

/*!
 * \brief �j n�vjegyet sz�r be a l�ncolt list�ba
 *
 * Ez a funcki� egy �j n�vjegy l�trehoz�s�t v�gzi el, a nev mez� szerint ABC sorrendben rendezve.
 * @param lista Lista, amivel dolgozni fog.
 * @param nev  Az �j n�vjegy neve.
 * @param telefonszam Az �j n�vjegybe �rand� telefonsz�m.
 * @param email Az �j n�vjegybe �rand� email c�m.
 * @return Visszat�r a m�dos�tott lista pointer�vel.
 */
Nevjegyek* uj_nevjegy(Nevjegyek* lista, char* nev, char* telefonszam, char* email);

/*!
 * \brief Egy f�jl fel�l�r�s�t v�gzi egy l�ncolt lista alapj�n.
 *
 * A sikeresss�g visszat�r�se fontos lehet, hogy a f�jl �s programon bel�li adatszerkezet perzisztens legyen.
 * @param lista Ki�rand� lista.
 * @param fajlnev F�jln�v, amibe �rni fog.
 * @return Visszat�r a f�jlba�r�s sikeress�g�vel.
 */
bool fajlba_ment(Nevjegyek* lista, char* fajlnev);

#endif //MAIN_C_ADATOK_H
