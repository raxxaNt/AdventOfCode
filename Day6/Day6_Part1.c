#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define RACE_CUANT 4

int *get_nums(char cadena[38])
{
    int i = 0, counter = 0;
    int *get_num;
    
    get_num = malloc(sizeof(get_num) * 4);
    while (cadena[i] != '\0') {
        if (isdigit(cadena[i]) != 0) {
            get_num[counter] = atoi(&cadena[i]);
            counter++;
            while (isdigit(cadena[i + 1]) != 0)
                i++;
        }
        i++;
    }
    return get_num;
}

int get_record_race(int time, int distance)
{
    int record = 0, time_left = 0, dist_rec;

    for (int hold_button = 0; hold_button < time; hold_button++) {
        time_left = time - hold_button;
        dist_rec = hold_button * time_left;
        if (dist_rec > distance)
            record++;
    }
    return record;
}

int main() {
    FILE *f;
    int line = 0, record = 1;
    char cadena[2][38];
    int *time, *distance;

    time = malloc(sizeof(time) * 4);
    distance = malloc(sizeof(distance) * 4);
    f = fopen("doc.txt","r");
    while (feof(f) == 0) {
        fgets(cadena[line], 38, f);
        line++;
    }
    fclose(f);

    time = get_nums(cadena[0]);
    distance = get_nums(cadena[1]);

    for (int race = 0; race < RACE_CUANT; race++) {
        record *= get_record_race(time[race], distance[race]); //function name (time[race], distance[race])
    }
    printf("El resultado es: %d\n", record);
    free(time);
    free(distance);
}