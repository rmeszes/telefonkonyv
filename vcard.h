//
// Created by rmesz on 2022. 11. 16..
//

#ifndef TELEFONKONYV_VCARD_H
#define TELEFONKONYV_VCARD_H

#include "adatok.h"

/*!
 * A vCard-ok kezelésére szolgáló menürendszert hívja meg.
 * @param lista A névjegyek listája.
 * @return Visszatér a listával, annak esetére ha importálásra került sor.
 */
Nevjegyek* vcard(Nevjegyek* lista);

#endif //TELEFONKONYV_VCARD_H
