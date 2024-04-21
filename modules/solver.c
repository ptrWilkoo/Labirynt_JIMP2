#include "solver.h"

void printPliki(int numFiles, int lw, int lk, int lwp) {

    char filename[30];
    FILE *file;

    for (int i = 1; i <= numFiles-1; ++i) {
        // Tworzenie nazwy pliku
        snprintf(filename, sizeof(filename), "pliki/plik_%d.txt", i);

        // Otwarcie pliku
        file = fopen(filename, "r");
        if (file == NULL) {
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


void splitFile(const char *input_file, int lwp) {
    FILE *input_fp = fopen(input_file, "r");
    if (input_fp == NULL) {
        fprintf(stderr, "Błąd otwarcia pliku %s\n", input_file);
        return;
    }

    char folder_name[] = "pliki";
    if (mkdir(folder_name, 0777) == -1) {
        fprintf(stderr, "Bład tworzernia folderu!");
        return;
    }

    char output_file[MAX_LINE_LENGTH];
    int file_count = 1;
    FILE *output_fp = NULL;
    int line_count = 0;

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, input_fp) != NULL) {

        if (line_count % lwp == 0) {
            if (output_fp != NULL) {
                fclose(output_fp);
            }
            sprintf(output_file, "%s/plik_%d.txt", folder_name, file_count++);
            output_fp = fopen(output_file, "w");
            if (output_fp == NULL) {
                fprintf(stderr, "Bład tworzenia pliku %s\n", output_file);
                exit(EXIT_FAILURE);
            }
        }
        fputs(line, output_fp);
        line_count++;
    }
    if (output_fp != NULL) {
        fclose(output_fp);
    }

    fclose(input_fp);
}


void deleteFolder(const char *folder_path) {
    DIR *dir = opendir(folder_path);
    if (dir == NULL) {
        fprintf(stderr, "Bład otwarcia folderu!");
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
            deleteFolder(path);
        } else {
            if (remove(path) != 0) {
                fprintf(stderr, "Bład usuwania pliku %s\n", path);
            }
        }
    }
    closedir(dir);

    if (rmdir(folder_path) != 0) {
        fprintf(stderr, "Błąd usuwania folderu");
    }
}

void wczytajLabZPliku(int lw, int lk, char labirynt[lw][lk], int tryb) {
    char nazwaPlikuZDanymi[50];
    sprintf(nazwaPlikuZDanymi, "pliki/plik_%d.txt", tryb);
    FILE *plik = fopen(nazwaPlikuZDanymi, "r");
    if (plik == NULL) {
        //printf("Nie można otworzyć pliku.\n");
        return;
    }

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
            char znak;
            if (fscanf(plik, "%c", &znak) != 1) {
                fclose(plik);
                return;
            }
            if (j < lk) {
                labirynt[i][j] = znak;
            } else {

            }
        }
        i++;
    } while (i < end);

    fclose(plik);
    //printf("\nWczytano plik: %d\n", tryb);
}

void wektorDoPliku(int x, int y, char array[x][y], int tryb) {
    char nazwaPlikuZDanymi[30];
    sprintf(nazwaPlikuZDanymi, "pliki/plik_%d.txt", tryb);
    FILE *file = fopen(nazwaPlikuZDanymi, "w");
    if (file == NULL) {
        fprintf(stderr, "Błąd otwarcia pliku %s\n", nazwaPlikuZDanymi);
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
                    wektorDoPliku(lwplik, lk, lab, ((pi-(pi%lwp))/lwp));
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

                    wektorDoPliku(lwplik, lk, lab, ((pi-(pi%lwp))/lwp)+2);
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
        wektorDoPliku(lwplik, lk, lab, plik_nparz);
        wektorDoPliku(lwplik, lk, lab, plik_parz);

        wczytajLabZPliku(lwplik, lk, lab, plik_nparz_kopia);
        wczytajLabZPliku(lwplik, lk, lab, plik_parz_kopia);
        
    }
}


void deadEndKill (int lw, int lk, int lwp, char lab[2*lwp][lk]) {
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
                wektorDoPliku(2*lwp, lk, lab, ((i-(i%lwp))/lwp));
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
    
    wektorDoPliku(2*lwp, lk, lab, (((lw)-((lw)%lwp))/lwp) );
    wektorDoPliku(2*lwp, lk, lab, (((lw)-((lw)%lwp))/lwp)+1 );
}

