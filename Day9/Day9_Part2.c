#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define NUMBER_PER_LINE 21

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

int get_full_nums(int **full_nums, int *num)
{
    int counter = 1, num_counter = 1, next_num = 1;
    full_nums[0] = num;
    for (int k = 1; k < NUMBER_PER_LINE; k++) {
        full_nums[k] = malloc(sizeof(int*) * (NUMBER_PER_LINE - k + 1));
    }
    while (full_zeroes(full_nums[counter - 1], num_counter) != 0) {
        next_num = 1;
        for(int i = 0; i < NUMBER_PER_LINE - num_counter; i++) {
            full_nums[counter][i] = full_nums[counter - 1][next_num] - full_nums[counter - 1][i];
            next_num++;
        }
        num_counter++;
        counter++;
    }
    return counter;
}

int get_placeholder(int **full_num, int size)
{
    int value = 0;
    size -= 2;
    if (size == 20)
        size--;
    while (size >= 0) {
        value =  full_num[size][0]- value;
        size--;   
    }
    return value;
}

int main()
{
    FILE *f;
    int *num;
    int **full_nums;
    int size = 0, value = 0;
    char cadena[255];
    full_nums = malloc(sizeof(int*) * NUMBER_PER_LINE);
    f = fopen("doc.txt","r");

    while (feof(f) == 0) {
        fgets(cadena, 255, f);
        num = get_line_numbers(cadena);
        size = get_full_nums(full_nums, num);
        value += get_placeholder(full_nums, size);
    }
    fclose(f);
    printf("Value: %d\n", value);
}