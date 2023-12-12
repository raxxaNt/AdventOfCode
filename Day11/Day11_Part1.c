#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DOC_LINES 140 //140 //12
#define DOC_LINE_SIZE 145 //142 //15
#define REAL_DOC_LINE_SIZE 140 //140 //13

int get_num_size(char **map, int map_row_size)
{
    int line = 0, i = 0, num = 0;
    while (line < map_row_size) {
        i = 0;
        while (map[line][i] != '\0') {
            if (map[line][i] == '#') {
                num++;
                //printf("LINE: %d---POS: %d\n", line, i);
            }
            i++;
        }
        line++;
    }
    return num;
}

int get_line(char **map, int size, int direction, int map_row_size)
{
    int line = 0, i = 0, num = 0;
    while (line < map_row_size && num < size) {
        i = 0;
        while (map[line][i] != '\0') {
            if (map[line][i] == '#') {
                num++;
                if (num == direction)
                    return line;
            }
            i++;
        }
        line++;
    }
    return line;
}

int get_pos(char **map, int size, int direction, int map_row_size)
{
    int line = 0, i = 0, num = 0;
    while (line < map_row_size && num < size) {
        i = 0;
        while (map[line][i] != '\0') {
            if (map[line][i] == '#') {
                num++;
                if (num == direction)
                    return i;
            }
            i++;
        }
        line++;
    }
    return i;
}

int get_value(char **map, int size, int map_row_size)
{
    int num = 1, value = 0, next_num = 0, line = 0, pos = 0, next_line = 0, next_pos = 0, temp_pos = 0, compare = 0;
    while (num < size) {
        next_num = num + 1;
        line = get_line(map, size, num, map_row_size);
        pos = get_pos(map, size, num, map_row_size);
        while (next_num <= size) {
            next_line = get_line(map, size, next_num, map_row_size);
            next_pos = get_pos(map, size, next_num, map_row_size);
            temp_pos = next_pos - pos;
            if (temp_pos < 0)
                temp_pos *= -1;
            //printf("NXTLINE: %d---NXTPOS: %d---LINE: %d---POS: %d\n", next_line, next_pos, line, pos);
            compare = value; //
            value += ((next_line - line) + temp_pos); //¿¿1??
            //if (num == 7)
            //    printf("NXTLINE: %d---NXTPOS: %d---LINE: %d---POS: %d---VALUE: %d\n", next_line, next_pos, line, pos, value - compare);
            next_num++;
        }
        num++;
    }
    return value;
}

int row_check(char **map, int line) // 0 si no hay nada
{
    int i = 0;
    while (map[line][i] != '\0') {
        if (map[line][i] == '#')
            return -1;
        i++;
    }
    return line;
}

int col_check(char **map, int pos, int row_cuant) // 0 si no hay nada
{
    int line = 0;
    while (line < row_cuant) {
        if (map[line][pos] == '#')
            return -1;
        line++;
    }
    return line;
}

void draw_full_map(char **map, int map_row_size)
{
    int col_counter = 0, line = 0, temp_row = 0, pos = 0;
    while (pos < DOC_LINE_SIZE + col_counter) {
        if (col_check(map, pos, map_row_size) != -1) {
            col_counter++;
            for (int k = 0; k < map_row_size; k++) {
                //map[k] = (char*)realloc(map[k], DOC_LINE_SIZE + col_counter);
                temp_row = strlen(map[k]);
                while (pos < temp_row) {
                    map[k][temp_row] = map[k][temp_row - 1];
                    temp_row--;
                }
                map[k][REAL_DOC_LINE_SIZE + col_counter] = '\0';
            }
            pos++;
        }
        pos++;
    }
}

int draw_map_row(char **map) //Works
{
    int line = 0, row_counter = 0, temp_line = 0;
    while (line < DOC_LINES + row_counter) {
        if (row_check(map, line) != -1) {
            row_counter++;
            *map = realloc(*map, sizeof(char*) * DOC_LINES + row_counter);
            temp_line = DOC_LINES + row_counter - 1;
            while (line < temp_line) {
                map[temp_line] = map[temp_line - 1];
                temp_line--;
            }
            line++; //Para hacer skip de la nueva linea
        }
        line++;
    }
    return DOC_LINES + row_counter;
}

int main() {
    FILE *f;
    char **map;
    int size = 0, map_row_size = 0;
    
    map = malloc(sizeof(char*) * DOC_LINES);
    f = fopen("doc.txt", "r");
    int line = 0;
    while (feof(f) == 0) {
        map[line] = malloc(DOC_LINE_SIZE);
        fgets(map[line], DOC_LINE_SIZE, f);
        line++;
    }
    fclose(f);
    map_row_size = draw_map_row(map);
    draw_full_map(map, map_row_size);
    for (int i = 0; i < map_row_size; i++)
        printf("%s\n", map[i]);
    printf("Size: %d\n", map_row_size);
    size = get_num_size(map, map_row_size);
    printf("Size: %d\n", map_row_size);
    int lineA = get_line(map, size, 4, map_row_size);
    int posA = get_pos(map, size, 4, map_row_size);
    //printf("%d---%d\n", lineA, posA);
    int value = get_value(map, size, map_row_size);
    printf("Value: %d\n", value);
}