void sciezkaBIN(const char *input_file, const char *output_file) {
    FILE *input = fopen(input_file, "r");
    if (input == NULL) {
        printf("Błąd otwierania pliku wejściowego.\n");
        return;
    }

    FILE *output = fopen(output_file, "w");
    if (output == NULL) {
        printf("Błąd otwierania pliku wyjściowego.\n");
        fclose(input);
        return;
    }

    char current_char;
    char previous_char = '\0';
    int count = 0;

    while ((current_char = fgetc(input)) != EOF) {
        if (current_char != previous_char) {
            if (previous_char != '\0') {
                fprintf(output, "%c%d\n", previous_char, count - 1);
            }
            count = 1;
        } else {
            count++;
        }
        previous_char = current_char;
    }
    
    // Zapisujemy ostatnią sekwencję
    if (previous_char != '\0') {
        fprintf(output, "%c%d\n", previous_char, count - 1);
    }

    fclose(input);
    fclose(output);

    // Usuwamy plik path_pom.txt
    if (remove(input_file) == 0) {
        //printf("Plik %s został pomyślnie usunięty.\n", input_file);
    } else {
        printf("Błąd podczas usuwania pliku %s.\n", input_file);
    }
}


void sciezkaISOD(const char *input_file, const char *output_file) {
    FILE *input = fopen(input_file, "r");
    if (input == NULL) {
        printf("Błąd otwierania pliku wejściowego.\n");
        return;
    }

    FILE *output = fopen(output_file, "w");
    if (output == NULL) {
        printf("Błąd otwierania pliku wyjściowego.\n");
        fclose(input);
        return;
    }

    // Początkowe instrukcje
    fprintf(output, "START\n");

    char line[100];
    int forward_count = 0;

    while (fgets(line, sizeof(line), input)) {
        if (strcmp(line, "TURNRIGHT\n") == 0) {
            if (forward_count > 1) {
                fprintf(output, "FORWARD %d\n", forward_count);
                forward_count = 0;
            }
            if (forward_count == 1) {
                fprintf(output, "FORWARD\n");
                forward_count = 0;
            }
            fprintf(output, "TURNRIGHT\n");
        } else if (strcmp(line, "TURNLEFT\n") == 0) {
            if (forward_count > 1) {
                fprintf(output, "FORWARD %d\n", forward_count);
                forward_count = 0;
            }
            if (forward_count == 1) {
                fprintf(output, "FORWARD\n");
                forward_count = 0;
            }
            fprintf(output, "TURNLEFT\n");
        } else if (strcmp(line, "FORWARD\n") == 0) {
            forward_count++;
        }
    }

    // Zapisujemy ostatnie instrukcje FORWARD
    if (forward_count > 1) {
        fprintf(output, "FORWARD %d\n", forward_count);
    }
    if (forward_count == 1) {
        fprintf(output, "FORWARD\n");
        forward_count = 0;
    }
    // Końcowe instrukcje
    fprintf(output, "STOP\n");

    fclose(input);
    fclose(output);

    // Usuwamy plik path_isod_pom.txt
    if (remove(input_file) == 0) {
        //printf("Plik %s został pomyślnie usunięty.\n", input_file);
    } else {
        printf("Błąd podczas usuwania pliku %s.\n", input_file);
    }
}


void znajdzPoczKoniec (int lw, int lk, int lwp, char lab[2*lwp][lk], int pocz_i_kon[4]) {
    wczytajLabZPliku(2*lwp, lk, lab, 1);
    wczytajLabZPliku(2*lwp, lk, lab, 2);
    
    //[0]- px (j)
    //[1]- py (i)
    //[2]- kx (j)
    //[3]- ky (i)
    
    for (int i = 0; i < lw; i++) {
        for (int j = 0; j < lk; j++) {
            if (lab[((i%(2*lwp)))%(2*lwp)][j]=='P') {
                pocz_i_kon[0] = j;
                pocz_i_kon[1] = i;
            }
            if (lab[((i%(2*lwp)))%(2*lwp)][j]=='K') {
                pocz_i_kon[2] = j;
                pocz_i_kon[3] = i;
            }
        }
        if ((i%lwp) == (lwp-3) && (((i-(i%lwp))/lwp)+2) < (((lw)-((lw)%lwp))/lwp)+2) {
            if (((i-(i%lwp))/lwp) > 0  && (((i-(i%lwp))/lwp)+2) < ((lw-(lw%lwp)/lwp)+2)) {
                wczytajLabZPliku(2*lwp, lk, lab, (((i-(i%lwp))/lwp)+2));
            }
        }
    }
}


