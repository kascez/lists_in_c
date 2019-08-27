//
//  main.c
//  listeMeni
//
//  Created by Zoran Kascelan on 08/05/2018.
//  Copyright © 2018 Zoran Kascelan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cvor *PCVOR;
typedef struct cvor {
    int podatak;
    PCVOR sledeci;
} CVOR;

void dodajNaKraj (PCVOR *glava, int podatak) {
    PCVOR novi = malloc(sizeof(int));
    PCVOR tek = *glava;
    
    novi->podatak = podatak;
    novi->sledeci = NULL;
    
    if (*glava == NULL) { //prvi element
        *glava = novi;
    } else {
        while (tek->sledeci != NULL) {
            tek = tek->sledeci;
        }
        tek->sledeci = novi;
    }
    return;
}

void dodajNaPocetak (PCVOR *glava, int podatak) {
    PCVOR novi = malloc(sizeof(int));
    novi->podatak = podatak;
    novi->sledeci = *glava;
    *glava = novi;
    
    return;
}

int brojElemenata (PCVOR glava) {
    int brojac = 0;
    PCVOR tek = glava;
    while (tek != NULL) {
        tek = tek->sledeci;
        brojac++;
    }
    return brojac;
}

void ubaciNaPoziciju (PCVOR *glava, int podatak) {
    int x;
    PCVOR tek = *glava;
    PCVOR pret = NULL;
    printf("Unesite poziciju na kojoj zelite unijeti novi element:\n");
    scanf("%d", &x);
    PCVOR novi = malloc(sizeof(int));
    if (x == 0) {
        dodajNaPocetak(glava, podatak);
    } else {
        while (x) {
            pret = tek;
            tek = tek->sledeci;
            x--;
        }
    }
    pret->sledeci = novi;
    novi->podatak = podatak;
    novi->sledeci = tek;
    
    return;
}

void izbaciPrviElement (PCVOR *glava) {
    PCVOR tek = *glava;
    if (*glava == NULL) {
        return;
    }
    *glava = (*glava)->sledeci;
    free(tek);
    
    return;
}

void izbaciSaKraja (PCVOR *glava) {
    PCVOR tek = *glava;
    PCVOR pret = tek;
    while (tek->sledeci != NULL) {
        pret = tek;
        tek = tek->sledeci;
    }
    pret->sledeci = NULL;
    free(tek);
    return;
}

void izbaciElementSaPozicije (PCVOR *glava) {
    int x;
    PCVOR tek = *glava;
    PCVOR pret = NULL;
    printf("Unesite poziciju elementa koji zelite izbaciti :(\n");
    scanf("%d", &x);
    if (x == 0) {
        printf("Imash funkciju izbrisi prvi element zasto smaras odje onda, al dobro ajde\n");
        izbaciPrviElement(glava);
    } else if (x >= brojElemenata(*glava)) {
        printf("Nemas tolko elemenata glibove\n");
    } else {
        while (x) {
            pret = tek;
            tek = tek->sledeci;
            x--;
        }
        pret->sledeci = tek->sledeci;
        tek->sledeci = NULL;
        free(tek);
    }
    
    return;
}

void izbaciElementSaZadatomVrijednoscu (PCVOR *glava) {
    PCVOR tek = *glava;
    PCVOR sled = malloc(sizeof(CVOR));
    PCVOR pom = malloc(sizeof(CVOR));
    int x;
    printf("Unesite koji element zelite obrisati:\n");
    scanf("%d", &x);
    if (*glava == NULL) {
        printf("Lista je prazna\n");
        return;
    }
    while (tek->podatak == x) {
        pom = tek;
        *glava = tek->sledeci;
        tek = tek->sledeci;
        free(pom);
    }
    while (tek->sledeci != NULL) {
        sled = tek->sledeci;
        if (sled->podatak == x) {
            tek->sledeci = sled->sledeci;
            free(sled);
        } else {
            tek = tek->sledeci;
        }
    }
    return;
}

