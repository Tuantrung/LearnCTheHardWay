#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dbg.h"

#define MAX_DATA 100

typedef enum EyeColor {
    BLUE_EYES, GREEN_EYES, BROWN_EYES,
    BLACK_EYES, OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
    "Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person {
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
} Person;

void strip(char * input_str) 
{
    int i=0;
    int j=0;
    while(input_str[i]) {
        if (!isspace(input_str[i])) {
            input_str[j] = input_str[i];
            j++;
        }
        i++;
    }
    input_str[j] = '\0';
}
void read_input (char * input_str, int size)
{
    char c = '\0';
    int i = 0;

    while (i < size-1 && scanf("%c", &c) == 1) {
        if (i == 0 && isspace(c)){
            continue;
        }

        if (c != '\n' && !isspace(c)) {
            input_str[i] = c;
            i++;
        } else if (c == '\n') {
            input_str[i] = '\0';
            return;
        }
    }

    input_str[i] = '\0';
}

int main(int argc, char *argv[])
{
    Person you = {.age = 0};
    int i = 0;
    char *in = NULL;
    char tmp[MAX_DATA];

    printf("What's your First Name? ");
    // in = fgets(you.first_name, MAX_DATA - 1, stdin);
    read_input(you.first_name, MAX_DATA);
    // fscanf(stdin, "%50s", you.first_name);
    // in = fgets(tmp, MAX_DATA - 1, stdin);
    // check(in != NULL, "Failed to read first name.");
    // strip(you.first_name);

    printf("What's your Last Name? ");
    // in = fgets(you.last_name, MAX_DATA - 1, stdin);
    // check(in != NULL, "Failed to read first name.");
    // strip(you.last_name);
    read_input(you.last_name, MAX_DATA);

    printf("How old are you? ");
    // int rc = fscanf(stdin, "%d", &you.age);
    // int rc = scanf("%d", &you.age);
    in = fgets(tmp, MAX_DATA - 1, stdin);
    // check(rc > 0, "Failed to read first name.");
    you.age = atoi(in);

    printf("What color are your eyes:\n");
    for(i = 0; i<= OTHER_EYES; i++) {
        printf("%d %s\n", i + 1, EYE_COLOR_NAMES[i]);
    }
    printf("> ");

    int eyes = -1;
    // rc = fscanf(stdin, "%d", &eyes);
    // rc = scanf("%d", &eyes);
    in = fgets(tmp, MAX_DATA - 1, stdin);
    eyes = atoi(in);
    // check(rc > 0, "You have to enter a number");

    you.eyes = eyes - 1;
    check(you.eyes <= OTHER_EYES && you.eyes >= 0, "Do it right, that's not an option.");

    printf("How much do you make an hour? ");
    // rc = fscanf(stdin, "%f", &you.income);
    // int rc = scanf("%f", &you.income);
    in = fgets(tmp, MAX_DATA - 1, stdin);
    you.income = strtof(tmp, &in);
    // check(rc > 0, "Enter a floating point number.");

    printf("----- RESULTS -----\n");

    printf("First Name: %s", you.first_name);
    printf("Last Name: %s", you.last_name);
    printf("Age: %d\n", you.age);
    printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
    printf("Income: %f\n", you.income);

    return 0;
error:

    return -1;
}