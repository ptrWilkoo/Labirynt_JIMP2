#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

void zapiszFragmentyDoPliku(FILE *oryginalnyLabirynt, char nazwaPlikow[20], char nazwaFolderu[10], int ileWszystkichLinii, int ileWJednymPliku);
void zPlikuDoWektora(FILE *plik, char *wektor);
int liczKolumny(FILE *plik);
int liczWiersze(FILE *plik);
