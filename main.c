#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Nie podano nazwy pliku!");
		return 1;
	}

	FILE *plik;
	char linia[2050];//liczba znaków to 2n+1 wymiar labiryntu + znak końca linii
	int liczba_znaków = -1;//uwzględnia znak końca linii

	plik = fopen(argv[1], "r");

	if(plik == NULL) {
		printf("Nie udało się otworzyć pliku!");
		return 1;
	}

	if(fgets(linia, sizeof(linia), plik)) {
		for(int i = 0; linia[i] != '\0'; i++) {
			liczba_znaków++;
		}
	}

	printf("Liczba znaków w wierszu: %d\n", liczba_znaków);

	return 0;
}
