#include "errors.h"

int FileOpenError(FILE *file, char* nazwa){
    if(file == NULL){
        fprintf(stderr, "Błąd otwarcia pliku %s", nazwa);
        return 1;
    }else{
        return 0;
    }
}

int EntryError(FILE *file){
    char ch;
    
    int count = 0;

    while((ch = fgetc(file)) != EOF){
        if(ch == 'P'){
            count++;
        }
    }

    fseek(file, 0, SEEK_SET);

    if(count == 0 || count > 1){
        fprintf(stderr, "Plik jest uszkodzony - więcej niz jeden początek");
        return 1;
    }else{
        return 0;
    }
}
int ExitError(FILE *file){
    char ch;
    
    int count = 0;

    while((ch = fgetc(file)) != EOF){
        if(ch == 'K'){
            count++;
        }
    }
    fseek(file, 0, SEEK_SET);

    if(count == 0 || count > 1){
        fprintf(stderr, "Plik jest uszkodzony - więcej niz jeden koniec");
        return 1;
    }else{
        return 0;
    }
}

int invalidMaze(FILE *file){

    char ch;
    int kolumny=0;

    char prev_ch=0;

    int prev = -1;

    while((ch = fgetc(file)) != EOF){
        if(ch != '\n'){
            kolumny++;
        }else{
            if(prev != -1 && kolumny != prev && ch != EOF && prev_ch != '\n'){
                fprintf(stderr, "Plik uszkodzony - Jedna z linii posiada mniej znakow niz inne! - %d, %d", kolumny, prev);
                return 1;
            }
            prev = kolumny;
            kolumny = 0;
        }
        ch = prev_ch;
    }
    fseek(file, 0, SEEK_SET);
    return 0;
}
