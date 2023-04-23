#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 5
typedef unsigned int uint;

typedef struct User {
    int id;
    char *login;
    char *password;
} User_t;

static void PrintUser(User_t *user) {
    printf("{id = %d, login = \"%s\", password = \"%s\"}\n",
           user->id, user->login, user->password);
}

static void FreeUser(User_t **users, uint size) {
    for (uint i = 0; i < size; i++){
        free((*users)[i].login);
        free((*users)[i].password);
    }
    free(*users);
}

int main(void) {
    uint size;
    char buffer[128];
    User_t *users;

    printf("Enter number of users: ");
    scanf("%d",&size);
    size = (size <= MAX_SIZE) ? size : MAX_SIZE;
    users = (User_t *) malloc(sizeof(User_t));

    for (uint i = 0; i < size; i++) {
        memset(buffer, 0, 128);
        printf("User #%d:\n", i+1);
        users[i].id = i;
        printf("Enter login: ");
        scanf("%s",buffer);
        users[i].login = (char *) malloc(strlen(buffer) + 1);
        strcpy(users[i].login, buffer);
        printf("Enter password: ");
        scanf("%s",buffer);
        users[i].password = (char *) malloc(strlen(buffer) + 1);
        strcpy(users[i].password,buffer);
    }

    for (uint i = 0; i < size; i++) {
        PrintUser(&users[i]);
    }

    FreeUser(&users, size);
    return 0;
}