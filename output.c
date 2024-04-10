#include "output.h"

void binaryOutput(FILE *in){

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

    FILE *sciezka = fopen("path.txt", "r");
    FILE *out = fopen("binary.bin", "wb");
    

    // Read and write data accordingly
    fread(&id, sizeof(uint32_t), 1, in);
    fwrite(&id, sizeof(uint32_t), 1, out);

    fread(&escape, sizeof(uint8_t), 1, in);
    fwrite(&escape, sizeof(uint8_t), 1, out);

    fread(&columns, sizeof(uint16_t), 1, in);
    fwrite(&columns, sizeof(uint16_t), 1, out);

    fread(&lines, sizeof(uint16_t), 1, in);
    fwrite(&lines, sizeof(uint16_t), 1, out);

    fread(&entryX, sizeof(uint16_t), 1, in);
    fwrite(&entryX, sizeof(uint16_t), 1, out);

    fread(&entryY, sizeof(uint16_t), 1, in);
    fwrite(&entryY, sizeof(uint16_t), 1, out);

    fread(&exitX, sizeof(uint16_t), 1, in);
    fwrite(&exitX, sizeof(uint16_t), 1, out);

    fread(&exitY, sizeof(uint16_t), 1, in);
    fwrite(&exitY, sizeof(uint16_t), 1, out);

    fread(&reserved_one, sizeof(uint32_t), 1, in);
    fwrite(&reserved_one, sizeof(uint32_t), 1, out);

    fread(&reserved_two, sizeof(uint32_t), 1, in);
    fwrite(&reserved_two, sizeof(uint32_t), 1, out);

    fread(&reserved_three, sizeof(uint32_t), 1, in);
    fwrite(&reserved_three, sizeof(uint32_t), 1, out);

    fread(&counter, sizeof(uint32_t), 1, in);
    fwrite(&counter, sizeof(uint32_t), 1, out);

    fread(&solution_offset, sizeof(uint32_t), 1, in);
    solution_offset = 123;
    fwrite(&solution_offset, sizeof(uint32_t), 1, out);

    fread(&separator, sizeof(uint8_t), 1, in);
    fwrite(&separator, sizeof(uint8_t), 1, out);

    fread(&wall, sizeof(uint8_t), 1, in);
    fwrite(&wall, sizeof(uint8_t), 1, out);

    fread(&path, sizeof(uint8_t), 1, in);
    fwrite(&path, sizeof(uint8_t), 1, out);

    uint32_t path_id = 0x52524243;
    fwrite(&path_id, sizeof(uint32_t), 1, out);
    
    uint8_t steps = 100; // do zrobienia
    fwrite(&steps, sizeof(uint8_t), 1, out);


    // co jesli count > 9 
    // char ch;
    // int pom = 0;
    // while((ch = fgetc(sciezka)) != EOF){
    //     if(pom % 2 != 0){
    //         int kroki = ch - '0';
            
    //         uint8_t kroki_bin = (uint8_t)kroki;
    //         printf("%u\n", kroki_bin);
    //         fwrite(&kroki_bin, sizeof(uint8_t), 1, out);
    //     }else{
    //         uint8_t kierunek = ch;
    //         printf("%u ", kierunek);
    //         fwrite(&kierunek, sizeof(uint8_t), 1, out);
    //     }
    //     pom++;
    // }


    // printf("id = %u\n", id);
    // printf("escape = %hhu\n", escape);
    // printf("columns = %hu\n", columns);
    // printf("lines = %hu\n", lines);
    // printf("entryX = %hu\n", entryX);
    // printf("entryY = %hu\n", entryY);
    // printf("exitX = %hu\n", exitX);
    // printf("exitY = %hu\n", exitY);
    // printf("reserved_one = %u\n", reserved_one);
    // printf("reserved_two = %u\n", reserved_two);
    // printf("reserved_three = %u\n", reserved_three);
    // printf("counter = %u\n", counter);
    // printf("solution_offset = %u\n", solution_offset);
    // printf("separator = %hhu\n", separator);
    // printf("wall = %hhu\n", wall);
    // printf("path = %hhu\n", path);


    
    fclose(in);
    fclose(sciezka);
    fclose(out);

}