#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file(char *cadena)
{
    FILE *f;
    cadena = malloc(23000);
    f = fopen("doc.txt","r");

    fgets(cadena, 23000, f);
    int size = strlen(cadena);
    cadena[size] = '\0';
    cadena = realloc(cadena, size);
    //printf("%d\n", size);
    //printf("%s\n", cadena);
    //printf("%c\n", cadena[size - 1]);
    
    fclose(f);
    return cadena;
}

int get_algorithm(char *str, int len)
{
    int i = 0, ascii_value = 0, current_value = 0;
    str[len] = '\0';
    while (str[i] != '\0') {
        ascii_value = str[i];
        current_value += ascii_value;
        current_value *= 17;
        current_value %= 256;
        i++;
    }
    return current_value;
}

int main() {
    FILE *f;
    int value = 0, len = 0;
    char *cadena;
    char *token = malloc(8);
    cadena = read_file(cadena);
    token = strtok(cadena, ",");
    if (token != NULL) {
        while (token != NULL) {
            len = strlen(token);
            value += get_algorithm(token, len);
            token = strtok(NULL, ",");
        }
    }
    printf("El total value es de: %d\n", value);
    free(cadena);
    free(token);
}