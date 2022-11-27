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
        printf("A megnyitand� f�jl neve: (maximum 1000 karakter!)\n");
        gets(fajlnev);
    }
    Nevjegyek *adatok = fajlbol_beolvas(fajlnev); //!<A f� adatt�rol�ja a programnak. Ide olvassa be a n�vjegyeket �s ezzel v�gez el minden m�veletet.
    if (adatok == NULL) {
        printf("Nyomj meg egy gombot a programb�l val� kil�p�shez!\n");
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
        printf("MEN�\n"
               "\t1. N�vjegyek\n"
               "\t2. N�vjegy hozz�ad�sa\n"
               "\t3. N�vjegy t�rl�se\n"
               "\t4. N�vjegy m�dos�t�sa\n"
               "\t5. Keres�s\n"
               "\t6. vCard import�l�sa/export�l�sa\n"
               "\t7. Kil�p�s (vagy #)\n"
               "�rja be a v�lasztott men�pont sz�m�t!\n"
               "A programban ah�ny # karakter van, annyi men�pontot fog visszal�pni!\n");
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
                printf("�rv�nytelen men�pont!\n");
            }
        } while (input >= '1' && input <= '7' | kilep == true || hamis_karakter );

        if(kilep == false && input != '7') { //ha kil�p, nem n�zz�k melyik men�pontot v�lasztja!
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
                    printf("Ismeretlen hiba t�rt�nt");
                    break;
            }
        }
    } while (kilep != true && input != '7');

    lista_felszabaditasa(adatok);
    return 0;
}


