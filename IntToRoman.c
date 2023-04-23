#include <stdio.h>
#include <malloc.h>

static char *IntToRoman(int num);
static int ipow(int x, int n);

int main(void){
    int number;
    printf("Enter an integer number: ");
    scanf("%d", &number);
    printf("Roman number: %s\n", IntToRoman(number));
    return 0;
}

static char *IntToRoman(int num){
    char *str = NULL;
    unsigned int k = num, len_str = 0, len_num = 0, i = 0;
    while (k != 0){
        len_num++;
        k /= 10;
    }
    while (num != 0){
        k = num - num % ipow(10,len_num-1-i);
        if (k < 10){
            switch (k){
                case 1:
                    len_str++;
                    str = (char*) realloc(str,len_str);
                    str[len_str-1] = 'I';
                    break;
                case 2:
                    len_str += 2;
                    str = (char*) realloc(str,len_str);
                    str[len_str-2] = 'I';
                    str[len_str-1] = 'I';
                    break;
                case 3:
                    len_str += 3;
                    str = (char*) realloc(str,len_str);
                    str[len_str-3] = 'I';
                    str[len_str-2] = 'I';
                    str[len_str-1] = 'I';
                    break;
                case 4:
                    len_str += 2;
                    str = (char*) realloc(str,len_str);
                    str[len_str-2] = 'I';
                    str[len_str-1] = 'V';
                    break;
                case 5:
                    len_str++;
                    str = (char*) realloc(str,len_str);
                    str[len_str-1] = 'V';
                    break;
                case 6:
                    len_str += 2;
                    str = (char*) realloc(str,len_str);
                    str[len_str-2] = 'V';
                    str[len_str-1] = 'I';
                    break;
                case 7:
                    len_str += 3;
                    str = (char*) realloc(str,len_str);
                    str[len_str-3] = 'V';
                    str[len_str-2] = 'I';
                    str[len_str-1] = 'I';
                    break;
                case 8:
                    len_str += 4;
                    str = (char*) realloc(str,len_str);
                    str[len_str-4] = 'V';
                    str[len_str-3] = 'I';
                    str[len_str-2] = 'I';
                    str[len_str-1] = 'I';
                    break;
                case 9:
                    len_str += 2;
                    str = (char*) realloc(str,len_str);
                    str[len_str-2] = 'I';
                    str[len_str-1] = 'X';
                    break;
            }
        }
        else if (k < 100){
            switch (k){
                case 10:
                    len_str++;
                    str = (char*) realloc(str,len_str);
                    str[len_str-1] = 'X';
                    break;
                case 20:
                    len_str += 2;
                    str = (char*) realloc(str,len_str);
                    str[len_str-2] = 'X';
                    str[len_str-1] = 'X';
                    break;
                case 30:
                    len_str += 3;
                    str = (char*) realloc(str,len_str);
                    str[len_str-3] = 'X';
                    str[len_str-2] = 'X';
                    str[len_str-1] = 'X';
                    break;
                case 40:
                    len_str += 2;
                    str = (char*) realloc(str,len_str);
                    str[len_str-2] = 'X';
                    str[len_str-1] = 'L';
                    break;
                case 50:
                    len_str++;
                    str = (char*) realloc(str,len_str);
                    str[len_str-1] = 'L';
                    break;
                case 60:
                    len_str += 2;
                    str = (char*) realloc(str,len_str);
                    str[len_str-2] = 'L';
                    str[len_str-1] = 'X';
                    break;
                case 70:
                    len_str += 3;
                    str = (char*) realloc(str,len_str);
                    str[len_str-3] = 'L';
                    str[len_str-2] = 'X';
                    str[len_str-1] = 'X';
                    break;
                case 80:
                    len_str += 4;
                    str = (char*) realloc(str,len_str);
                    str[len_str-4] = 'L';
                    str[len_str-3] = 'X';
                    str[len_str-2] = 'X';
                    str[len_str-1] = 'X';
                    break;
                case 90:
                    len_str += 2;
                    str = (char*) realloc(str,len_str);
                    str[len_str-2] = 'X';
                    str[len_str-1] = 'C';
                    break;
            }
        }
        else if (k < 1000){
            switch (k){
                case 100:
                    len_str++;
                    str = (char*) realloc(str,len_str);
                    str[len_str-1] = 'C';
                    break;
                case 200:
                    len_str += 2;
                    str = (char*) realloc(str,len_str);
                    str[len_str-2] = 'C';
                    str[len_str-1] = 'C';
                    break;
                case 300:
                    len_str += 3;
                    str = (char*) realloc(str,len_str);
                    str[len_str-3] = 'C';
                    str[len_str-2] = 'C';
                    str[len_str-1] = 'C';
                    break;
                case 400:
                    len_str += 2;
                    str = (char*) realloc(str,len_str);
                    str[len_str-2] = 'C';
                    str[len_str-1] = 'D';
                    break;
                case 500:
                    len_str++;
                    str = (char*) realloc(str,len_str);
                    str[len_str-1] = 'D';
                    break;
                case 600:
                    len_str += 2;
                    str = (char*) realloc(str,len_str);
                    str[len_str-2] = 'D';
                    str[len_str-1] = 'C';
                    break;
                case 700:
                    len_str += 3;
                    str = (char*) realloc(str,len_str);
                    str[len_str-3] = 'D';
                    str[len_str-2] = 'C';
                    str[len_str-1] = 'C';
                    break;
                case 800:
                    len_str += 4;
                    str = (char*) realloc(str,len_str);
                    str[len_str-4] = 'D';
                    str[len_str-3] = 'C';
                    str[len_str-2] = 'C';
                    str[len_str-1] = 'C';
                    break;
                case 900:
                    len_str += 2;
                    str = (char*) realloc(str,len_str);
                    str[len_str-2] = 'C';
                    str[len_str-1] = 'M';
                    break;
            }
        }
        else{
            switch (k){
                case 1000:
                    len_str++;
                    str = (char*) realloc(str,len_str);
                    str[len_str-1] = 'M';
                    break;
                case 2000:
                    len_str += 2;
                    str = (char*) realloc(str,len_str);
                    str[len_str-2] = 'M';
                    str[len_str-1] = 'M';
                    break;
                case 3000:
                    len_str += 3;
                    str = (char*) realloc(str,len_str);
                    str[len_str-3] = 'M';
                    str[len_str-2] = 'M';
                    str[len_str-1] = 'M';
                    break;
            }
        }
        num %= ipow(10,len_num-1-i);
        i++;
    }
    str[len_str] = '\0';
    return str;
}

static int ipow(int x, int n){
    int p = 1;
    for (int i = 0; i < n; i++)
        p *= x;
    return p;
}
