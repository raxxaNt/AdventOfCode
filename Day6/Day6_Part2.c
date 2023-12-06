#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define RACE_CUANT 4

int long long get_nums(char cadena[38])
{
    int i = 0;
    int long long num = 0;
    
    while (cadena[i] != '\0') {
        if (isdigit(cadena[i]) != 0)
            num = num * 10 + (cadena[i] - '0');
        i++;
    }
    return num;
}

int get_record_race(int long long time, int long long distance)
{
    int long long record = 0, time_left = 0, dist_rec = 0;

    for (int long long hold_button = 0; hold_button < time; hold_button++) {
        time_left = time - hold_button;
        dist_rec = hold_button * time_left;
        if (dist_rec > distance)
            record++;
    }
    return record;
}

int main() {
    FILE *f;
    int line = 0;
    char cadena[2][38];
    int long long time = 0, distance = 0, record = 0;

    f = fopen("doc.txt","r");
    while (feof(f) == 0) {
        fgets(cadena[line], 38, f);
        line++;
    }
    fclose(f);

    time = get_nums(cadena[0]);
    distance = get_nums(cadena[1]);

    record = get_record_race(time, distance);

    printf("El resultado es: %lld\n", record);
}
