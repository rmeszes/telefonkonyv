//
// Created by rmesz on 2022. 11. 16..
//

#ifndef TELEFONKONYV_VCARD_H
#define TELEFONKONYV_VCARD_H

#include "adatok.h"

/*!
 * A vCard-ok kezel�s�re szolg�l� men�rendszert h�vja meg.
 * @param lista A n�vjegyek list�ja.
 * @return Visszat�r a list�val, annak eset�re ha import�l�sra ker�lt sor.
 */
Nevjegyek* vcard(Nevjegyek* lista);

#endif //TELEFONKONYV_VCARD_H
