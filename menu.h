//
// Created by rmesz on 2022. 11. 26..
//

#ifndef TELEFONKONYV_MENU_H
#define TELEFONKONYV_MENU_H

#include "adatok.h"

/*!
 * Almen� n�vjegyek m�dos�t�s�ra.
 * @param lista Lista, amivel dolgozni fog.
 * @param fajlnev A f�jl neve, amiben m�dos�tani fogja a n�vjegyet.
 */
void nevjegy_modositasa(Nevjegyek *lista, char *fajlnev);

/*!
 * Kilist�zza a n�vjegyeket �s megk�ri a felhaszn�l�t, hogy v�laszzon.
 * @param lista Lista, amivel dolgozni fog.
 * @return A v�lasztott lista. Ha a felhaszn�l� visszal�pett, akkor NULL!
 */
Nevjegy* nevjegyek_kiir(Nevjegyek *lista);

/*!
 * Felsorolja a n�vjegyeket �s egy kiv�laszt�s�ra ki�rja annak adatait.
 * @param lista Lista, amivel dolgozni fog.
 */
void nevjegyek_almenu(Nevjegyek* lista);

/*!
 * \brief Men� �j n�vjegy besz�r�s�ra a felhaszn�l� sz�m�ra.
 *
 * Bek�ri a felhaszn�l�t�l a sz�ks�ges adatokat, majd azokat f�jlba �rja.
 * @param lista Lista, amivel dolgozni fog.
 * @param fajlnev Ebbe a f�jlba fogja �rni az �jonnan k�sz�tett list�t. (vigy�zat: az eg�sz f�jlt fel�l �rja, a rendezetts�g �rdek�ben.)
 */
void nevjegy_hozzaadasa_programbol(Nevjegyek *lista, char *fajlnev);

/*!
 * \brief Men� n�vjegy t�rl�s�re a felhaszn�l� sz�m�ra.
 *
 * Kilist�zza a n�vjegyeket, majd a v�lasztott n�vjegyet a program t�rli, a f�jlt m�dos�tja.
 * @param lista Lista, amivel dolgozni fog.
 * @param fajlnev Ebbe a f�jlba fogja �rni az �jonnan k�sz�tett list�t. (vigy�zat: az eg�sz f�jlt fel�l �rja, a rendezetts�g �rdek�ben.)
 */
void nevjegy_torlese_programbol(Nevjegyek *lista, char *fajlnev);

#endif //TELEFONKONYV_MENU_H
