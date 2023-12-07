//Darle un valor a cada linea, luego ver su carta alta sumando valores y luego hacer un compare y un swap para ordenar el array
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define HANDS 1000

int get_hand_values(char *hand)
{
    int counter1 = 1, counter = 0, counter2 = 1, i = 0, j = 0, k = 0;
    while (i < 5) {
        k = 0;
        while (k < i) {
            if (hand[i] == hand[k]) {
                i++;
                continue;
            }
            k++;
        }
        counter = 1;
        j = i + 1;
        while (j < 5) {
            if (hand[i] == hand[j])
                counter++;
            j++;
        }
        if (counter > 1 && counter1 > 1)
            counter2 = counter;
        else if (counter > 1)
            counter1 = counter;
        i++;
    }
    if (counter1 == 2 && counter2 == 2)
        return 250;
    else if ((counter1 == 3 && counter2 == 2) || (counter1 == 2 && counter2 == 3))
        return 350;
    counter = (counter1 * counter2) * 100;
    return counter;
}

void order_values(char **hand, int hand_value[HANDS], int bid[HANDS])
{
    int hand_counter = 0, temp = 0, check_every = 0;
    char *temp_str;
    
    while (hand_counter < HANDS - 1) {
        check_every = hand_counter + 1;
        while (check_every < HANDS) {
            if (hand_value[hand_counter] > hand_value[check_every]) {
                temp = hand_value[hand_counter];
                hand_value[hand_counter] = hand_value[check_every];
                hand_value[check_every] = temp;
                temp_str = hand[hand_counter];
                hand[hand_counter] = hand[check_every];
                hand[check_every] = temp_str;
                temp = bid[hand_counter];
                bid[hand_counter] = bid[check_every];
                bid[check_every] = temp;
            }
            check_every++;
        }
        hand_counter++;
    }
}

void change_letter(char **temp_hand)
{
    int i = 0, hand = 0;
    while (hand < HANDS) {
        i = 0;
        while (i < 5) {
            if (temp_hand[hand][i] == 'T')
                temp_hand[hand][i] = 'A';
            else if (temp_hand[hand][i] == 'J')
                temp_hand[hand][i] = 'B';
            else if (temp_hand[hand][i] == 'Q')
                temp_hand[hand][i] = 'C';
            else if (temp_hand[hand][i] == 'K')
                temp_hand[hand][i] = 'D';
            else if (temp_hand[hand][i] == 'A')
                temp_hand[hand][i] = 'E';
            i++;
        }
        hand++;
    }
}

void final_order(char **temp_hand, int bid[HANDS], int hand_value[HANDS])
{
    int hand = 0, j = 0, value = 100, temp_bid = 0;
    char *temp;
    while (hand < HANDS) {
        while (hand_value[hand] == value) {
            j = hand + 1;
            while (j < HANDS && hand_value[j] == value) {
                if (strcmp(temp_hand[hand], temp_hand[j]) > 0) {
                    temp = temp_hand[hand];
                    temp_hand[hand] = temp_hand[j];
                    temp_hand[j] = temp;
                    temp_bid = bid[hand];
                    bid[hand] = bid[j];
                    bid[j] = temp_bid;
                }
                j++;
            }
            hand++;
        }
        value += 50;
    }
}

int main() {
    FILE *f;
    int line = 0, tot_sum = 0, bid_res = 0;
    int bid[HANDS], hand_value[HANDS];
    char **hand, cadena[15], **temp_hand;

    hand = malloc(sizeof(char*) * HANDS);
    temp_hand = malloc(sizeof(char*) * HANDS);
    f = fopen("doc.txt","r");
    while (feof(f) == 0) {
        hand[line] = malloc(sizeof(char) * 10);
        temp_hand[line] = malloc(sizeof(char) * 10);
        fgets(cadena, 15, f);
        strncpy(hand[line], cadena, 5);
        bid[line] = atoi(&cadena[5]);
        line++;
    }
    for (int i = 0; i < HANDS; i++)
        hand_value[i] = get_hand_values(hand[i]);
    order_values(hand, hand_value, bid);
    for (int i = 0; i < HANDS; i++)
        strcpy(temp_hand[i], hand[i]);
    change_letter(temp_hand);
    final_order(temp_hand, bid, hand_value);
    
    
    for (int i = 0; i < HANDS; i++) {//Bucle de comprobación
        bid_res = bid[i] * (i + 1);
        tot_sum += bid_res;
    }
    //printf("CADENA: %s---VALUE %d---BID: %d---TEMP: %s\n", hand[i], hand_value[i], bid[i], temp_hand[i]);
    printf("El resultado es: %d\n", tot_sum);
}