void izbaciParne (PCVOR *glava) {
    PCVOR tek = *glava;
    PCVOR sled = malloc(sizeof(CVOR));
    if (*glava == NULL) {
        printf("Lista je prazna\n");
        return;
    }
    while (tek->podatak % 2 == 0) {
        *glava = tek->sledeci;
        tek = tek->sledeci;
    }
    while (tek->sledeci != NULL) {
        if (tek->sledeci->podatak % 2 == 0) {
            sled = tek->sledeci;
            tek->sledeci = sled->sledeci;
            free(sled);
        } else {
            tek = tek->sledeci;
        }
    }
    return;
}

void izbaciNeparne (PCVOR *glava) {
    PCVOR tek = *glava;
    PCVOR sled = malloc(sizeof(CVOR));
    if (*glava == NULL) {
        printf("Lista je prazna\n");
        return;
    }
    while (tek->podatak % 2 == 1) {
        *glava = tek->sledeci;
        tek = tek->sledeci;
    }
    while (tek->sledeci != NULL) {
        if (tek->sledeci->podatak % 2 == 1) {
            sled = tek->sledeci;
            tek->sledeci = sled->sledeci;
            free(sled);
        } else {
            tek = tek->sledeci;
        }
    }
    return;
}

void unistiListu (PCVOR *glava) {
    int br = brojElemenata(*glava);
    int i;
    PCVOR tek;
    for (i = br; i > 0; i--) {
        tek = *glava;
        *glava = (*glava)->sledeci;
        free(tek);
    }
    return;
}

void unesiListu (PCVOR *glava) {
    int opet = 1;
    int podatak;
    while (opet != 0) {
        printf("Koji element zelite da unesete u listu?\n");
        scanf("%d", &podatak);
        dodajNaKraj(glava, podatak);
        printf("Opet? 0 - ne\n");
        scanf("%d", &opet);
    }
    return;
}

void prikazListe(PCVOR glava) {
    PCVOR tekuci = glava;
    printf("Elementi liste su:\n");
    while (tekuci != NULL) {
        printf("%d\t", tekuci->podatak);
        tekuci = tekuci->sledeci;
    }
    printf("\n");
    
    return;
}

double srednjaVrijednost(PCVOR glava) {
    PCVOR tek = glava;
    int suma = 0;
    int brojac = 0;
    double as = 0;
    while (tek != NULL) {
        brojac++;
        suma = suma + tek->podatak;
        tek = tek->sledeci;
    }
    as = (double)suma/brojac;
    
    return as;
}

void prikaziParne(PCVOR glava) {
    PCVOR tek = glava;
    printf("Parni elementi liste su:\n");
    while (tek != NULL) {
        if (tek->podatak % 2 == 0) {
            printf("%d\t", tek->podatak);
        }
        tek = tek->sledeci;
    }
    printf("\n");
    
    return;
}

void prikaziNeparne(PCVOR glava) {
    PCVOR tek = glava;
    printf("Neparni elementi liste su:\n");
    while (tek != NULL) {
        if (tek->podatak % 2 == 1) {
            printf("%d\t", tek->podatak);
        }
        tek = tek->sledeci;
    }
    printf("\n");
    
    return;
}


void sortirani (PCVOR glava) {
    PCVOR tek = glava;
    PCVOR pret = NULL;
    while (tek->sledeci != NULL) {
        pret = tek;
        tek = tek->sledeci;
        if ((pret->podatak) > (tek->podatak) ) {
            printf("Nisu sortirani\n");
            return;
        }
    }
    printf("Sortirani su\n");
    return;
}

void sortiraniOpadajuce (PCVOR glava) {
    PCVOR tek = glava;
    PCVOR pret = NULL;
    while (tek->sledeci != NULL) {
        pret = tek;
        tek = tek->sledeci;
        if ((pret->podatak) < (tek->podatak) ) {
            printf("Nisu sortirani\n");
            return;
        }
    }
    printf("Sortirani su\n");
    return;
}

void frekvencijaaa(PCVOR glava) {
    int n;
    int brojac = 0;
    PCVOR tek = glava;
    printf("Unesite za koji element zelite provjeriti koliko puta se ponavlja u listi:\n");
    scanf("%d", &n);
    while (tek != NULL) {
        if (tek->podatak == n) {
            brojac++;
        }
        tek = tek->sledeci;
    }
    printf("Frekvencija elementa %d je -> %d\n", n, brojac);
}


