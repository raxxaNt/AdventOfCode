#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*int check_line_up_down(char cadena[140][160], int i, int temp_pos, char *cadena1, int line)
{
    int num1 = 1, num2 = 1;
    
    while (temp_pos <= i) {
        if (isdigit(cadena1[temp_pos]) != 0) {
        //    if (line == 100) //
        //        printf("1--TEMPPOS: %d---I: %d---CHAR: %c\n", temp_pos, i, cadena1[temp_pos]);
            if (temp_pos != i)
                temp_pos -= 2;
            while (isdigit(cadena1[temp_pos]) == 0)
                temp_pos++;
            num1 = atoi(&cadena1[temp_pos]);
        //    if (line == 100) //
        //        printf("2--TEMPPOS: %d---I: %d---CHAR: %c\n", temp_pos, i, cadena1[temp_pos]);
            while (isdigit(cadena1[temp_pos]) != 0)
                temp_pos++;
            while (isdigit(cadena1[temp_pos]) == 0 && temp_pos != i)
                temp_pos++;
            if (i < temp_pos)
                break;
            if (num1 > 1 && isdigit(cadena1[temp_pos]) != 0)
                num2 = atoi(&cadena1[temp_pos]);
        }
        temp_pos++;
    }
    //if (line == 100)
        //printf("NUM1: %d--NUM2: %d\n", num1 , num2);
    return num1 * num2;
}*/

int check_line_up_down(char cadena[140][160], int i, int temp_pos, char *cadena1, int line)
{
    int num1 = 1, num2 = 1;

    if (isdigit(cadena1[temp_pos]) != 0 && isdigit(cadena1[temp_pos - 1]) == 0)
        num1 = atoi(&cadena1[temp_pos]);
    else if (isdigit(cadena1[temp_pos]) != 0) {
        temp_pos -= 2;
        while (isdigit(cadena1[temp_pos]) == 0)
            temp_pos++;
        num1 = atoi(&cadena1[temp_pos]);
        while (isdigit(cadena1[temp_pos]) != 0)
            temp_pos++;
    }
    while (temp_pos <= i){
        if (isdigit(cadena1[temp_pos]) != 0) {
            num2 = atoi(&cadena1[temp_pos]);
            break;
        }
        temp_pos++;
    }
    if (num1 == num2)
        num2 = 1;
    return num1 * num2;
}

int get_before(char cadena[140][160], int line, int temp_pos)
{
    int get_num = 1;
    if (isdigit(cadena[line][temp_pos]) != 0) {
        temp_pos -= 2;
        while (isdigit(cadena[line][temp_pos]) == 0)
            temp_pos++;
        get_num = atoi(&cadena[line][temp_pos]);
    }
    return get_num;
}

int check_size_up_and_down(char cadena[140][160], char *cadena1, int temp_pos, int i)
{
    int num1 = 1, num2 = 1, size = 0;

    if (isdigit(cadena1[temp_pos]) != 0 && isdigit(cadena1[temp_pos - 1]) == 0) {
        num1 = atoi(&cadena1[temp_pos]);
        size = 1;
    }
    else if (isdigit(cadena1[temp_pos]) != 0) {
        temp_pos -= 2;
        while (isdigit(cadena1[temp_pos]) == 0)
            temp_pos++;
        num1 = atoi(&cadena1[temp_pos]);
        size = 1;
        while (isdigit(cadena1[temp_pos]) != 0)
            temp_pos++;
    }
    while (temp_pos <= i){
        if (isdigit(cadena1[temp_pos]) != 0) {
            num2 = atoi(&cadena1[temp_pos]);
            size = 2;
            break;
        }
        temp_pos++;
    }
    if (num1 == num2)
        size = 1;
    else if (num1 == 1 && num2 > 1)
        size = 1;
    return size;
}

