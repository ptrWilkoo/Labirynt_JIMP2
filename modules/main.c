#include "input.h"
#include "solver.h"
#include "output.h"
#include "errors.h"

int main(int argc, char **argv){
    int opt;
    FILE *in = NULL;
    FILE *bin = NULL;
    const int ilosclinii = 16;

    int tflag = 0;
    int bflag = 0;
    
    if(argc<2){
        fprintf(stderr, "Brak parametrow wywolania!\n\n");
        fprintf(stderr, "\nSposób wywołania:\n%s -t <Nazwa Pliku>\nW przypadku pliku tekstowego\n\n./a.out -b <Nazwa Plik>\nW przypadku pliku binarnego\n\n", argv[0]);
        return 102;

    }

    while ((opt = getopt(argc, argv, "t:b:")) != -1) {
        switch (opt) {
        case 't':
            tflag = 1;
            break;
        case 'b':
            bflag = 1;
            break;
        default:
            fprintf(stderr, "\nSposób wywołania:\n%s -t <Nazwa Pliku>\nW przypadku pliku tekstowego\n\n./a.out -b <Nazwa Pliku\nW przypadku pliku binarnego\n\n>", argv[0]);
            return 102;
        }
    }

    if(tflag == 1 && bflag == 1){
        fprintf(stderr, "Mozesz wybrać tylko jeden tryb wczytywania na raz - binarny lub tekstowy\n");
        return 102;
    }
    if(tflag == 0 && bflag == 0){
        fprintf(stderr, "Musisz wprowdzić flagę rodzaju pliku wejsciowego (-b lub -t)\n");
        return 102;
    }

    if(tflag == 1){
        in = fopen(argv[2], "rt");
        if(FileOpenError(in, argv[2])){
            return 101;
        }

        create_folder_and_split_file(argv[2], ilosclinii);
    }
    if(bflag == 1){
        bin = fopen(argv[2], "rb");
        if(FileOpenError(bin, argv[2])){
            return 101;
        }

        binaryToText(bin);

        in = fopen("maze.txt", "rt");
        if(FileOpenError(in, argv[2])){
            return 101;
        }

        create_folder_and_split_file("maze.txt", ilosclinii);
    }

    if(ExitError(in)){
        delete_folder_recursively("pliki");
        return 103;
    }
    if(EntryError(in)){
        delete_folder_recursively("pliki");
        return 103;
    }
    if(invalidMaze(in)){
        delete_folder_recursively("pliki");
        return 103;
    }

    int kolumny = (liczKolumny(in))/2;
    int wiersze = (liczWiersze(in))/2;
    char labirynt[2*ilosclinii][2*kolumny+1];
    printf("Wymiar labiryntu: %d x %d\n", wiersze, kolumny);


    printf("Trwa rozwiązywanie labiryntu...\n");
    deadEndKill(2*wiersze+1, 2*kolumny+1, ilosclinii, labirynt);

    int steps = 0;
    pathFind(2*wiersze+1, 2*kolumny+1, ilosclinii, labirynt, &steps);
    //printf("kroki - %d\n", steps);

    if(tflag == 1){
        outputFromText(in, &steps);
    }
    if(bflag == 1){
        outputFromBinary(bin, &steps);
    }

    delete_folder_recursively("pliki");
    fclose(in);
    fclose(bin);
}