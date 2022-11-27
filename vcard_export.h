//
// Created by rmesz on 2022. 11. 27..
//

#ifndef TELEFONKONYV_VCARD_EXPORT_H
#define TELEFONKONYV_VCARD_EXPORT_H

#include "adatok.h"

/*!
 * \brief vCard exportálására szolgáló menü
 *
 * Bekéri a felhasználótól melyik névjegyet és milyen fájlba szeretné írni, ezután ezt elvégzi.
 * @param lista A névjegyek listája.
 */
void vcard_export(Nevjegyek* lista);

#endif //TELEFONKONYV_VCARD_EXPORT_H
