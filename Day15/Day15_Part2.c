#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_OF_BOXES 256

int get_algorithm(char *str)
{
    int i = 0, ascii_value = 0, current_value = 0;
    while (str[i] != '-' && str[i] != '=') {
        ascii_value = str[i];
        current_value += ascii_value;
        current_value *= 17;
        current_value %= 256;
        i++;
    }
    return current_value;
}

char *read_file(char *cadena)
{
    FILE *f;
    cadena = malloc(23000);
    f = fopen("doc.txt","r");

    fgets(cadena, 23000, f);
    int size = strlen(cadena);
    cadena[size] = '\0';
    cadena = realloc(cadena, size);
    
    fclose(f);
    return cadena;
}

void get_allocated(char ***box, int **lens)
{
    for (int i = 0; i < NUM_OF_BOXES; i++) {
        box[i] = malloc(sizeof(char*) * 100);
        for (int j = 0; j < 100; j++) {
            box[i][j] = malloc(8);
        }
    }
    for (int l = 0; l < NUM_OF_BOXES; l++)
        lens[l] = malloc(sizeof(int) * 100);
}

int check_operator(char *token)
{
    int i = 0;
    while (token[i] != '\0') {
        if (token[i] == '-')
            return 1;
        i++;
    }
    return 0;
}

int get_size(char *str)
{
    int i = 0;
    while (str[i] != '-' && str[i] != '=') {
        i++;
    }
    return i;
}

void order_labels(char ***box, int hash_value, int array_pos)
{
    while (box[hash_value][array_pos][0] != '\0') {
        box[hash_value][array_pos] = box[hash_value][array_pos + 1];
        array_pos++;
    }
}

void print_map(char ***box, char *cadena)
{
    int array_pos = 0, hash_value = 0, size = 0;
    char *token = malloc(8);
    token = strtok(cadena, ",");
    if (token != NULL) {
        while (token != NULL) {
            array_pos = 0;
            hash_value = get_algorithm(token);
            size = get_size(token);
            while(box[hash_value][array_pos][0] != '\0') {
                if (strncmp(box[hash_value][array_pos], token, size) == 0) {
                    if (check_operator(token) == 1)
                        order_labels(box, hash_value, array_pos);
                    else
                        box[hash_value][array_pos] = token;
                    break;
                }
                array_pos++;
            }
            if (box[hash_value][array_pos][0] == '\0' && check_operator(token) == 0)
                box[hash_value][array_pos] = token;
            token = strtok(NULL, ",");
        }
    }
}

void get_nums(char ***box, int **lens)
{
    int size = 0;
    for (int m = 0; m < NUM_OF_BOXES; m++) {
        for (int n = 0; box[m][n][0] != '\0'; n++) {
            size = strlen(box[m][n]);
            size -= 1;
            lens[m][n] = atoi(&box[m][n][size]);
        }
    }
}

int get_focusing_power(char ***box, int **lens)
{
    int box_num = 0, array_pos = 0, focus_power = 0;
    while (box_num < NUM_OF_BOXES) {
        array_pos = 0;
        while (box[box_num][array_pos][0] != '\0') {
            focus_power += ((box_num + 1) * (array_pos + 1) * lens[box_num][array_pos]);
            array_pos++;
        }
        box_num++;
    }
    return focus_power;
}

int main() {
    FILE *f;
    int value = 0;
    char ***box = malloc(sizeof(char**) * NUM_OF_BOXES);
    int **lens = malloc(sizeof(int*) * NUM_OF_BOXES);
    char *cadena;
    get_allocated(box, lens);
    cadena = read_file(cadena);
    print_map(box, cadena);
    get_nums(box, lens);
    value = get_focusing_power(box, lens);
    /*for (int m = 0; m < NUM_OF_BOXES; m++) {
        printf("Box %d: ", m);
        for (int n = 0; box[m][n][0] != '\0'; n++) {
            printf("%s---", box[m][n]);
            printf("%d-----", lens[m][n]);
        }
        printf("\n");
    }*/
    printf("El total value es de: %d\n", value);
    free(cadena);
    free(lens);
    free(box);
}