#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define NUMBERS 9

int check_first_number(char *str, int index)
{
    int i = 0, j = 0;
    char nums[9][7] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char *ptr;
    
    ptr = (char*)malloc(sizeof(char) * 6);
    ptr = &str[index];
    while (j < NUMBERS) {
        i = 0;
        if (ptr[i] == nums[j][i]) {
            while (ptr[i] == nums[j][i])
                i++;
            if (nums[j][i] == '\0' && nums[j][i - 1] == ptr[i - 1])
                return (j + 1);
        }
        j++;
    }
    return 0;
}

int check_last_number(char *str, int index)
{
    int temp_index = 0, j = 0, num_size = 0;
    char nums[9][7] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    temp_index = index;
    while (j < NUMBERS) {
        index = temp_index;
        num_size = strlen(nums[j]);
        num_size -= 1;
        if (str[index] == nums[j][num_size]) {
                while (str[index] == nums[j][num_size] && num_size != -1) {
                    index--;
                    num_size--;
                }
                if (num_size == -1)
                    return (j + 1);
        }
        j++;
    }
    return 0;
}

int look_for_number(char *str) {
    int start = 0, end = 0, get_num1 = 0, get_num2 = 0, final_num = 0;

    end = strlen(str);
    while (str[start] != '\0') {
        if (isdigit(str[start]) != 0 || check_first_number(str, start) != 0) {
            if (isdigit(str[start]) != 0)
                get_num1 = str[start] - '0';
            else
                get_num1 = check_first_number(str, start);
            break;        
        }
        start++;
    }
    while (end >= 0) {
        if (isdigit(str[end]) != 0 || check_last_number(str, end) != 0) {
            if (isdigit(str[end]) != 0)
                get_num2 = str[end] - '0';
            else
                get_num2 = check_last_number(str, end);
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
        //printf("El get num es: %d\n", get_num);
    }
    fclose(f);
    printf("La suma total es: %d", tot_sum);
    return 0;
}