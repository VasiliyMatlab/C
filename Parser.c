#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

// Пример работы с агрументами командной строки с помощью getopt
// Для более наглядного примера следует использовать совместно
// с bash-скриптом '_parser.sh'
int main(int argc, char * const *argv) {
    // Символ, возвращаемый getopt
    int opchar = 0;
    // Структура со всеми возможными опциями
    struct option opts[] = {
        {"Question", no_argument, 0, 'Q'},
        {"query", required_argument, 0, 'q'},
        {"longinformationrequest", no_argument, 0, 'i'},
        {"version", no_argument, 0, 'v'},
        {0,0,0,0}
    };

    // Вызывается функция в цикле, пока не дойдет до того,
    // где ее полномочия заканчиваются
    while ((opchar = getopt_long(argc, argv, "Qivq:", opts, NULL)) != -1) {
        switch (opchar) {
            case 'Q':
                printf("Question\n");
                break;
            case 'q':
                printf("query\n");
                printf("%s\n", optarg);
                break;
            case 'i':
                printf("longinformationrequest\n");
                break;
            case 'v':
                printf("version\n");
                break;
            default:
                //Printing invalid option
                break;
        }
    }
    
    return 0;
}