#include "input.h"
#include "solver.h"
#include "output.h"

int main(int argc, char **argv){

    FILE *bin = fopen("maze.bin", "rb"); // argv

    binaryToText(bin);

    fclose(bin);

    FILE *in = fopen("maze.txt", "r");

    int kolumny = (liczKolumny(in)-1)/2;
    int wiersze = (liczWiersze(in))/2;
    printf("%d - %d\n", kolumny, wiersze);
    int ilosclinii = 16;

    create_folder_and_split_file(in, ilosclinii);
    
    char labirynt[2*ilosclinii][2*kolumny+1];
    
    deadEndKill2(2*wiersze+1, 2*kolumny+1, ilosclinii, labirynt);

    //printPliki( (((2*wiersze)-((2*wiersze)%ilosclinii))/ilosclinii)+1, wiersze, kolumny, ilosclinii );

    pathFinder(wiersze, kolumny, ilosclinii, labirynt);
    
    delete_folder_recursively("pliki");
}