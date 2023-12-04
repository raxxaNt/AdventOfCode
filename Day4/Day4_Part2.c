#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int get_ocurr(char cadena[130])
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
                    ocurr++;
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
    int card[195];
    int tot_sum = 0, match_num = 0; //
    int i = 0, copias = 0, j = 0, k = 0; //For loops

    while (i < 195) {
        card[i] = 1;
        i++;
    }
    i = 1;
    card[0] = 0;
    card[i] = 1;
    f= fopen("doc.txt", "r");
    while (feof(f) == 0) {
        copias = 0;
        fgets(cadena, 130, f);
        match_num = get_ocurr(cadena);
        copias = 0;
        //printf("%d\n", i);
        //printf ("Cadena: %s\nOCURR: %d---CARD_I: %d---CARD_J: %d\n", cadena, match_num, card[i], card[j]);
        while (copias < card[i]) {
            k = 0;
            j = i + 1;
            while (k < match_num) { //no es +2
                //printf("JOTA: %d\n", j);
                card[j] += 1;
                j++;
                k++;
            }
            copias++;
        }
        //printf ("Cadena: %s\nOCURR: %d---CARD_I: %d---CARD_J: %d\n", cadena, match_num, card[i], card[j - 1]);
        //printf("%d\n", i);
        tot_sum += card[i];
        //printf("TOT_SUM: %d\n", tot_sum);
        i++;
    }
    //printf("%d--%d--%d--%d--%d--%d\n", card[1], card[2], card[3], card[4], card[5], card[6]);
    card[195] = 0;
    fclose(f);
    printf("Los puntos totales son: %d\n", tot_sum);
}