int rozwiazSciezke (int lw, int lk, int lwp, char lab[2*lwp][lk], int i, int j, int kx, int ky, int dldrogi, char kierunek) {
    
    if (i < lwp) {
        wczytajLabZPliku(2*lwp, lk, lab, 1);
        wczytajLabZPliku(2*lwp, lk, lab, 2);
    } else if (i < (lk-lwp)) {
        wczytajLabZPliku(2*lwp, lk, lab, (((i-(i%lwp))/lwp)));
        wczytajLabZPliku(2*lwp, lk, lab, (((i-(i%lwp))/lwp)+1));
    } else {
        wczytajLabZPliku(2*lwp, lk, lab, (((i-(i%lwp))/lwp)));
        wczytajLabZPliku(2*lwp, lk, lab, (((i-(i%lwp))/lwp)-1));
    }
    
    int pom;
    
    FILE *zapisdobin= fopen("path_pom.txt", "w");
    if (zapisdobin == NULL) {
        fprintf(stderr, "Bład otwarca pliku path_pom.txt\n");
        exit(EXIT_FAILURE);
    }
    
    FILE *zapisisod= fopen("path_isod_pom.txt", "w");
    if (zapisisod == NULL) {
        fprintf(stderr, "Bład otwarca pliku path_isod_pom.txt\n");
        exit(EXIT_FAILURE);
    }
    
    do {
        pom = -1;
        switch (kierunek) {
            case 'N':
                if (lab[i%(2*lwp)][j+1] == ' ' || lab[i%(2*lwp)][j+1] == 'K') {
                    fprintf(zapisisod, "TURNRIGHT\nFORWARD\n");
                    j=j+2;
                    dldrogi++;
                    kierunek = 'E';
                    break;
                }
                if (lab[((i%(2*lwp))-1)%(2*lwp)][j] == ' ' || lab[((i%(2*lwp))-1)%(2*lwp)][j] == 'K') {
                    fprintf(zapisisod, "FORWARD\n");
                    kierunek = 'N';
                    dldrogi++;
                    i=i-2;
                    break;
                }
                if (lab[i%(2*lwp)][j-1] == ' ' || lab[i%(2*lwp)][j-1] == 'K') {
                    fprintf(zapisisod, "TURNLEFT\nFORWARD\n");
                    dldrogi++;
                    j=j-2;
                    kierunek = 'W';
                    break;
                }
                if (lab[((i%(2*lwp))+1)%(2*lwp)][j] == ' ' || lab[((i%(2*lwp))+1)%(2*lwp)][j] == 'K') {
                    fprintf(zapisisod, "TURNLEFT\nTURNLEFT\nFORWARD\n");
                    dldrogi++;
                    i=i+2;
                    kierunek = 'S';
                    break;
                }
                break;
            case 'E':
                if (lab[((i%(2*lwp))+1)%(2*lwp)][j] == ' ' || lab[((i%(2*lwp))+1)%(2*lwp)][j] == 'K') {
                    fprintf(zapisisod, "TURNRIGHT\nFORWARD\n");
                    dldrogi++;
                    i=i+2;
                    kierunek = 'S';
                    break;
                }
                if (lab[i%(2*lwp)][j+1] == ' ' || lab[i%(2*lwp)][j+1] == 'K') {
                    fprintf(zapisisod, "FORWARD\n");
                    dldrogi++;
                    j=j+2;
                    break;
                }
                if (lab[((i%(2*lwp))-1)%(2*lwp)][j] == ' ' || lab[((i%(2*lwp))-1)%(2*lwp)][j] == 'K') {
                    fprintf(zapisisod, "TURNLEFT\nFORWARD\n");
                    dldrogi++;
                    i=i-2;
                    kierunek = 'N';
                    break;
                }
                if (lab[i%(2*lwp)][j-1] == ' ' || lab[i%(2*lwp)][j-1] == 'K') {
                    fprintf(zapisisod, "TURNLEFT\nTURNLEFT\nFORWARD\n");
                    dldrogi++;
                    j=j-2;
                    kierunek = 'W';
                    break;
                }
                break;
            case 'S':
                if (lab[i%(2*lwp)][j-1] == ' ' || lab[i%(2*lwp)][j-1] == 'K') {
                    fprintf(zapisisod, "TURNRIGHT\nFORWARD\n");
                    dldrogi++;
                    j=j-2;
                    kierunek = 'W';
                    break;
                }
                if (lab[((i%(2*lwp))+1)%(2*lwp)][j] == ' ' || lab[((i%(2*lwp))+1)%(2*lwp)][j] == 'K') {
                    fprintf(zapisisod, "FORWARD\n");
                    dldrogi++;
                    i=i+2;
                    break;
                }
                if (lab[i%(2*lwp)][j+1] == ' ' || lab[i%(2*lwp)][j+1] == 'K') {
                    fprintf(zapisisod, "TURNLEFT\nFORWARD\n");
                    j=j+2;
                    dldrogi++;
                    kierunek = 'E';
                    break;
                }
                if (lab[((i%(2*lwp))-1)%(2*lwp)][j] == ' ' || lab[((i%(2*lwp))-1)%(2*lwp)][j] == 'K') {
                    fprintf(zapisisod, "TURNLEFT\nTURNLEFT\nFORWARD\n");
                    dldrogi++;
                    i=i-2;
                    kierunek = 'N';
                    break;
                }
                break;
            case 'W':
                if (lab[((i%(2*lwp))-1)%(2*lwp)][j] == ' ' || lab[((i%(2*lwp))-1)%(2*lwp)][j] == 'K') {
                    fprintf(zapisisod, "TURNRIGHT\nFORWARD\n");
                    dldrogi++;
                    i=i-2;
                    kierunek = 'N';
                    break;
                }
                if (lab[i%(2*lwp)][j-1] == ' ' || lab[i%(2*lwp)][j-1] == 'K') {
                    fprintf(zapisisod, "FORWARD\n");
                    dldrogi++;
                    j=j-2;
                    break;
                }
                if (lab[((i%(2*lwp))+1)%(2*lwp)][j] == ' ' || lab[((i%(2*lwp))+1)%(2*lwp)][j] == 'K') {
                    fprintf(zapisisod, "TURNLEFT\nFORWARD\n");
                    dldrogi++;
                    kierunek = 'S';
                    i=i+2;
                    break;
                }
                if (lab[i%(2*lwp)][j+1] == ' ' || lab[i%(2*lwp)][j+1] == 'K') {
                    fprintf(zapisisod, "TURNLEFT\nTURNLEFT\nFORWARD\n");
                    j=j+2;
                    dldrogi++;
                    kierunek = 'E';
                    break;
                }
                break;
        }
        fprintf(zapisdobin, "%c", kierunek);
        
        //plik w dol
        if ((i%lwp) == (lwp-3) && (((i-(i%lwp))/lwp)+2) < (((lw)-((lw)%lwp))/lwp)+2) {
            if (((i-(i%lwp))/lwp) > 0  && (((i-(i%lwp))/lwp)+2) < ((lw-(lw%lwp)/lwp)+2)) {
                wczytajLabZPliku(2*lwp, lk, lab, (((i-(i%lwp))/lwp)+2));
            }
        }
        
        //plik w gore
        if (((i%lwp) == 1) && ((i-(i%lwp))/lwp) > 0  && (((i-(i%lwp))/lwp)+2) < ((lw-(lw%lwp)/lwp)+2)) {
                wczytajLabZPliku(2*lwp, lk, lab, (((i-(i%lwp))/lwp)));
        }
        
    } while (lab[((i%(2*lwp))-1)%(2*lwp)][j] != 'K' && lab[((i%(2*lwp))+1)%(2*lwp)][j] != 'K' && lab[i%(2*lwp)][j+1] != 'K' && lab[i%(2*lwp)][j-1] != 'K');
    
    fclose(zapisisod);
    fclose(zapisdobin);
    
    sciezkaBIN("path_pom.txt", "path.txt");
    sciezkaISOD("path_isod_pom.txt", "path_isod.txt");
    
    return dldrogi;
}


