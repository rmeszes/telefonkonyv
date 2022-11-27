//
// Created by rmesz on 2022. 11. 27..
//

#ifndef TELEFONKONYV_VCARD_IMPORT_H
#define TELEFONKONYV_VCARD_IMPORT_H

#include "adatok.h"

/*!
 * vCard importálásra szolgáló menürendszer.
 * @param lista A lista, amibe kerül majd az új névjegy.
 * @return A módosított lista, az új elemmel.
 */
Nevjegyek* vcard_import(Nevjegyek* lista);

#endif //TELEFONKONYV_VCARD_IMPORT_H
