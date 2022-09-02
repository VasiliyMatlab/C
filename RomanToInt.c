#include <stdio.h>
#include <string.h>

typedef unsigned int uint;
static uint RomanToInt(char *Roman);
static uint Choise(char c);

int main(){
    char Roman[16];
    printf("Enter a roman number: ");
    scanf("%s",Roman);
    printf("Integer number: %d", RomanToInt(Roman));
    return 0;
}

static uint RomanToInt(char *Roman){
    uint number = 0, len = strlen(Roman);
    for (uint i = 0; i < len; i++){
        if ((i == len - 1) || (Choise(Roman[i]) >= Choise(Roman[i+1])))
            number += Choise(Roman[i]);
        else
            number -= Choise(Roman[i]);
    }
    return number;
}

static uint Choise(char c){
    uint number;
    switch (c){
        case 'I':
            number = 1;
            break;
        case 'V':
            number = 5;
            break;
        case 'X':
            number = 10;
            break;
        case 'L':
            number = 50;
            break;
        case 'C':
            number = 100;
            break;
        case 'D':
            number = 500;
            break;
        case 'M':
            number = 1000;
            break;
        default:
            number = 0;
    }
    return number;
}