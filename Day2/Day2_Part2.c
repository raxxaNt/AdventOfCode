#include <stdio.h>
#include <ctype.h>
#include <string.h>

int check_color(char *str, int index)
{
    while (isalpha(str[index]) == 0) {
        index++;
    }
    if (str[index] == 'r')
        return 1;
    else if (str[index] == 'g')
        return 2;
    else if (str[index] == 'b')
        return 3;
    return (0);
}

int check_num(char *str)
{
    int total_num = 0, counter = 0, i = 0, get_num = 0;
    int high_red = 0, high_green = 0, high_blue = 0;
   
    while (str[i] != '\0') {
        if (isdigit(str[i]) != 0 && isdigit(str[i + 1]) != 0) {
            counter++;
            if (counter > 1) {
                get_num = (str[i] - '0') * 10 + (str[i + 1] - '0');
                if (check_color(str, i) == 1 && high_red <= get_num)
                    high_red = get_num;
                else if (check_color(str, i) == 2 && high_green <= get_num)
                    high_green = get_num;
                else if (check_color(str, i) == 3 && high_blue <= get_num)
                    high_blue = get_num;
            }
            i++;
        }
        else if (isdigit(str[i]) != 0) {
            counter++;
            if (counter > 1) {
                get_num = str[i] - '0';
                if (check_color(str, i) == 1 && high_red <= get_num)
                    high_red = get_num;
                else if (check_color(str, i) == 2 && high_green <= get_num)
                    high_green = get_num;
                else if (check_color(str, i) == 3 && high_blue <= get_num)
                    high_blue = get_num;
            }       
        }
        i++;
    }
    printf("R:%d--G:%d--B:%d\n", high_red, high_green, high_blue);
    get_num = high_blue * high_green * high_red;
    return get_num;
}
int main() {
    FILE *f;
    int game_counter = 0, tot_id = 0;
    char cadena[255];

    f = fopen("doc.txt", "r");
    int i = 0; //
    while (feof(f) == 0) {
        fgets(cadena, 255, f);
        game_counter = check_num(cadena);
        tot_id += game_counter;
        i++; //
        printf("Linea %d: %d\n", i, tot_id);
    }
    fclose(f);
    printf("La suma total es: %d\n", tot_id);
}