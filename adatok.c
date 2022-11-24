//
// Created by rmesz on 2022. 11. 04..
//

#include "adatok.h"
#include "debugmalloc.h"
//#define TESZT

void nevjegy_torlese_listabol(Nevjegy* elem) {
    elem->elozo->kov = elem->kov;
    elem->kov->elozo = elem->elozo;
    free(elem);
}

void fajlba_ment(Nevjegyek* lista, char* fajlnev) {
    Nevjegy *mozgo = lista->elso->kov;
    for(int i = 1; mozgo->id != lista->id; i++) {
        mozgo = mozgo->kov;
    }
    FILE* fp;
    fp = fopen(fajlnev, "a");
    if (fp == NULL) {
        nevjegy_torlese_listabol(mozgo);
        perror("Nem sikerült a fájlba mentés");
        printf("Továbblépés az Enter billentyûvel.");
        while (getchar() != '\n');
        return;
    }
    fprintf(fp, "%s;%s;%s;\n", mozgo->nev, mozgo->telefonszam, mozgo->email);
    fclose(fp);
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
    if(fp == NULL) {
        fp = fopen(strdup(fajlnev), "w");
        if (fp == NULL) {
            lista_felszabaditasa(nevjegyek);
            perror("Nem sikerült a fájl megnyitása! Ok");
            return NULL;
        }
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
        system("cls");
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
    printf("Telefonszám (maximum 20 karakter):");
    char telefonszam[21];
    gets(telefonszam);
    printf("Email cím (maximum 320 karakter):");
    char email[321];
    gets(email);
    uj_nevjegy(lista,nev,telefonszam,email);
    fajlba_ment(lista,fajlnev);
}

void nevjegy_torlese_programbol(Nevjegyek *lista, char *fajlnev) {
    system("cls");
    printf("NÉVJEGY TÖRLÉSE\n"
           "Válassza ki a törlendõ névjegyet!\n");
    //TODO: nevjegy_torlese_fajlbol
    Nevjegy* temp = nevjegyek_kiir(lista);
    if (temp != NULL)nevjegy_torlese_listabol(temp);
}