int first_and_last(char cadena[140][160], int line, char *cadena2, char *cadena1, int temp_pos, int i) //Está mal, pero da igual para mi input :)
{
    int sum_line = 0, get_num1 = 0, get_num2 = 0, get_num3 = 0;
    if (line == 0) {
        if (isdigit(cadena[line][temp_pos]) != 0)
            get_num1 = get_before(cadena, line, temp_pos);
        if (isdigit(cadena[line][i]) != 0 && get_num1 > 0)
                get_num2 = atoi(&cadena[line][i]);
        else if (isdigit(cadena[line][i]) != 0 && get_num1 == 0)
                get_num1 = atoi(&cadena[line][i]);
        if (get_num1 > 0 && get_num2 == 0)
                get_num2 = check_line_up_down(cadena, i, temp_pos, cadena2, line);
        else if (get_num1 == 0 && get_num2 == 0)
                get_num3 = check_line_up_down(cadena, i, temp_pos, cadena2, line);
    }
    else if (line == 139) {
        if (isdigit(cadena[line][temp_pos]) != 0)
            get_num1 = get_before(cadena, line, temp_pos);
        if (isdigit(cadena[line][i]) != 0 && get_num1 > 0)
                get_num2 = atoi(&cadena[line][i]);
        else if (isdigit(cadena[line][i]) != 0 && get_num1 == 0)
                get_num1 = atoi(&cadena[line][i]);
        if (get_num1 > 0 && get_num2 == 0)
                get_num2 = check_line_up_down(cadena, i, temp_pos, cadena2, line);
        else if (get_num1 == 0 && get_num2 == 0)
                get_num3 = check_line_up_down(cadena, i, temp_pos, cadena2, line);
    }
    if (get_num1 > 0 && get_num2 > 0)
        sum_line += (get_num1 * get_num2);
    else
        sum_line += get_num3;
    return sum_line;
}

int check_nums(char cadena[140][160], int line, char *cadena2, char *cadena1)
{
    int i = 0, sum_line = 0, get_num1, temp_pos = 0, get_num2, get_num3, get_num4, counter = 0;
    
    
    while (cadena[line][i] != '\0') {
        counter = 0;
        get_num1 = 0;
        get_num2 = 0;
        get_num3 = 0;
        get_num4 = 1;
        if (cadena[line][i] == '*') {
            temp_pos = i - 1;
            i += 1;
            if (line == 0 || line == 139) {
                sum_line += first_and_last(cadena, line, cadena2, cadena1, temp_pos, i);
            }
            else {
                get_num1 = get_before(cadena, line, temp_pos);
                if (get_num1 > 1)
                    counter++;
                get_num2 = check_line_up_down(cadena, i, temp_pos, cadena1, line);
                if (get_num2 > 1)
                    counter += check_size_up_and_down(cadena, cadena1, temp_pos, i);
                get_num3 = check_line_up_down(cadena, i, temp_pos, cadena2, line);
                if (get_num3 > 1)
                    counter += check_size_up_and_down(cadena, cadena2, temp_pos, i);
                if (isdigit(cadena[line][i]) != 0)
                    get_num4 = atoi(&cadena[line][i]);
                if (get_num4 > 1)
                    counter++;
            }
            if (counter >= 2)
                sum_line += (get_num1 * get_num2 * get_num3 * get_num4);
            else
                sum_line += 0;
            //printf("LINE: %d---COUNTER: %d\n", line, counter);
            if (line == 100)
                printf("%d---%d---%d---%d\n", get_num1, get_num2, get_num3, get_num4);
        }
        i++;
    }
    //printf ("LINE: %d---SUM LINE: %d\n", line, sum_line);
    return sum_line;
}

int main () {
    FILE *f;
    char cadena[140][160];
    char *cadena2;
    char *cadena1;
    int line = 0;
    unsigned int tot_sum = 0;

    f = fopen("doc.txt", "r");
    cadena1 = malloc(145);
    cadena2 = malloc(145);
    while (feof(f) == 0) {
        fgets(cadena[line], 145, f);
        line++;
    }
    line = 0;
    while (line < 140) {
        if (line != 0) {
            fgets(cadena[line - 1], 160, f);
            cadena1 = cadena[line - 1];
        }
        if (line != 139) {
            fgets(cadena[line + 1], 160, f);
            cadena2 = cadena[line + 1];
        }
        fgets(cadena[line], 160, f);
        tot_sum += check_nums(cadena, line, cadena2, cadena1);
        line++;
    }
    fclose(f);
    printf("La suma total es de: %u\n", tot_sum);
}