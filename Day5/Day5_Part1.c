#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define LINE_SIZE 204

int long long *get_seeds(char cadena_l1[255])
{
    int i = 0, seed_counter = 0;
    int long long get_seed = 0;
    int long long *seed;

    seed = malloc(sizeof(seed) * 20);
    while (cadena_l1[i] != '\0') {
        if (isdigit(cadena_l1[i]) != 0) {
            get_seed = atoll(&cadena_l1[i]);
            //printf("GET_SEED: %lu---SEED_COUNTER: %d\n", get_seed, seed_counter);
            seed[seed_counter] = get_seed;
            seed_counter++;
            while (isdigit(cadena_l1[i + 1]) != 0)
                i++;
        }
        i++;
    }
    return (seed);
}

int count_nums(char cadena[40])
{
    int i = 0, count_num = 0;
    while (cadena[i] != '\0') {
        if (isdigit(cadena[i]) != 0) {
            count_num++;
            while (isdigit(cadena[i + 1]) != 0)
                i++;
        }
        i++;
    }
    return (count_num);
}

int long long get_range(int long long seed, int long long dest, int long long src, int long long len)
{
    int long long temp_src = 0;
    temp_src = src;
    if (src <= seed) {
        while (src < (temp_src + len)) {
            if (src == seed) {
                //printf("DEST: %lld\n", dest);
                return dest;
            }
            src++;
            dest++;
        }
    }
    //printf("SEED: %lld\n", seed);
    return seed;

}

int long long get_location(int long long seed, char cadena[LINE_SIZE][40])
{
    int line = 3, i = 0;
    int long long dest_num = -1, src_num = -1, len = 0, temp_seed = 0;

    while (line < LINE_SIZE + 1) {
        //printf("SEED: %lld---LINE: %d---Cadena: %s\n", seed, line, cadena[line]);
        i = 0, dest_num = -1, src_num = -1;
        if (count_nums(cadena[line]) == 3) {
            //printf("LINE: %d---", line);
            while (cadena[line][i] != '\0') {
                //printf("CADENA: %s\n", cadena[line]);
                if (isdigit(cadena[line][i]) != 0 && dest_num == -1)
                    dest_num = atoll(&cadena[line][i]);
                else if (isdigit(cadena[line][i]) != 0 && src_num == -1)
                    src_num = atoll(&cadena[line][i]);
                else if (isdigit(cadena[line][i]) != 0)
                    len = atoll(&cadena[line][i]);
                if (isdigit(cadena[line][i]) != 0) {
                    while (isdigit(cadena[line][i + 1]) != 0)
                        i++;
                }
                i++;
            }
            temp_seed = seed;
            seed = get_range(seed, dest_num, src_num, len);
            if (temp_seed != seed) {
                while (count_nums(cadena[line]) == 3)
                    line++;
            }
            //printf("DEST: %lld---SRC: %lld---LEN: %lld\n", dest_num, src_num, len);
            //printf("SEED: %lld\n", seed);
        }
        line++;
    }
    //printf("SEED: %lld\n", seed);
    return seed;
}

int main() {
    FILE *f;
    int line = 1, seed_counter = 0;
    int long long *seeds, *location;
    char cadena_l1[255];
    char cadena[LINE_SIZE][40];
    int long long min_loc = 0;

    seeds = malloc(sizeof(seeds)* 20);
    location = malloc(sizeof(location)* 20);
    f= fopen("doc.txt", "r");
    while (feof(f) == 0) {
        if (line == 1) {
            fgets(cadena_l1, 255, f);
            seeds = get_seeds(cadena_l1);
            //printf("LINE: %d---%s\n", line, cadena_l1);
        }
        else {
            fgets(cadena[line], 40, f);
            //printf("LINE: %d---%s\n", line, cadena[line]);
        }
        line++;
    }
    //printf("SEEDS: %llu---%llu\n", seeds[1], seeds[3]);
    line = 1;
    
    while (seed_counter < 20) {//Hay 20 semillas.
        //printf("SEEDS: %llu\n", seeds[seed_counter]);
        location[seed_counter] = get_location(seeds[seed_counter], cadena);
        //printf("LOCATION: %llu--SEED_COUNTER: %d\n", location[seed_counter], seed_counter);
        seed_counter++;
    }
    min_loc = location[0];
    for (int k = 1; k < seed_counter; k++) {
        if (min_loc > location[k])
            min_loc = location[k];
    }

    printf("%llu", min_loc);
}