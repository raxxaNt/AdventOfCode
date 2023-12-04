#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int get_card_points(char cadena[130])
{
    int winning_num[10];
    int i = 0, win_counter = 0, ocurr = 0, get_num = 0;

    while (cadena[i] != ':')
        i++;
    i += 1;
    while (cadena[i] != '|') {
        if (isdigit(cadena[i]) != 0) {
            winning_num[win_counter] = atoi(&cadena[i]);
            win_counter++;
            while (isdigit(cadena[i + 1]) != 0)
                i++;
        }
        i++;
    }
    while (cadena[i] != '\0') {
        win_counter = 0;
        if (isdigit(cadena[i]) != 0) {
            get_num = atoi(&cadena[i]);
            while (win_counter < 10) {
                if (get_num == winning_num[win_counter]) {
                    if (ocurr == 0)
                        ocurr++;
                    else
                        ocurr *= 2;
                    break;
                }
                win_counter++;
            }
            while (isdigit(cadena[i + 1]) != 0)
            i++;
        }
        i++;
    }
    return ocurr;
}

int main() {
    FILE *f;
    char cadena[130];
    int tot_sum = 0;
    //int i = 0;

    f= fopen("doc.txt", "r");

    while (feof(f) == 0) {
        fgets(cadena, 130, f);
        tot_sum += get_card_points(cadena);
        //printf("LINE %d--TOTSUM: %d\n", i, tot_sum);
        //i++;
    }
    fclose(f);
    printf("Los puntos totales son: %d\n", tot_sum);
}