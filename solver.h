#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#define MAX_LINE_LENGTH 2050

void printPliki(int numFiles, int lw, int lk, int lwp) ;
void create_folder_and_split_file(FILE *input_fp, int lwp);
void delete_folder_recursively(const char *folder_path) ;
int wczytajLabZPliku(int lw, int lk, char labirynt[lw][lk], int tryb);
void write_2d_array_to_file(int x, int y, char array[x][y], int tryb) ;
void mrowka (int lwplik, int lk, char lab[lwplik][lk], int pi, int pj, int plik_nparz_kopia, int plik_parz_kopia, int lw) ;
void deadEndKill2 (int lw, int lk, int lwp, char lab[2*lwp][lk]);
void pathFinder (int lw, int lk, int lwp, char lab[2*lwp][lk]);