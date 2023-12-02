#include <stdio.h>
#include <ctype.h>

int look_for_number(char *str) {
    int start = 0, end = 0, get_num1 = 0, get_num2 = 0, final_num = 0;

    while (str[end] != '\0')
        end++;
    end -= 1;
    while (str[start] != '\0') {
        if (isdigit(str[start]) != 0) {
            get_num1 = str[start] - '0';
            break;        
        }
        start++;
    }
    while (end >= 0) {
        if (isdigit(str[end]) != 0) {
            get_num2 = str[end] - '0';
            break;        
        }
        end--;
    }
    final_num = get_num1 * 10 + get_num2;
    return (final_num);
}

int main() {
    FILE *f;
    int tot_sum = 0, get_num = 0;
    char cadena[255];

    f = fopen("doc.txt","r");
    while (feof(f) == 0) {
        fgets(cadena, 255, f);
        get_num = look_for_number(cadena);
        tot_sum += get_num;
    }
    fclose(f);
    printf("La suma total es: %d", tot_sum);
    return 0;
}