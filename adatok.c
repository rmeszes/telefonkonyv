//
// Created by rmesz on 2022. 11. 04..
//
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "adatok.h"
#include "debugmalloc.h"
//#define TESZT

void nevjegy_torlese_listabol(Nevjegy* elem) {
    elem->elozo->kov = elem->kov;
    elem->kov->elozo = elem->elozo;
    free(elem);
}

bool fajlba_ment(Nevjegyek* lista, char* fajlnev) {
    FILE* fp;
    fp = fopen(fajlnev, "w");
    if (fp == NULL) {
        perror("Nem sikerült a fájlba mentés");
        printf("Továbblépés az Enter billentyûvel.");
        while (getchar() != '\n');
        return false;
    }
    Nevjegy *mozgo = lista->elso->kov;
    while (mozgo->kov != NULL) {
        fprintf(fp, "%s;%s;%s;\n", mozgo->nev, mozgo->telefonszam, mozgo->email);
        mozgo = mozgo->kov;
    }
    fclose(fp);
    return true;
}

/*
 * Beszúr egy új névjegyet a listába, abc sorrend szerinti helyére (név mezõ alapján).
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
 * Létrehoz egy Nevjegy elemet egy fájlból beolvasott sorból (sztringbõl).
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
 * Visszatér a beolvasott láncolt lista pointerével, amit a hívónak fel kell szabadítani!
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
    if (fp == NULL) {
        lista_felszabaditasa(nevjegyek);
        perror("Nem sikerült a fájl megnyitása! Ok");
        return NULL;
    }

#ifdef TESZT
    printf("Debug: A %s fájl megnyitása sikerült.\n", strdup(fajlnev));
#endif
    char buffer[641]; // 640 karakter lehet egy sorban a mezõk karakterlimitjei miatt
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
 * lista felszabadítás.
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

void nevjegyek_almenu(Nevjegyek* lista) {
    system("cls");
    Nevjegy *temp = nevjegyek_kiir(lista);
    if (temp == NULL) return;

    printf("NÉVJEGY\n"
           "\tNév: %s\n"
           "\tTelefonszám: %s\n"
           "\tEmail cím: %s\n"
           "Visszalépés # karakterrel\n", temp->nev, temp->telefonszam, temp->email);

    char input;

    scanf(" %c", &input);
    while (input != '#') {
        printf("Érvénytelen bemenet!\n");
        //while(getchar() != '\n');
        scanf(" %c", &input);
    }
}

Nevjegy* nevjegyek_kiir(Nevjegyek *lista) {
    Nevjegy *mozgo = lista->elso;
    int darab = 0;

    while(mozgo != NULL) {
        darab++;
        mozgo = mozgo->kov;
    }
    darab--;  //a kezdõ strázsa pointert bemásolom a tömbbe, mert megegyszerûsíti az indexelést, viszont az utolsót nem.

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
        printf("NÉVJEGYEK: (%d) Kilépés: #\n", darab-1);
        for (int i = 1; i < darab; i++) {
            printf("\t%d. %s\n", i, elemek[i]->nev);
        }
        do  {
            if(scanf("%d", &input)  != 1) {
                scanf(" %c", &in_char);
                if(in_char == '#')
                    kilep = true;
                else {
                    hamis_karakter = true;
                    while (getchar() != '\n');
                }
            }
            if (!(input >= 1 && input <= darab || kilep) || hamis_karakter ) {
                printf("Érvénytelen menüpont!\n");
                hamis_karakter = false;
            }
        } while (!(input >= 1 && input <= darab || kilep));

        if(kilep == false && input != darab) { //ha kilép, nem nézzük melyik menüpontot választja!
            return elemek[input];
        }
    } while (kilep == false && input != darab);
    return NULL;
}

void nevjegy_hozzaadasa_programbol(Nevjegyek *lista, char *fajlnev) {
    system("cls");
    printf("ÚJ NÉVJEGY HOZZÁADÁSA\n");
    printf("Név (maximum 300 karakter):");
    char nev[301];
    gets(nev);
    while (nev[0] == '\0') {
        printf("Kérlek írj be érvényes nevet.\n");
        gets(nev);
    }
    nev[0] = toupper(nev[0]);
    printf("Telefonszám (maximum 20 karakter):");
    char telefonszam[21];
    gets(telefonszam);
    while (telefonszam[0] == '\0') {
        printf("Kérlek írj érvényes telefonszámot.\n");
        gets(telefonszam);
    }
    printf("Email cím (maximum 320 karakter):");
    char email[321];
    gets(email);
    while (email[0] == '\0') {
        printf("Kérlek írj érvényes email címet.\n");
        gets(email);
    }
    uj_nevjegy(lista,nev,telefonszam,email);
    if(fajlba_ment(lista,fajlnev) == false) {
        Nevjegy *mozgo = lista->elso->kov;
        while (mozgo->id != lista->id) {
            mozgo = mozgo->kov;
        }
        nevjegy_torlese_listabol(mozgo);
    }
}

void nevjegy_torlese_programbol(Nevjegyek *lista, char *fajlnev) {
    system("cls");
    printf("NÉVJEGY TÖRLÉSE\n"
           "Válassza ki a törlendõ névjegyet!\n");
    Nevjegy* temp = nevjegyek_kiir(lista);
    if (temp != NULL) {
        nevjegy_torlese_listabol(temp);
        fajlba_ment(lista, fajlnev);
    }
}

void nevjegy_modositasa(Nevjegyek *lista, char *fajlnev) {
    system("cls");
    printf("NÉVJEGY MÓDOSÍTÁSA\n"
           "Válassza ki a módosítani való névjegyet!\n");
    Nevjegy* temp = nevjegyek_kiir(lista);
    if (temp != NULL) {
        while(getchar() != '\n');
        nevjegy_hozzaadasa_programbol(lista, fajlnev);
        nevjegy_torlese_listabol(temp);
        fajlba_ment(lista, fajlnev);
    }
}

bool strmatch(const char vizsgalando[], const char feltetel[])
{
    int vizsg_hossz = strlen(vizsgalando);
    int feltetel_hossz = strlen(feltetel);

    if (feltetel_hossz == 0)
        return (vizsg_hossz == 0); // üres feltétel, csak üres adattal lehetne egyenlõ

    bool eredmenyek[vizsg_hossz + 1][feltetel_hossz + 1]; //eredmények tárolására

    //feltöltés false-al
    for (int i = 0; i < vizsg_hossz + 1; ++i) {
        for (int j = 0; j < feltetel_hossz + 1; ++j) {
            eredmenyek[i][j] = false;
        }
    }
    eredmenyek[0][0] = true;

    for (int j = 1; j <= feltetel_hossz; j++)
        if (feltetel[j - 1] == '*')
            eredmenyek[0][j] = eredmenyek[0][j - 1];

    for (int j = 1; j <= feltetel_hossz; j++)
        if (feltetel[j - 1] == '*')
            eredmenyek[0][j] = eredmenyek[0][j - 1];


    for (int i = 1; i <= vizsg_hossz; i++) {
        for (int j = 1; j <= feltetel_hossz; j++) {

            if (feltetel[j - 1] == '*')
                eredmenyek[i][j]
                        = eredmenyek[i][j - 1] || eredmenyek[i - 1][j];
            else if (feltetel[j - 1] == '?'
                     || vizsgalando[i - 1] == feltetel[j - 1])
                eredmenyek[i][j] = eredmenyek[i - 1][j - 1];

                // If characters don't match
            else
                eredmenyek[i][j] = false;
        }
    }

    return eredmenyek[vizsg_hossz][feltetel_hossz];
}

static int kereses_darab(Nevjegyek* lista, int mezo, char *feltetel) {
    int darab = 1;
    Nevjegy *mozgo = lista->elso->kov;
    if (mezo == 1) {
        printf("Keresett név:");
        char input[301];
        gets(input);
        strcpy(feltetel, input);

        while (mozgo->kov != NULL) {
            if (strmatch(mozgo->nev, feltetel)) darab++;
            mozgo = mozgo->kov;
        }
    }
    else if (mezo == 2) {
        printf("Keresett telefonszám:");
        char input[20];
        gets(input);
        strcpy(feltetel, input);

        while (mozgo->kov != NULL) {
            if (strmatch(mozgo->telefonszam, feltetel)) darab++;
            mozgo = mozgo->kov;
        }
    }
    else {
        printf("Keresett email:");
        char input[321];
        gets(input);
        strcpy(feltetel, input);

        while (mozgo->kov != NULL) {
            if (strmatch(mozgo->email, feltetel)) darab++;
            mozgo = mozgo->kov;
        }
    }
    return darab;
}


static void kereso(Nevjegyek *source, int mezo, char *feltetel, Nevjegy** cel) {
    Nevjegy* mozgo = source->elso->kov;
    int cel_id = 1;
    if (mezo == 1) {
        while (mozgo->kov != NULL) {
            if (strmatch(mozgo->nev, feltetel)) {
                cel[cel_id++] = mozgo;
            }
            mozgo = mozgo->kov;
        }
    } else if (mezo == 2) {
        while (mozgo->kov != NULL) {
            if (strmatch(mozgo->telefonszam, feltetel)) {
                cel[cel_id++] = mozgo;
            }
            mozgo = mozgo->kov;
        }
    } else {
        while (mozgo->kov != NULL) {
            if (strmatch(mozgo->email, feltetel)) {
                cel[cel_id++] = mozgo;
            }
            mozgo = mozgo->kov;
        }
    }
}

static void kereses_almenu(Nevjegy* elem) {
    system("cls");
    printf("NÉVJEGY\n"
           "\tNév: %s\n"
           "\tTelefonszám: %s\n"
           "\tEmail cím: %s\n"
           "Visszalépés # karakterrel\n", elem->nev, elem->telefonszam, elem->email);

    char input;

    scanf(" %c", &input);
    while (input != '#') {
        printf("Érvénytelen bemenet!\n");
        //while(getchar() != '\n');
        scanf(" %c", &input);
    }
}

void kereses(Nevjegyek * lista) {
    system("cls");
    printf("Mi alapján szeretnél keresni?\n"
           "\t1. Név\n"
           "\t2. Telefonszám\n"
           "\t3. Email cím\n");
    int mezo;
    scanf("%d", &mezo);
    while (getchar() != '\n') {
        if (getchar() == '#') return;
    }
    while (mezo <= 1 & mezo >= 3) {
        printf("Érvénytelen menüpont!");
        scanf("%d", &mezo);
        while (getchar() != '\n') {
            if (getchar() == '#') return;
        }
    }
    system("cls");
    char feltetel[321];
    int db = kereses_darab(lista, mezo, feltetel);
    Nevjegy* talalatok[db];
    kereso(lista, mezo, feltetel, talalatok);
    system("cls");
    printf("KERESÉSI TALÁLATOK:\n");
    for (int i = 1; i < db; ++i) {
        printf("\t%d. %s\n", i, talalatok[i]->nev);
    }
    int valasztott;
    if (scanf("%d", &valasztott) == 1) {
        if (valasztott > 0 & valasztott <= db) {
            kereses_almenu(talalatok[valasztott]);
        }
    } else {
        while(getchar() != '\n');
    }
}