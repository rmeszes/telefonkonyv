//
// Created by rmesz on 2022. 11. 27..
//

#ifndef TELEFONKONYV_VCARD_EXPORT_H
#define TELEFONKONYV_VCARD_EXPORT_H

#include "adatok.h"

/*!
 * \brief vCard export�l�s�ra szolg�l� men�
 *
 * Bek�ri a felhaszn�l�t�l melyik n�vjegyet �s milyen f�jlba szeretn� �rni, ezut�n ezt elv�gzi.
 * @param lista A n�vjegyek list�ja.
 */
void vcard_export(Nevjegyek* lista);

#endif //TELEFONKONYV_VCARD_EXPORT_H
