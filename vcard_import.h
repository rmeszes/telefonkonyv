//
// Created by rmesz on 2022. 11. 27..
//

#ifndef TELEFONKONYV_VCARD_IMPORT_H
#define TELEFONKONYV_VCARD_IMPORT_H

#include "adatok.h"

/*!
 * vCard import�l�sra szolg�l� men�rendszer.
 * @param lista A lista, amibe ker�l majd az �j n�vjegy.
 * @return A m�dos�tott lista, az �j elemmel.
 */
Nevjegyek* vcard_import(Nevjegyek* lista);

#endif //TELEFONKONYV_VCARD_IMPORT_H
