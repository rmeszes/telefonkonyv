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
    //fájlnév ellenõrzése/bekérése
    char fajlnev[101];
    if (argc > 1) {
        strcpy(fajlnev,argv[1]);
    }
    else {
        printf("A megnyitandó fájl neve: (maximum 100 karakter!)\n");
        gets(fajlnev);
    }
    Nevjegyek *adatok = fajlbol_beolvas(fajlnev);
    if (adatok == NULL) {
        printf("Nyomj meg egy gombot a programból való kilépéshez!\n");
        getchar();
        return 0;
    }

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
            Nevjegy* temp;
            switch (input) {
                case 1:
                    temp = nevjegyek_kiir(adatok);
                    if (temp != NULL) nevjegyek_almenu(temp);
                    break;
                case 2:
                    nevjegy_hozzaadasa_programbol(adatok,fajlnev);
                    break;
                case 3:
                    //nevjegy_torlese_programbol();
                    break;
                case 4:
                    //nevjegy_modositasa();
                    break;
                case 5:
                    //kereses();
                    break;
                case 6:
                    //vcard();
                    break;
                default:
                    printf("Ismeretlen hiba történt");
                    break;
            }
        }
    } while (kilep != true && input != '7');

#ifdef TESZT_LISTA
    //kiírja a lista elemeit, ha teszt-ként van építve a program
    Nevjegy* mozgo = adatok->elso->kov;
    printf("Debug: A lista elemei:\n");
    while (mozgo->kov != NULL) {
        printf("ID: %d\n", mozgo->id);
        printf("//\tNév: %s\n//\tTelefonszám: %s\n//\tEmail: %s\n", mozgo->nev, mozgo->telefonszam, mozgo->email);
        printf("\n");
        mozgo = mozgo->kov;
    }
#endif
    lista_felszabaditasa(adatok);
    return 0;
}
