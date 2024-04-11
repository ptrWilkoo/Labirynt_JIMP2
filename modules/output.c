#include "output.h"
#include "input.h"

int isDigit(char x){
    if(x >= '0' && x <= '9'){
        return 1;
    }else{
        return 0;
    }
}

int outputFromText(FILE *in){

    FILE *out = fopen("wynik.bin", "wb");

    uint32_t id = 0x52524243;
    uint8_t escape = 0x1B;


    uint16_t columns = liczKolumny(in);;
    uint16_t lines = liczWiersze(in);

    int x = 1;
    int y = 1;
    int ch;

    fseek(in, 0, SEEK_SET);
    while((ch = fgetc(in)) != 'P'){

        if(ch == '\n'){
            y++;
            x = 1;
        }else{
            x++;
        }
    }
    fseek(in, 0, SEEK_SET);


    uint16_t entryX = x;
    uint16_t entryY = y;
    
    x = 1;
    y = 1;
    while((ch = fgetc(in)) != 'K'){

        if(ch == '\n'){
            y++;
            x = 1;
        }else{
            x++;
        }
    }
    fseek(in, 0, SEEK_SET);

    uint16_t exitX = x;
    uint16_t exitY = y;

    uint32_t reserved_one = 255;
    uint32_t reserved_two = 255;
    uint32_t reserved_three = 255;

    uint32_t counter; // todo

    uint32_t solution_offset = 123;

    uint8_t separator = 35;
    uint8_t wall = 88;
    uint8_t path = 32;

    int prev = 't';
    int count = 1;

    while((ch = fgetc(in)) != EOF){
        if(ch != '\n'){
            if(prev != ch && prev != 't'){
                count++;
            }
            prev = ch;
        }else{
            count++;
        }
    }
    counter = count;
    fseek(in, 0, SEEK_SET);


    fwrite(&id, sizeof(uint32_t), 1, out);
    fwrite(&escape, sizeof(uint8_t), 1, out);
    fwrite(&columns, sizeof(uint16_t), 1, out);
    fwrite(&lines, sizeof(uint16_t), 1, out);
    fwrite(&entryX, sizeof(uint16_t), 1, out);
    fwrite(&entryY, sizeof(uint16_t), 1, out);
    fwrite(&exitX, sizeof(uint16_t), 1, out);
    fwrite(&exitY, sizeof(uint16_t), 1, out);
    fwrite(&reserved_one, sizeof(uint32_t), 1, out);
    fwrite(&reserved_two, sizeof(uint32_t), 1, out);
    fwrite(&reserved_three, sizeof(uint32_t), 1, out);
    fwrite(&counter, sizeof(uint32_t), 1, out);
    fwrite(&solution_offset, sizeof(uint32_t), 1, out);
    fwrite(&separator, sizeof(uint8_t), 1, out);
    fwrite(&wall, sizeof(uint8_t), 1, out);
    fwrite(&path, sizeof(uint8_t), 1, out);

    // zapis slow kodowych
    prev = 't';
    int prev_ch = 't';
    count = 0;
    int znak = 0;
    int test = 0;
    while((ch = fgetc(in)) != EOF){

        if(ch == 'X'){
            znak = wall;
        }else if(ch == ' ' || ch == 'P' || ch == 'K'){
            znak = path;
        }

        if(ch != '\n'){
            if(prev != znak && prev_ch != '\n'){
                if(prev != 't'){
                    if(count < 0 ) count = 0;
                    fwrite(&separator, sizeof(uint8_t), 1, out);
                    fwrite(&prev, sizeof(uint8_t), 1, out);
                    fwrite(&count, sizeof(uint8_t), 1, out);
                }
                count = 0;

            }else{
                count++;
                if(count==255){
                    fwrite(&separator, sizeof(uint8_t), 1, out);
                    fwrite(&znak, sizeof(uint8_t), 1, out);
                    fwrite(&count, sizeof(uint8_t), 1, out);
                    count = -1;
                    
                }
            }
        }
        else{
            if(count<0){
                continue;   
            }
            
            fwrite(&separator, sizeof(uint8_t), 1, out);
            fwrite(&znak, sizeof(uint8_t), 1, out);
            fwrite(&count, sizeof(uint8_t), 1, out);
            
            count=-1;
        }
        
        prev = znak;
        prev_ch = ch;
    }
    fwrite(&separator, sizeof(uint8_t), 1, out);
    fwrite(&znak, sizeof(uint8_t), 1, out);
    fwrite(&count, sizeof(uint8_t), 1, out);
    fseek(in, 0, SEEK_SET);
    
    // sciezka
    FILE *sciezka = fopen("path.txt", "rt");

    uint32_t path_id = 0x52524243;
    uint8_t steps = 100; // todo - policz kroki w sciezce

    fwrite(&path_id, sizeof(uint32_t), 1, out);
    fwrite(&steps, sizeof(uint8_t), 1, out);


    // zapis sciezki

    int c = 0;
    prev = 't';
    int prev_c = 0;
    int liczba = 0;

    while((c = fgetc(sciezka)) != EOF){

        if(c != '\n'){
            if(isDigit(c)){
                if(isDigit(prev)){
                    liczba *= 10;
                    liczba += (c - '0');
                }else{
                    liczba += (c - '0');
                }
                
            }else{     
                if(isDigit(prev)){

                    if(liczba > 255){
                        while(liczba > 0) {
                            int pom = liczba > 255 ? 255 : liczba; 
                            fwrite(&prev_c, sizeof(uint8_t), 1, out);
                            fwrite(&pom, sizeof(uint8_t), 1, out); 
                            liczba -= pom;
                        }
                    }else{
                        fwrite(&prev_c, sizeof(uint8_t), 1, out);
                        fwrite(&liczba, sizeof(uint8_t), 1, out);
                        liczba = 0;
                    }       
                }
                prev_c = c;
            }
            prev = c;
        }
        
    }
    fwrite(&prev_c, sizeof(uint8_t), 1, out);
    fwrite(&liczba, sizeof(uint8_t), 1, out);

    fseek(sciezka, 0, SEEK_SET);

    fclose(sciezka);
    fclose(in);
    fclose(out);
    

    return 0;
}