void prikazVeciOdSrednje (PCVOR glava) {
    double sv = srednjaVrijednost(glava);
    PCVOR tek = glava;
    printf("Elementi liste, veci od srednje vrijednosti %.2lf, su:\n", sv);
    while (tek != NULL) {
        if (tek->podatak > sv) {
            printf("%d\t", tek->podatak);
        }
        tek = tek->sledeci;
    }
    printf("\n");
    
    return;
}

int frekvencija (PCVOR glava, int n) {
    int brojac = 0;
    PCVOR tek = glava;
    while (tek != NULL) {
        if (tek->podatak == n) {
            brojac++;
        }
        tek = tek->sledeci;
    }
    return brojac;
}

int provjera (PCVOR glava, int poz, int x) {
    PCVOR tek = glava;
    while (poz) {
        if (tek->podatak == x) {
            return 1;
        }
        poz--;
        tek = tek->sledeci;
    }
    return 0;
}

void prikazPojavljivanja (PCVOR glava) {
    PCVOR tek = glava;
    int brojac = 0;
    printf("Prikaz broja pojavljivanja svakog elementa:\n");
    while (tek != NULL) {
        if (provjera(glava, brojac, tek->podatak) == 0) {
            printf("Broj pojavljivanja elementa %d je %d\n", tek->podatak, frekvencija(glava, tek->podatak));
        }
        brojac++;
        tek = tek->sledeci;
    }
    return;
}

void sortiranjeListe (PCVOR glava) {
    PCVOR tek;
    PCVOR sled;
    int promjena;
    
    tek = glava;
    while (tek != NULL) {
        sled = tek->sledeci;
        while (sled != NULL) {
            if (tek->podatak > sled->podatak) {
                promjena = sled->podatak;
                sled->podatak = tek->podatak;
                tek->podatak = promjena;
            }
            sled = sled->sledeci;
        }
        tek = tek->sledeci;
    }
    printf("Elementi liste su sada sortirani.\n");
    return;
}

void sortiranjeListeObrnuto (PCVOR glava) {
    PCVOR tek;
    PCVOR sled;
    int promjena;
    
    tek = glava;
    while (tek != NULL) {
        sled = tek->sledeci;
        while (sled != NULL) {
            if (tek->podatak < sled->podatak) {
                promjena = sled->podatak;
                sled->podatak = tek->podatak;
                tek->podatak = promjena;
            }
            sled = sled->sledeci;
        }
        tek = tek->sledeci;
    }
    printf("Elementi liste su sada sortirani.\n");
    return;
}


