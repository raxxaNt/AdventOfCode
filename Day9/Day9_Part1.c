#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define NUMBER_PER_LINE 21 //21

int *get_line_numbers(char cadena[255])
{
    int i = 0, counter = 0;
    int *num;
    char neg = '-';

    num = malloc(sizeof(int) * NUMBER_PER_LINE);
    while (cadena[i] != '\0') {
        if (isdigit(cadena[i]) != 0)  {
            num[counter] = atoi(&cadena[i]);
            if (cadena[i - 1] == '-')
                num[counter] *= -1;
            counter++;
            while (isdigit(cadena[i + 1]) != 0)
                i++;
        }
        i++;
    }
    num[counter] = '\0';
    return num;
}

int full_zeroes(int *num, int num_counter)
{
    for (int j = 0; j < NUMBER_PER_LINE + 1 - num_counter; j++) {
        if (num[j] != 0)
            return 1;
    }
    return 0;
}

int get_zeroes(int *num, int get_num, int num_counter)
{
    int next_num = 1;
    get_num += num[NUMBER_PER_LINE - num_counter];
    if (full_zeroes(num, num_counter) != 0) {  //if ((num[NUMBER_PER_LINE - 1 - num_counter]) != 0) {
        for (int i = 0; i < NUMBER_PER_LINE - num_counter; i++) { //-1
            num[i] = num[next_num] - num[i];
            next_num++;
        }
        num_counter++;
    }
    else
        return get_num;
    return get_zeroes(num, get_num, num_counter);
}

int main()
{
    FILE *f;
    int *num;
    int num_diff = 0;
    char cadena[255];
    f = fopen("doc.txt","r");

    while (feof(f) == 0) {
        fgets(cadena, 255, f);
        num = get_line_numbers(cadena);
        num_diff += get_zeroes(num, 0, 1);
        printf("NUMDIFF: %d\n", num_diff);
    }
    fclose(f);
    //printf("NUM_DIFF: %d\n", num_diff);
}