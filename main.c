#include "input.h"
#include "solver.h"
#include "output.h"

int main(int argc, char **argv){
    int opt;
    FILE *in = NULL;
    FILE *bin = NULL;
    const int ilosclinii = 16;
    
    while ((opt = getopt(argc, argv, "t:b:")) != -1) {
        switch (opt) {
        case 't':
            in = fopen(argv[2], "rt");
            create_folder_and_split_file(argv[2], ilosclinii);
            break;
        case 'b':
            bin = fopen(argv[2], "rb");
            binaryToText(bin);
            in = fopen("maze.txt", "rt");
            create_folder_and_split_file("maze.txt", ilosclinii);
            break;
        default:
            fprintf(stderr, "\nSposób wywołania:\n./a.out -t <Nazwa Pliku>\nW przypadku pliku tekstowego\n\n./a.out -b <Nazwa Pliku\nW przypadku pliku binarnego\n\n>");
            exit(EXIT_FAILURE);
        }
    }

    int kolumny = (liczKolumny(in)-1)/2;
    int wiersze = (liczWiersze(in))/2;
    //printf("%d - %d\n", kolumny, wiersze);
    
    

    char labirynt[2*ilosclinii][2*kolumny+1];
    
    deadEndKill2(2*wiersze+1, 2*kolumny+1, ilosclinii, labirynt);

    pathFinder(2*kolumny+1, ilosclinii, labirynt);
    
    // GETOPT NIE DZIAŁA DLA OPCJI BINARNEJ, BEZ GETOPTA JEST OK, NWM CZEMU TUTAJ NIE DZIALA
    // makefile nie dziala
    
    //binaryOutput(bin); // dziala tylko, jesli na wejsciu dostajemy binarny (kopiuje z niego poczatek, dopisuje sciezke)
    // trzeba jeszcze zapisac do binarnego, jesli dostajemy tylko .txt (TRUDNE), do zrobienia
    
    /*
        - najkrotsza sciezka
        - poprawic sciezke binarną
        - napisac binarny output, kiedy nie dostejemy binarnego (caly labirynt i jego parametry z .txt do .bin)
        - błędy wg dokumentacji
        


    */


    delete_folder_recursively("pliki");
    fclose(in);
    fclose(bin);
}
