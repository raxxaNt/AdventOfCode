#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int check_up_and_down(char cadena[140][160], int line, int i, int temp_pos, char *cadena2, char *cadena1)
{
    if (line == 0) {
        while (temp_pos <= i) {
            if ((cadena2[temp_pos] != '.' && isdigit(cadena2[temp_pos]) == 0 && temp_pos != -1 && temp_pos != 140)
                || (cadena2[i] != '.' && isdigit(cadena2[i]) == 0 && i != 140))
                return 1;
            temp_pos++;
        }
    }
    else if (line == 139) {
        while (temp_pos <= i) {
            if ((cadena1[temp_pos] != '.' && isdigit(cadena1[temp_pos]) == 0 && temp_pos != -1 && temp_pos != 140)
                || (cadena1[i] != '.' && isdigit(cadena1[i]) == 0 && i != 140))
                return 1;
            temp_pos++;
        }
    }
    else {
        while (temp_pos <= i) {
            if ((cadena2[temp_pos] != '.' && isdigit(cadena2[temp_pos]) == 0 && temp_pos != -1 && temp_pos != 140)
                || (cadena1[temp_pos] != '.' && isdigit(cadena1[temp_pos]) == 0 && temp_pos != -1 && temp_pos != 140)
                    || (cadena2[i] != '.' && isdigit(cadena2[i]) == 0 && i != 140)
                || (cadena1[i] != '.' && isdigit(cadena1[i]) == 0 && i != 140)) 
                return 1;
            temp_pos++;
        }
    }
    //printf("%d\n", line);
    return 0;
}

int check_nums(char cadena[140][160], int line, char *cadena2, char *cadena1)
{
    int i = 0, sum_line = 0, get_num = 0, temp_pos = 0;
    
    while (cadena[line][i] != '\0') {
        if (isdigit(cadena[line][i]) != 0) {
            temp_pos = i - 1;
            get_num = atoi(&cadena[line][i]);
            while(isdigit(cadena[line][i]) != 0)
                i++;
            if ((cadena[line][temp_pos] != '.' && temp_pos != -1) || (cadena[line][i] != '.' && i != 140) || (check_up_and_down(cadena, line, i, temp_pos, cadena2, cadena1) == 1)) {
                sum_line += get_num;
            //    printf("LINE: %d---GET_NUM: %d\n", line, get_num);
            }
        }
        i++;
    }
    //printf("LINE: %d---SUM_LINE: %d\n", line, sum_line);
    return sum_line;
}

int main () {
    FILE *f;
    char cadena[140][160];
    char *cadena2;
    char *cadena1;
    int line = 0, tot_sum = 0;

    f = fopen("doc.txt", "r");
    cadena1 = malloc(145);
    cadena2 = malloc(145);
    while (feof(f) == 0) {
        fgets(cadena[line], 145, f);
        //printf("LINE %d-------%s\n", line, cadena[line]);
        line++;
    }
    //printf("%s\n", cadena[55]);
    line = 0;
    while (line < 140) {
        if (line != 0) {
            fgets(cadena[line - 1], 160, f);
            cadena1 = cadena[line - 1];
            //printf("Cadena1: %s\n", cadena1);
        }
        if (line != 139) {
            fgets(cadena[line + 1], 160, f);
            cadena2 = cadena[line + 1];
           // printf("Cadena2: %s\n", cadena2);
        }
        fgets(cadena[line], 160, f);
        //printf("Cadena: %s\n", cadena[line]);
        tot_sum += check_nums(cadena, line, cadena2, cadena1);
        line++;
       // printf("Primer: %s\nSegon: %s\nTercer: %s\n", cadena1, cadena[line], cadena2);
    }
    fclose(f);
    printf("La suma total es de: %d\n", tot_sum);
}