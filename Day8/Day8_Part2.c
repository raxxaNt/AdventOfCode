#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAP_SIZE 800
#define INSTRUCTIONS 293
#define LINE_SIZE 20

char *get_node(char c, char **map, int line)
{
    char *str = malloc(4);
    int i = 0, pos_node = 0;

    if (c == 'L') {
        pos_node = 7;
        while (i < 3) {
            str[i] = map[line][pos_node];
            i++;
            pos_node++;
        }
    }
    else if (c == 'R') {
        pos_node = 12;
        while (i < 3) {
            str[i] = map[line][pos_node];
            i++;
            pos_node++;
        }
    }
    str[i] = '\0';
    return str;
}

int finish_A(char **map)
{
    int line = 3, counter = 0;
    while (line < MAP_SIZE + 1)
    {
        if (map[line][2] == 'A')
            counter++;
        line++;
    }
    return counter;
}

int *get_lines(char **map, int get_a)
{
    int *lines;
    int line = 3, counter = 0;
    lines = malloc(sizeof(int) * get_a);
    while (line < MAP_SIZE + 1)
    {
        if (map[line][2] == 'A') {
            lines[counter] = line;
            counter++;
        }
        line++;
    }
    return lines;
}


int get_next_line(int line, char *str, char **map)
{
    while (line < MAP_SIZE + 1) {
        if (strncmp(map[line], str, 3) == 0)
            return line;
        line++;
        if (line == MAP_SIZE + 1)
            line = 3;
    }
    return line;
}

int long long get_steps(char *instructions, char **map, int a_limit, int *lines)
{
    int steps = 0, start = 0, z_counter = 0, z_loop = 0;
    int long long counter = 0;
    char **temp_str;
    temp_str = malloc(sizeof(char*) * a_limit);
    while (steps < INSTRUCTIONS) {
       start = 0;
       while (start < a_limit) {
            temp_str[start] = get_node(instructions[steps], map, lines[start]);
            lines[start] = get_next_line(lines[start], temp_str[start], map);
            start++;
            //printf("start: %d---a_limit: %d\n", start, a_limit);
            if (start == a_limit) {
                z_counter = 0;
                z_loop = 0;
                while (z_loop < a_limit) {
                    if (temp_str[z_counter][2] == 'Z')
                        z_counter++;
                    printf("%s---", temp_str[z_loop]);
                    z_loop++;
                }
                printf("\n");
            }
       }
       counter++;
       printf("COUNTER: %lld\n", counter);
       steps++;
        if (z_counter == 6)
            return counter;
        if (steps == INSTRUCTIONS)
            steps = 0;
    }
    return counter;
}

int main()
{
    FILE *f;
    char *direction;
    char **map;
    int line = 0, get_a = 0;
    int *lines;
    direction = malloc(INSTRUCTIONS + 1);
    map = malloc(sizeof(char*) * (MAP_SIZE + 1));

    f = fopen("doc.txt","r");
    while (feof(f) == 0) {
        if (line == 0)
            fgets(direction, INSTRUCTIONS + 1, f);
        else {
            map[line] = malloc(LINE_SIZE);
            fgets(map[line], LINE_SIZE ,f);
        }
        line++;
    }
    fclose(f);
    get_a = finish_A(map);
    lines = get_lines(map, get_a);
    int long long lol = get_steps(direction, map, get_a, lines);
    printf("COUNTER: %lld", lol);
}