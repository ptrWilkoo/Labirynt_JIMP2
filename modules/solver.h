#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#define MAX_LINE_LENGTH 2051

void printPliki(int numFiles, int lw, int lk, int lwp) ;
void create_folder_and_split_file(const char *input_file, int lwp);
void delete_folder_recursively(const char *folder_path) ;
void wczytajLabZPliku(int lw, int lk, char labirynt[lw][lk], int tryb);
void write_2d_array_to_file(int x, int y, char array[x][y], int tryb) ;
void mrowka (int lwplik, int lk, char lab[lwplik][lk], int pi, int pj, int plik_nparz_kopia, int plik_parz_kopia, int lw) ;
void deadEndKill (int lw, int lk, int lwp, char lab[2*lwp][lk]);
void pathFind (int lw, int lk, int lwp, char lab[2*lwp][lk], int *length);
int rozwiazSciezke (int lw, int lk, int lwp, char lab[2*lwp][lk], int i, int j, int kx, int ky, int dldrogi, char kierunek);
