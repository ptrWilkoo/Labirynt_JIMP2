#include <stdlib.h>
#include <stdio.h>
#include "pliki.h"

int main(int argc, char **argv){

    FILE *plik = fopen("maze100.txt", "r");

    int powiekszonyWymiar = liczKolumny(plik);

    zapiszFragmentyDoPliku(plik, "plik", "folder", powiekszonyWymiar, 50);

    int kolumny = liczKolumny(plik);
    int wiersze = liczWiersze(plik);

    printf("wymiar: %d x %d\n", kolumny, wiersze);

    int n = kolumny * 50;

    char *wektor = malloc(n * sizeof(char));

    FILE *czesc = fopen("folder/plik1", "r");
    
    zPlikuDoWektora(czesc, wektor);

    for(int i=0; i<n; i++){
        printf("%c", wektor[i]);
        if((i+1) % kolumny == 0 && i != 0){
            printf("\n");
        }
    }
    
    fclose(plik);

    return 0;
}