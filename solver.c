#include "solver.h"

void printPliki(int numFiles, int lw, int lk, int lwp) {

    char filename[30]; // zakładam, że nazwa pliku nie przekroczy 20 znaków (plik_999999.txt)
    FILE *file;

    for (int i = 1; i <= numFiles-1; ++i) {
        // Tworzenie nazwy pliku
        snprintf(filename, sizeof(filename), "pliki/plik_%d.txt", i);

        // Otwarcie pliku
        file = fopen(filename, "r");
        if (file == NULL) {
            perror("Błąd otwarcia pliku");
            exit(EXIT_FAILURE);
        }

        // Wypisywanie zawartości pliku na stdout
        int c;
        while ((c = fgetc(file)) != EOF) {
            printf("%c", c);
        }

        // Zamknięcie pliku
        fclose(file);
    }
    
    
    snprintf(filename, sizeof(filename), "pliki/plik_%d.txt", numFiles);
    // Otwarcie pliku
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Błąd otwarcia pliku");
        exit(EXIT_FAILURE);
    }

    int pom;
    pom = ((((2*lw)+1) - ((numFiles-1)*lwp)) * ((2*lk)+2));
    
    // Wypisywanie zawartości pliku na stdout
    for (int i = 0; i < pom; i++) {
        printf("%c", fgetc(file));
    }
    
    // Zamknięcie pliku
    fclose(file);
}


void create_folder_and_split_file(const char *input_file, int lwp) {
    FILE *input_fp = fopen(input_file, "r");
    if (input_fp == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    // Create a folder to store new files
    char folder_name[] = "pliki";
    if (mkdir(folder_name, 0777) == -1) {
        perror("Error creating folder");
        exit(EXIT_FAILURE);
    }

    char output_file[MAX_LINE_LENGTH];
    int file_count = 1;
    FILE *output_fp = NULL;
    int line_count = 0;

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, input_fp) != NULL) {
        // Open new output file if needed
        if (line_count % lwp == 0) {
            if (output_fp != NULL) {
                fclose(output_fp);
            }
            sprintf(output_file, "%s/plik_%d.txt", folder_name, file_count++);
            output_fp = fopen(output_file, "w");
            if (output_fp == NULL) {
                perror("Error creating output file");
                exit(EXIT_FAILURE);
            }
        }

        // Write line to output file
        fputs(line, output_fp);
        line_count++;
    }

    // Close last output file
    if (output_fp != NULL) {
        fclose(output_fp);
    }

    // Close input file
    fclose(input_fp);
}


void delete_folder_recursively(const char *folder_path) {
    DIR *dir = opendir(folder_path);
    if (dir == NULL) {
        perror("Error opening folder");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", folder_path, entry->d_name);
        if (entry->d_type == DT_DIR) {
            delete_folder_recursively(path);
        } else {
            if (remove(path) != 0) {
                perror("Error deleting file");
            }
        }
    }
    closedir(dir);

    if (rmdir(folder_path) != 0) {
        perror("Error deleting folder");
    }
}


int wczytajLabZPliku(int lw, int lk, char labirynt[lw][lk], int tryb) {
    char nazwaPlikuZDanymi[50];
    sprintf(nazwaPlikuZDanymi, "pliki/plik_%d.txt", tryb);
    FILE *plik = fopen(nazwaPlikuZDanymi, "r");
    if (plik == NULL) {
        printf("Nie można otworzyć pliku.\n");
        return tryb;
    }

    char pom[lw][lk+1];
    int i, end;
    
    if (tryb % 2 == 1) {
        i = 0;
        end = lw/2;
    } else {
        i = lw/2;
        end = lw;
    }
    
    do {
        for (int j = 0; j < lk+1; j++) {
            fscanf(plik, "%c", &pom[i][j]);
        }
        i++;
    } while (i < end);
    

    if (tryb % 2 == 1) {
        i = 0;
        end = lw/2;
    } else {
        i = lw/2;
        end = lw;
    }
    
    do {
        for (int j = 0; j < lk; j++) {
            labirynt[i][j]= pom[i][j];
        }
        i++;
    } while (i < end);


    fclose(plik);
    //printf("\nWczytano plik: %d\n", tryb);
    return 1;
}


