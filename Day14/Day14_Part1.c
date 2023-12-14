#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 100
#define LINE_SIZE 109

void read_file(char **map)
{
    FILE *f;
    int line = 1;

    f = fopen("doc.txt","r");
    map[0] = "####################################################################################################";
    while (feof(f) == 0) {
        fgets(map[line], LINE_SIZE, f);
        line++;
    }
    fclose(f);
}

void print_map(char **map)
{
    read_file(map);
    int line = 2, i = 0, temp_line = 0;
    while (line < MAX_LINE + 1) {
        i = 0;
        while (map[line][i] != '\0') {
            temp_line = line;
            if (map[line][i] == 'O') {
                while (map[temp_line - 1][i] != '#' && map[temp_line - 1][i] != 'O' && temp_line > 1) {
                    map[temp_line - 1][i] = map[temp_line][i];
                    map[temp_line][i] = '.';
                    temp_line--;
                }
            }
            i++;
        }
        line++;
    }
    //for (int l = 1; l < MAX_LINE + 1; l++)
    //    printf("%s\n", map[l]);
}

int get_O(char *cadena)
{
    int counter = 0;
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (cadena[i] == 'O')
            counter++;
    }
    return counter;
}

int main() {
    int *second_half;
    int line = 1, sec_count = MAX_LINE, O_counter = 0, total_load = 0;
    char **map;
    map = malloc(sizeof(char*) * MAX_LINE + 1);
    second_half = malloc(sizeof(int*) * MAX_LINE + 1);
    for (int i = 1; i <= MAX_LINE; i++) {
        map[i] = malloc(LINE_SIZE);
        second_half[i] = sec_count;
        sec_count--;
        //printf("I: %d---SEC: %d\n", i, second_half[i]);
    }
    //printf("This %d\n", second_half[100]);
    print_map(map);
    while (line < MAX_LINE + 1) {
        O_counter = get_O(map[line]);
        printf("Ocount: %d\n", O_counter);
        total_load += (O_counter * second_half[line]);
        printf("LINE VALUE: %d\n", second_half[line]); //Entra bien
        line++;
    }
    printf("La carga total es de: %d\n", total_load);
    free(map);
    free(second_half);
}