#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif


#include "debugmalloc.h"
#include "adatok.h"


int main(int argc, char **argv) {
#ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
#endif
    //f�jln�v ellen�rz�se/bek�r�se
    char fajlnev[101];
    if (argc > 1) {
        strcpy(fajlnev,argv[1]);
    }
    else {
        printf("A megnyitand� f�jl neve: (maximum 100 karakter!)\n");
        gets(fajlnev);
    }
    Nevjegyek *adatok = fajlbol_beolvas(fajlnev);
    if (adatok == NULL) {
        printf("Nyomj meg egy gombot a programb�l val� kil�p�shez!\n");
        getchar();
        return 0;
    }

    char input;
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
               "�rja be a v�lasztott men�pont sz�m�t!\n");
        do  {
            scanf(" %c", &input);
            //while (getchar() == '\n');
            if (!(input >= '1' && input <= '7' || input == '#'))
                printf("�rv�nytelen men�pont!");
        } while (!(input >= '1' && input <= '7' || input == '#'));

        if(input != '#' && input != '7') { //ha kil�p, nem n�zz�k melyik men�pontot v�lasztja!
            switch (input) {
                case '1':
                    nevjegyek_kiir(adatok);
                    break;
                case '2':
                    //nevjegy_hozzaadasa_programbol();
                    break;
                case '3':
                    //nevjegy_torlese_programbol();
                    break;
                case '4':
                    //nevjegy_modositasa();
                    break;
                case '5':
                    //kereses();
                    break;
                case '6':
                    //vcard();
                    break;
                default:
                    printf("Ismeretlen hiba t�rt�nt");
                    break;
            }
        }
    } while (input != '#' && input != '7');

#ifdef TESZT_LISTA
    //ki�rja a lista elemeit, ha teszt-k�nt van �p�tve a program
    Nevjegy* mozgo = adatok->elso->kov;
    printf("Debug: A lista elemei:\n");
    while (mozgo->kov != NULL) {
        printf("ID: %d\n", mozgo->id);
        printf("//\tN�v: %s\n//\tTelefonsz�m: %s\n//\tEmail: %s\n", mozgo->nev, mozgo->telefonszam, mozgo->email);
        printf("\n");
        mozgo = mozgo->kov;
    }
#endif
    lista_felszabaditasa(adatok);

    printf("Nyomj meg egy gombot a programb�l val� kil�p�shez!\n");
    getchar();
    return 0;
}
