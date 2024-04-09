#include "input.h"

int liczKolumny(FILE *plik){
    fseek(plik, 0, SEEK_SET);
    
    int liczbaKolumn = 0;
    int ch;

    while( (ch = fgetc(plik) ) != EOF && ch != '\n'){
        liczbaKolumn++;
    }

    return liczbaKolumn;
}

int liczWiersze(FILE *plik){
    fseek(plik, 0, SEEK_SET);

    int liczbaWierszy = 0;
    int ch;

    while((ch = fgetc(plik)) != EOF){
            if(ch == '\n') liczbaWierszy++;
    }
    return liczbaWierszy;
}

void binaryToText(FILE *in){

    uint32_t id;
    uint8_t escape;
    uint16_t columns;
    uint16_t lines;
    uint16_t entryX;
    uint16_t entryY;
    uint16_t exitX;
    uint16_t exitY;
    uint32_t reserved_one;
    uint32_t reserved_two;
    uint32_t reserved_three;
    uint32_t counter;
    uint32_t solution_offset;
    uint8_t separator;
    uint8_t wall;
    uint8_t path;


    

    fread(&id, sizeof(uint32_t), 1, in);
    fread(&escape, sizeof(uint8_t), 1, in);
    fread(&columns, sizeof(uint16_t), 1, in);
    fread(&lines, sizeof(uint16_t), 1, in);
    fread(&entryX, sizeof(uint16_t), 1, in);
    fread(&entryY, sizeof(uint16_t), 1, in);
    fread(&exitX, sizeof(uint16_t), 1, in);
    fread(&exitY, sizeof(uint16_t), 1, in);
    fread(&reserved_one, sizeof(uint32_t), 1, in);
    fread(&reserved_two, sizeof(uint32_t), 1, in);
    fread(&reserved_three, sizeof(uint32_t), 1, in);
    fread(&counter, sizeof(uint32_t), 1, in);
    fread(&solution_offset, sizeof(uint32_t), 1, in);
    fread(&separator, sizeof(uint8_t), 1, in);
    fread(&wall, sizeof(uint8_t), 1, in);
    fread(&path, sizeof(uint8_t), 1, in);

    printf("id = %u\n", id);
    printf("escape = %hhu\n", escape);
    printf("columns = %hu\n", columns);
    printf("lines = %hu\n", lines);
    printf("entryX = %hu\n", entryX);
    printf("entryY = %hu\n", entryY);
    printf("exitX = %hu\n", exitX);
    printf("exitY = %hu\n", exitY);
    printf("reserved_one = %u\n", reserved_one);
    printf("reserved_two = %u\n", reserved_two);
    printf("reserved_three = %u\n", reserved_three);
    printf("counter = %u\n", counter);
    printf("solution_offset = %u\n", solution_offset);
    printf("separator = %hhu\n", separator);
    printf("wall = %hhu\n", wall);
    printf("path = %hhu\n", path);


    FILE *out = fopen("maze.txt", "w");

    for(int i=0; i<lines; i++){
        if(i!=0) fprintf(out, "\n");
        for(int j=0; j<columns; j++){
            uint8_t temp;
            char znak;
            int ile;
            fread(&temp, sizeof(uint8_t), 1, in); // separator

            fread(&temp, sizeof(uint8_t), 1, in); // symbol
            if(temp == wall){
                znak = 'X';

            }else if(temp == path){
                znak = ' ';
            }else{
                znak = '?';
            }

            
            fread(&temp, sizeof(uint8_t), 1, in); //count
            ile = temp + 1;
            int counter = 0;

            j--;
            while(counter<ile){
                j++;
                if(j == columns){
                    j=0;
                    i++;
                }

                if(i==entryY-1 && j==entryX-1){
                    fprintf(out, "P");
                }else if(i==exitY-1 && j==exitX-1){
                    fprintf(out, "K");
                }else{
                    fprintf(out, "%c", znak);
                }
                counter++;              
            }
        }
    }
    fclose(in);
    fclose(out);

}