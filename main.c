#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

//#include "debugmalloc.h"
#include "adatok.h"
#include "menu.h"
#include "kereses.h"
#include "vcard.h"


int main(int argc, char **argv) {
#ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
#endif
    char fajlnev[1001];
    if (argc > 1) {
        strcpy(fajlnev,argv[1]);
    }
    else {
        printf("A megnyitandó fájl neve: (maximum 1000 karakter!)\n");
        gets(fajlnev);
    }
    Nevjegyek *adatok = fajlbol_beolvas(fajlnev); //!<A fõ adattárolója a programnak. Ide olvassa be a névjegyeket és ezzel végez el minden mûveletet.
    if (adatok == NULL) {
        printf("Nyomj meg egy gombot a programból való kilépéshez!\n");
        getchar();
        return 0;
    }
    fajlba_ment(adatok, fajlnev);

    int input;
    char in_char;
    bool kilep = false;
    bool hamis_karakter = false;
    do {
        system("cls");
        printf("MENÜ\n"
               "\t1. Névjegyek\n"
               "\t2. Névjegy hozzáadása\n"
               "\t3. Névjegy törlése\n"
               "\t4. Névjegy módosítása\n"
               "\t5. Keresés\n"
               "\t6. vCard importálása/exportálása\n"
               "\t7. Kilépés (vagy #)\n"
               "Írja be a választott menüpont számát!\n"
               "A programban ahány # karakter van, annyi menüpontot fog visszalépni!\n");
        do  {
            hamis_karakter = false;
            if(scanf("%d", &input)  != 1) {
                scanf(" %c", &in_char);
                while(getchar() != '\n');
                if(in_char == '#')
                    kilep = true;
                else {
                    hamis_karakter = true;
                    while (getchar() != '\n');
                }
            }
            if (input >= '1' && input <= '7' | kilep == true || hamis_karakter ) {
                printf("Érvénytelen menüpont!\n");
            }
        } while (input >= '1' && input <= '7' | kilep == true || hamis_karakter );

        if(kilep == false && input != '7') { //ha kilép, nem nézzük melyik menüpontot választja!
            while(getchar() != '\n');
            switch (input) {
                case 1:
                    nevjegyek_almenu(adatok);
                    break;
                case 2:
                    nevjegy_hozzaadasa_programbol(adatok,fajlnev);
                    break;
                case 3:
                    nevjegy_torlese_programbol(adatok, fajlnev);
                    break;
                case 4:
                    nevjegy_modositasa(adatok, fajlnev);
                    break;
                case 5:
                    kereses(adatok);
                    break;
                case 6:
                    adatok = vcard(adatok);
                    fajlba_ment(adatok,fajlnev);
                    break;
                default:
                    printf("Ismeretlen hiba történt");
                    break;
            }
        }
    } while (kilep != true && input != '7');

    lista_felszabaditasa(adatok);
    return 0;
}