void pathFind (int lw, int lk, int lwp, char lab[2*lwp][lk], int *length) {

    //znajdzSkrzyzowania(lw, lk, lwp, lab);
    
    int pocz_i_kon[4];
    znajdzPoczKoniec(lw, lk, lwp, lab, pocz_i_kon);
    
    //printf ("\nP(%d, %d)\nK(%d, %d)\n\n", pocz_i_kon[0], pocz_i_kon[1], pocz_i_kon[2], pocz_i_kon[3]);
    
    int i= pocz_i_kon[1];
    int j= pocz_i_kon[0];
    int dldrogi = 0;
    
    //N- idzie do góry, E- idzie w prawo, S-idzie do dołu, W- idzie w lewo
    char kierunek;
    
    if (pocz_i_kon[0] == 0) {
        j = 1;
        kierunek = 'E';
    }
    if (pocz_i_kon[1] == 0) {
        i = 1;
        kierunek = 'S';
    }
    if (pocz_i_kon[0] == lk-1) {
        j = lk-2;
        kierunek = 'W';
    }
    if (pocz_i_kon[1] == lw-1) {
        i = lw-2;
        kierunek = 'N';
    }
    
    dldrogi = rozwiazSciezke (lw, lk, lwp, lab, i, j, pocz_i_kon[2], pocz_i_kon[3], dldrogi, kierunek);
    *length = dldrogi;
    
    //printf("\nDługość drogi: %d\n", dldrogi);
}