void write_2d_array_to_file(int x, int y, char array[x][y], int tryb) {
    char nazwaPlikuZDanymi[30];
    sprintf(nazwaPlikuZDanymi, "pliki/plik_%d.txt", tryb);
    FILE *file = fopen(nazwaPlikuZDanymi, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int i, end;
    
    if (tryb % 2 == 1) {
        i = 0;
        end = x/2;
    } else {
        i = x/2;
        end = x;
    }
    
    do {
        for (int j = 0; j < y; j++) {
            fprintf(file, "%c", array[i][j]);
        }
        i++;
        fprintf(file, "\n");
    } while (i < end);

    fclose(file);
    //printf("\nzapisano plik: %d\n", tryb);
}

//----------------------------------------------------------------


void mrowka (int lwplik, int lk, char lab[lwplik][lk], int pi, int pj, int plik_nparz_kopia, int plik_parz_kopia, int lw) {
    int pom;
    char pom2 = '\0';
    int plik_parz= plik_parz_kopia;
    int plik_nparz= plik_nparz_kopia;
    int pom_wczytywanie;
    int lwp=lwplik/2;

    //printf("\nMrówka początek\n");
    
    do {
        pom = 0;
        pom_wczytywanie = 0;
        if (lab[(((pi-1)%(2*lwp)))%(2*lwp)][pj] == 'X') {pom++;} else {pom2='N';}
        if (lab[(((pi+1)%(2*lwp)))%(2*lwp)][pj] == 'X') {pom++;} else {pom2='S';}
        if (lab[(pi%(2*lwp))][pj-1] == 'X') {pom++;} else {pom2='W';}
        if (lab[(pi%(2*lwp))][pj+1] == 'X') {pom++;} else {pom2='E';}
        if (pom == 3) {
            lab[((pi%(2*lwp)))%(2*lwp)][pj]='X';
            switch (pom2) {
                case 'N':
                    pi--;
                    pom_wczytywanie = 1;
                    break;
                case 'S':
                    pi++;
                    pom_wczytywanie = 2;
                    break;
                case 'W':
                    pj--;
                    break;
                case 'E':
                    pj++;
                    break;
            }
        }
        
        //wczytywanie kolejnego w kolejności pliku
        if (pom_wczytywanie == 2) {
            if ((pi%lwp) == (lwp-1)) {
                if (((pi-(pi%lwp))/lwp) > 0  && (((pi-(pi%lwp))/lwp)+2) < ((lw-(lw%lwp)/lwp)+2) && plik_parz != (((pi-(pi%lwp))/lwp)+2) && plik_nparz != (((pi-(pi%lwp))/lwp)+2) ) {
                    //printf("\nDo dołu\npi: %d, pj: %d", pi, pj);
                    write_2d_array_to_file(lwplik, lk, lab, ((pi-(pi%lwp))/lwp));
                    wczytajLabZPliku(lwplik, lk, lab, (((pi-(pi%lwp))/lwp)+2));
                    
                    if (((((pi-(pi%lwp))/lwp)+2)%2) == 0) {
                        plik_parz= (((pi-(pi%lwp))/lwp)+2);
                    } else {
                        plik_nparz= (((pi-(pi%lwp))/lwp)+2);
                    }
                }
            }
        }
        
        //wczytywanie poprzedniego pliku
        if (pom_wczytywanie == 1) {
            if ((pi%lwp) == 1) {
                if (((pi-(pi%lwp))/lwp) > 0  && (((pi-(pi%lwp))/lwp)+2) < ((lw-(lw%lwp)/lwp)+2) && plik_parz != (((pi-(pi%lwp))/lwp)) && plik_nparz != (((pi-(pi%lwp))/lwp)) ) {

                    write_2d_array_to_file(lwplik, lk, lab, ((pi-(pi%lwp))/lwp)+2);
                    wczytajLabZPliku(lwplik, lk, lab, (((pi-(pi%lwp))/lwp)));
                    
                    if (((((pi-(pi%lwp))/lwp)+2)%2) == 0) {
                        plik_parz= ((pi-(pi%lwp))/lwp);
                    } else {
                        plik_nparz= ((pi-(pi%lwp))/lwp);
                    }
                }
            }
        }
        
    } while (pom == 3);
    
    if (plik_nparz_kopia != plik_nparz || plik_parz_kopia != plik_parz) {
        write_2d_array_to_file(lwplik, lk, lab, plik_nparz);
        write_2d_array_to_file(lwplik, lk, lab, plik_parz);

        wczytajLabZPliku(lwplik, lk, lab, plik_nparz_kopia);
        wczytajLabZPliku(lwplik, lk, lab, plik_parz_kopia);
        
    }
}


void deadEndKill2 (int lw, int lk, int lwp, char lab[2*lwp][lk]) {
    wczytajLabZPliku(2*lwp, lk, lab, 1);
    wczytajLabZPliku(2*lwp, lk, lab, 2);
    
    //lwp- linii w pliku
    int pom;
    int znalezionych = 0;
    char pom2 = '\0';
    int plik_parz_kopia= 2;
    int plik_nparz_kopia= 1;
       
    
    int i = 1;
    do {
        for (int j = 1; j < lk-1; j = j+2) {
            pom = 0;
            if (lab[((i%(2*lwp))-1)%(2*lwp)][j] == 'X') {pom++;} else {pom2='S';}
            if (lab[((i%(2*lwp))+1)%(2*lwp)][j] == 'X') {pom++;} else {pom2='N';}
            if (lab[i%(2*lwp)][j-1] == 'X') {pom++;} else {pom2='W';}
            if (lab[i%(2*lwp)][j+1] == 'X') {pom++;} else {pom2='E';}
            if (pom == 3) {
                mrowka (lwp*2, lk, lab, i, j, plik_nparz_kopia, plik_parz_kopia, lw);
            }
        }
        
        if ((i%lwp) == (lwp-3)) {
            if (((i-(i%lwp))/lwp) > 0  && (((i-(i%lwp))/lwp)+2) < ((lw-(lw%lwp)/lwp)+2) ) {
                write_2d_array_to_file(2*lwp, lk, lab, ((i-(i%lwp))/lwp));
                wczytajLabZPliku(2*lwp, lk, lab, (((i-(i%lwp))/lwp)+2));
                if (((((i-(i%lwp))/lwp)+2)%2) == 0) {
                    plik_parz_kopia= (((i-(i%lwp))/lwp)+2);
                } else {
                    plik_nparz_kopia= (((i-(i%lwp))/lwp)+2);
                }
            }
        }
        i=i+2;
    } while (i < lw);
    
    write_2d_array_to_file(2*lwp, lk, lab, (((lw)-((lw)%lwp))/lwp) );
    write_2d_array_to_file(2*lwp, lk, lab, (((lw)-((lw)%lwp))/lwp)+1 );
}

void pathFinder (int lk, int lwp, char lab[2*lwp][lk]) {
    
    FILE *path = fopen("path.txt", "w");

    int i;
    int j;
    char current='t';
    char previous='t';
    int count= -1;

    int pliki = 1;
    int found = 0;
    while(found == 0){
        wczytajLabZPliku(2*lwp, lk, lab, pliki);
        wczytajLabZPliku(2*lwp, lk, lab, pliki+1);

        for(int a=0; a<2*lwp; a++){
            for(int b=0; b<lk; b++){
                if(lab[a][b] == 'P'){
                    found = 1;
                    i = a;
                    j = b;
                }
            }
        }
        pliki+=2;
    }

    
    

    if(lab[i][j] == 'P'){
        if(j == 0){
            j++;
            //printf("tu1\n");
        }else
        if(j == lk-1){
            j--;
            //printf("tu2\n");
        }else
        if(i == 0){
            i++;
            //printf("tu3\n");
        }else{
            i--;
            //printf("tu4\n");
        }
    }
    int iter = 10;



    while(lab[i+1][j] != 'K' && lab[i-1][j] != 'K' && lab[i][j-1] != 'K' && lab[i][j+1] != 'K'){

        if(i == 1 && iter == 0){
            pliki-=2;
            wczytajLabZPliku(2*lwp, lk, lab, pliki);
            wczytajLabZPliku(2*lwp, lk, lab, pliki+1);
            //printf("pliki: %d %d\n", pliki, pliki+1);
            i = 2*lwp-1;
            
            count++;
            previous = current;
            current = 'N';
            if(previous != current){
                fprintf(path, "%c%d", previous, count);
                previous = current;
                count = -1;
            }
            
            // for(int a=0; a<2*lwp; a++){
            //     for(int b=0; b<lk; b++){
            //         printf("%c", lab[a][b]);
            //     }
            //     printf("\n");
            // }

        }else
        if(i == 31 && iter == 0){
            pliki+=2;
            wczytajLabZPliku(2*lwp, lk, lab, pliki);
            wczytajLabZPliku(2*lwp, lk, lab, pliki+1);
            //printf("pliki: %d %d\n", pliki, pliki+1);
            i = 1;

            count++;
            previous = current;
            current = 'S';
            if(previous != current){
                fprintf(path, "%c%d", previous, count);
                previous = current;
                count = -1;
            }

            // for(int a=0; a<2*lwp; a++){
            //     for(int b=0; b<lk; b++){
            //         printf("%c", lab[a][b]);
            //     }
            //     printf("\n");
            // }
        }

        iter = 0;

        //printf("%d, %d - %c\n", i, j, lab[i][j]);

        if(lab[i][j-1] == ' ' && previous != 'E'){
            //printf("%d, %d - %c\n", i, j, lab[i][j]);
            current = 'W';
            j-=2;
            //printf("tam1\n");
            count++;
            if(current != previous){
                if(previous != 't'){
                    fprintf(path, "%c%d", previous, count);
                }
                
                count = -1;
                previous = current;
            }
            iter++;

        }else if(lab[i][j+1] == ' ' && previous != 'W'){
            //printf("%d, %d - %c\n", i, j, lab[i][j]);
            current = 'E';
            j+=2;
            //printf("tam2\n");
            count++;
            
            if(current != previous){
                if(previous != 't'){
                    fprintf(path, "%c%d", previous, count);
                }
                count = -1;
                previous = current;
            }
            iter++;
            
        }else if(lab[i-1][j] == ' ' && previous != 'S' && i-2>=0){
            //printf("%d, %d - %c\n", i, j, lab[i][j]);
            current = 'N';
            i-=2;
            //printf("tam3\n");
            count++;
            if(current != previous){
                if(previous != 't'){
                    fprintf(path, "%c%d", previous, count);
                }
                count = -1;
                previous = current;
            }
            iter++;
            
        }else if(lab[i+1][j] == ' ' && previous != 'N'){
            //printf("%d, %d - %c\n", i, j, lab[i][j]);
            current = 'S';
            i+=2;
            //printf("tam4\n");
            count++;
            if(current != previous){
                if(previous != 't'){
                    fprintf(path, "%c%d", previous, count);
                }
                count = -1;
                previous = current;
            }
            iter++;
        }
        
        if(lab[i+1][j] == 'K' || lab[i-1][j] == 'K' || lab[i][j-1] == 'K' || lab[i][j+1] == 'K'){
            count++;
            fprintf(path, "%c%d", previous, count);
        }
    }
    fclose(path);
}


