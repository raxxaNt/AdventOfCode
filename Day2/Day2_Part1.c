#include <stdio.h>
#include <ctype.h>
#include <string.h>

int check_color(char *str, int get_num, int index)
{
    while (isalpha(str[index]) == 0) {
        index++;
    }
    if (str[index] == 'r' && get_num < 13)
        return 1;
    else if (str[index] == 'g' && get_num < 14)
        return 1;
    else if (str[index] == 'b' && get_num < 15)
        return 1;
    return (0);
}

int check_num(char *str)
{
    int i = 0, get_num = 0, counter = 0;
    char *token;

    token = strtok(str, ";");
    while (token != NULL) {
        i = 0;
        while (token[i] != '\0') {
            if (isdigit(token[i]) != 0 && isdigit(token[i + 1]) != 0) {
                get_num = (token[i] - '0') * 10 + (token[i + 1] - '0');
                counter++;
                if (counter > 1 && check_color(token, get_num, i) == 0)
                    return 1;
            }
            else if (isdigit(token[i]) != 0) {
                get_num = token[i] - '0';
                counter++;
                if (counter > 1 && check_color(token, get_num, i) == 0)
                    return 1;
            }
            i++;
        }
        //printf("%s\n", token);
        token = strtok(NULL, ";");
    }
    return 0;
}
int main() {
    FILE *f;
    int game_counter = 0, tot_id = 0;
    char cadena[255];

    f = fopen("doc.txt", "r");

    while (feof(f) == 0) {
        fgets(cadena, 255, f);
        game_counter++;
        if (check_num(cadena) == 0)
            tot_id += game_counter;
    }
    fclose(f);
    printf("La suma de los ID es: %d\n", tot_id);
}