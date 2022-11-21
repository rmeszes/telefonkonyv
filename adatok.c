//
// Created by rmesz on 2022. 11. 04..
//

#include "adatok.h"
#include "debugmalloc.h"
#define TESZT
/*
 * Besz�r egy �j n�vjegyet a list�ba, abc sorrend szerinti hely�re (n�v mez� alapj�n).
 */
Nevjegyek* uj_nevjegy(Nevjegyek* lista, char* nev, char* telefonszam, char* email) {
    Nevjegy *uj;
    uj = malloc(sizeof(Nevjegy));
    strcpy(uj->nev, nev);
    strcpy(uj->email, email);
    strcpy(uj->telefonszam, telefonszam);
    uj->id = ++lista->id;

    Nevjegy *mozgo = lista->elso->kov;

    while (strcmp(mozgo->nev, uj->nev) <= 0 && mozgo->kov != NULL) {
        mozgo = mozgo->kov;
    }

    uj->elozo = mozgo->elozo;
    uj->kov = mozgo;
    mozgo->elozo->kov = uj;
    mozgo->elozo = uj;
    return lista;
}

/*
 * L�trehoz egy Nevjegy elemet egy f�jlb�l beolvasott sorb�l (sztringb�l).
 */

static Nevjegy* uj_elem_fajlbol(const char* sor) {
    Nevjegy* uj = malloc(sizeof(Nevjegy));
    int mezo = 0;
    int sor_szamlalo = 0;
    int mezo_szamlalo = 0;
    while (mezo != 3){
        if(sor[sor_szamlalo] == ';') {
            mezo++;
            sor_szamlalo++;
            mezo_szamlalo = 0;
        }
        else {
            switch(mezo) {
                case 0:
                    uj->nev[mezo_szamlalo++] = sor[sor_szamlalo++];
                    uj->nev[mezo_szamlalo] = '\0';
                    break;
                case 1:
                    uj->telefonszam[mezo_szamlalo++] = sor[sor_szamlalo++];
                    uj->telefonszam[mezo_szamlalo] = '\0';
                    break;
                case 2:
                    uj->email[mezo_szamlalo++] = sor[sor_szamlalo++];
                    uj->email[mezo_szamlalo] = '\0';
                    break;
                default:
                    return NULL;
            }
        }
    }
    return uj;
}

/*
 * Visszat�r a beolvasott l�ncolt lista pointer�vel, amit a h�v�nak fel kell szabad�tani!
 */
Nevjegyek* fajlbol_beolvas(char* fajlnev) {
    Nevjegyek *nevjegyek = (Nevjegyek*) malloc(sizeof(Nevjegyek));
    nevjegyek->elso = (Nevjegy*) malloc(sizeof(Nevjegy));
    nevjegyek->utolso = (Nevjegy*) malloc(sizeof(Nevjegy));
    nevjegyek->elso->kov = nevjegyek->utolso;
    nevjegyek->utolso->elozo = nevjegyek->elso;
    nevjegyek->utolso->kov = NULL;
    nevjegyek->elso->elozo = NULL;
    nevjegyek->id = 0;

    FILE* fp;
    fp = fopen(strdup(fajlnev), "r");
    if(fp == NULL) {
        lista_felszabaditasa(nevjegyek);
        perror("Nem siker�lt a f�jl megnyit�sa! Ok");
        return NULL;
    }
#ifdef TESZT
    printf("Debug: A %s f�jl megnyit�sa siker�lt.\n", strdup(fajlnev));
#endif
    char buffer[641]; // 640 karakter lehet egy sorban a mez�k karakterlimitjei miatt
    while (fgets(buffer,641,fp) != NULL) {
        Nevjegy *temp;
        temp = uj_elem_fajlbol(buffer);
        uj_nevjegy(nevjegyek, temp->nev, temp->telefonszam, temp->email);
        free(temp);
    }

    fclose(fp);
    return nevjegyek;
}


/*
 * lista felszabad�t�s.
 */
void lista_felszabaditasa(Nevjegyek* lista) {
    Nevjegy *iter = lista->elso;
    while(iter != NULL) {
        Nevjegy *kov = iter->kov;
        free(iter);
        iter = kov;
    }
    free(lista);
}

static void nevjegyek_almenu(Nevjegy* nevjegy) {
    system("cls");

    printf("N�VJEGY\n"
           "\tN�v: %s\n"
           "\tTelefonsz�m: %s\n"
           "\tEmail c�m: %s\n"
           "Visszal�p�s a # karakter\n", nevjegy->nev, nevjegy->telefonszam, nevjegy->email);

    char input;

    scanf(" %c", &input);
    while (input != '#') {
        printf("�rv�nytelen bemenet!\n");
        while(getchar() != '\n');
        scanf(" %c", &input);
    }
}

void nevjegyek_kiir(Nevjegyek *lista) {
    Nevjegy *mozgo = lista->elso;
    int darab = 0;

    while(mozgo != NULL) {
        darab++;
        mozgo = mozgo->kov;
    }
    darab--;  //a kezd� str�zsa pointert bem�solom a t�mbbe, mert megegyszer�s�ti az indexel�st, viszont az utols�t nem.

    Nevjegy* elemek[darab];

    mozgo = lista->elso;

    for(int i = 0; mozgo->kov != NULL; i++) {
        elemek[i] = mozgo;
        mozgo = mozgo->kov;
    }

    int input;
    char in_char;
    bool kilep = false;
    bool hamis_karakter = false;
    do {
        system("cls");
        printf("N�VJEGYEK: (%d) Kil�p�s: #\n", darab-1);
        for (int i = 1; i < darab; i++) {
            printf("\t%d. %s\n", i, elemek[i]->nev);
        }
        do  {
            if(scanf("%d", &input)  != 1) {
                scanf(" %c", &in_char);
                while(getchar() != '\n');
                if(in_char == '#')
                    kilep = true;
                else
                    hamis_karakter = true;
            }
            if (!(input >= 1 && input <= darab || kilep) || hamis_karakter ) {
                printf("�rv�nytelen men�pont!\n");
                hamis_karakter = false;
            }
        } while (!(input >= 1 && input <= darab || kilep));

        if(kilep != true && input != darab) { //ha kil�p, nem n�zz�k melyik men�pontot v�lasztja!
            nevjegyek_almenu(elemek[input]);
        }
    } while (kilep != true && input != darab);
}