void meni(void) {
    PCVOR glava = NULL;
    int opcija;
    int opcija1;
    int opcija2;
    int opcija3;
    int opcija4;
    int x;
    do {
        printf("**********MENI**********\n");
        printf("1. Kreiraj listu\n");
        printf("2. Unisti listu\n");
        printf("3. Ubaci . . .\n");
        printf("4. Izbaci . . .\n");
        printf("5. Prikazi . . .\n");
        printf("6. Sortiranje . . .\n");
        printf("7. Prikazi broj pojavljivanja svakog elementa\n");
        printf("0. Kraj\n");
        printf("Izaberite opciju:\n");
        scanf("%d", &opcija);
        switch (opcija) {
            case 1:
                unesiListu(&glava);
                printf("Lista je unesena!\n");
                break;
            
            case 2:
                unistiListu(&glava);
                printf("Lista je unistena!\n");
                break;
            
            case 3:
                do {
                    printf("3.1. Ubaci na pocetak\n");
                    printf("3.2. Ubaci na kraj\n");
                    printf("3.3. Ubaci na zadatu poziciju\n");
                    printf("0. Povratak u glavni meni\n");
                    printf("Unesite opciju:\n");
                    scanf("%d", &opcija1);
                    switch (opcija1) {
                        case 1:
                            printf("Unesite koji broj zelite unijeti na pocetak:\n");
                            scanf("%d", &x);
                            dodajNaPocetak(&glava, x);
                            printf("Element je dodat!\n");
                            break;
                        
                        case 2:
                            printf("Unesite koji broj zelite unijeti na kraj:\n");
                            scanf("%d", &x);
                            dodajNaKraj(&glava, x);
                            printf("Element je dodat!\n");
                            break;
                        
                        case 3:
                            printf("Unesite koji element zelite unijeti na zadatu poziciju:\n");
                            scanf("%d", &x);
                            ubaciNaPoziciju(&glava, x);
                            printf("Element je dodat!\n");
                            break;
                            
                        case 0:
                            opcija1 = -1;
                            break;
                        
                        default:
                            printf("Unijeli ste pogresnu opciju:\n");
                            break;
                    }
                } while (opcija1 != -1);
                break;
                
            case 4:
                do {
                    printf("4.1. Izbaci sa pocetka\n");
                    printf("4.2. Izbaci sa kraja\n");
                    printf("4.3. Izbaci sa zeljene pozicije\n");
                    printf("4.4. Izbaci element sa zeljenom vrijednoscu\n");
                    printf("4.5. Izbaci parne elemente\n");
                    printf("4.6. Izbaci neparne elemente\n");
                    printf("0. Povratak u glavni meni\n");
                    printf("Unesite opciju:\n");
                    scanf("%d", &opcija2);
                    switch (opcija2) {
                        case 1:
                            izbaciPrviElement(&glava);
                            printf("Element je izbacen!\n");
                            break;
                            
                        case 2:
                            izbaciSaKraja(&glava);
                            printf("Element je izbacen!\n");
                            break;
                            
                        case 3:
                            izbaciElementSaPozicije(&glava);
                            printf("Element je izbacen!\n");
                            break;
                            
                        case 4:
                            izbaciElementSaZadatomVrijednoscu(&glava);
                            printf("Element je izbacen!\n");
                            break;
                            
                        case 5:
                            izbaciParne(&glava);
                            printf("Elementi su izbaceni!\n");
                            break;
                            
                        case 6:
                            izbaciNeparne(&glava);
                            printf("Elementi su izbaceni!\n");
                            break;
                            
                        case 0:
                            opcija2 = -1;
                            break;
                            
                        default:
                            printf("Unijeli ste pogresnu opciju:\n");
                            break;
                    }
                } while (opcija2 != -1);
                break;
                
            case 5:
                do {
                    printf("5.1. Prikaz svih elemenata\n");
                    printf("5.2. Prikaz parnih elemenata\n");
                    printf("5.3. Prikaz neparnih elemenata\n");
                    printf("5.4. Prikaz elemenata koji su veci od srednje vrijednosti svih\n");
                    printf("0. Povratak u glavni meni\n");
                    printf("Unesite opciju:\n");
                    scanf("%d", &opcija3);
                    switch (opcija3) {
                        case 1:
                            prikazListe(glava);
                            break;
                            
                        case 2:
                            prikaziParne(glava);
                            break;
                            
                        case 3:
                            prikaziNeparne(glava);
                            break;
                            
                        case 4:
                            prikazVeciOdSrednje(glava);
                            break;
                            
                        case 0:
                            opcija3 = -1;
                            break;
                            
                        default:
                            printf("Unijeli ste pogresnu opciju:\n");
                            break;
                    }
                } while (opcija3 != -1);
                break;
                
            case 6:
                do {
                    printf("6.1. Provjeri da li su sortirani u rastucem redoslijedu\n");
                    printf("6.2. Provjeri da li su sortirani u opadajucem redoslijedu\n");
                    printf("6.3. Sortiraj elemente liste u rastucem redoslijedu\n");
                    printf("6.4. Sortiraj elemente liste u opadajucem redoslijedu\n");
                    printf("0. Povratak u glavni meni\n");
                    printf("Unesite opciju:\n");
                    scanf("%d", &opcija4);
                    switch (opcija4) {
                        case 1:
                            sortirani(glava);
                            break;
                            
                        case 3:
                            sortiranjeListe(glava);
                            break;
                            
                        case 4:
                            sortiranjeListeObrnuto(glava);
                            break;
                            
                        case 0:
                            opcija4 = -1;
                            
                        default:
                            printf("Unijeli ste pogresnu opciju:\n");
                            break;
                    }
                } while (opcija4 != -1);
                
            case 7:
                prikazPojavljivanja(glava);
                break;
                
            case 0:
                printf("Zbogom\n");
                opcija = -1;
                break;
            
            default:
                printf("Unijeli ste pogresnu opciju\n");
                break;
        }
    } while (opcija != -1);
        
    return;
}

int main() {
    meni();
    
    return 0;
}
