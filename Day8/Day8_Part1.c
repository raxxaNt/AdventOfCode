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

int get_steps(char *instructions, char **map)
{
    int steps = 0, counter = 0, line = 746;
    char *temp_str;

    while (steps < INSTRUCTIONS) {
        temp_str = get_node(instructions[steps], map, line);
        printf("%d\n", line);
        if (strcmp(temp_str, "ZZZ") == 0) {
            printf("%s\n", temp_str);
            counter++;
            break;
        }
        while (line <= MAP_SIZE) {
            if (strncmp(map[line], temp_str, 3) == 0)
                break;
            line++;
            if (line == MAP_SIZE + 1)
                line = 3;
        }
        steps++;
        if (steps == INSTRUCTIONS)
            steps = 0;
        counter++;
    }
    return counter;
}

int main()
{
    FILE *f;
    char *direction;
    char **map;
    int line = 0;
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
    int lol = get_steps(direction, map);
    printf("COUNTER: %d", lol);
}

    