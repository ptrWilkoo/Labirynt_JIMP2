#include "pliki.h"

void zapiszFragmentyDoPliku(FILE *oryginalnyLabirynt, char nazwaPlikow[20], char nazwaFolderu[10], int ileWszystkichLinii, int ileWJednymPliku){
    fseek(oryginalnyLabirynt, 0, SEEK_SET);
    mkdir(nazwaFolderu, 0777);

    int wskaznik = 2;
    int licznikPlikow = 0;
    char nazwaPliku[20];
    int ch;

    while(wskaznik < ileWszystkichLinii-1){
        wskaznik--;
        licznikPlikow++;
        int obecnaLinia = 1;

        sprintf(nazwaPliku, "%s/%s%d", nazwaFolderu, nazwaPlikow, licznikPlikow);
        FILE *wyjscie = fopen(nazwaPliku, "w");

        while(obecnaLinia < wskaznik && (ch = fgetc(oryginalnyLabirynt)) != EOF){
            if(ch == '\n') obecnaLinia++;
        }

        while(obecnaLinia < wskaznik + ileWJednymPliku && (ch = fgetc(oryginalnyLabirynt)) != EOF){
            if(ch == '\n'){
                obecnaLinia++;
                fprintf(wyjscie, "\n");
                continue;
            }
        fprintf(wyjscie, "%c", (char)ch);
    }
        fclose(wyjscie);
        wskaznik += ileWJednymPliku;
        fseek(oryginalnyLabirynt, 0, SEEK_SET);
    }
}

void zPlikuDoWektora(FILE *plik, char *wektor){

    int ch;
    int i = 0;

    while( (ch = fgetc(plik) ) != EOF){
        if(ch == '\n'){
            continue;
        }
        wektor[i++] = (char)ch;
    }
}

int liczKolumny(FILE *plik){
    fseek(plik, 0, SEEK_SET);
    
    int liczbaKolumn = 0;
    int ch;

    while( (ch = fgetc(plik) ) != EOF && ch != '\n'){
        liczbaKolumn++;
    }

    return liczbaKolumn;
}

int liczWiersze(FILE *plik){
    fseek(plik, 0, SEEK_SET);

    int liczbaWierszy = 0;
    int ch;

    while((ch = fgetc(plik)) != EOF){
            if(ch == '\n') liczbaWierszy++;
    }
    return liczbaWierszy;
}