#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 5
typedef unsigned int uint;

typedef struct User{
    int id;
    char *login;
    char *password;
} User;

static void PrintUser(User *user){
    printf("{id = %d, login = \"%s\", password = \"%s\"}\n",
        user->id,user->login,user->password);
}
static void FreeUser(User **users, uint size){
    for (uint i = 0; i < size; i++){
        free((*users)[i].login);
        free((*users)[i].password);
    }
    free(*users);
}

int main(){
    uint size;
    char buffer[128];
    User *users;

    printf("Enter number of users: ");
    scanf("%d",&size);
    size = (size <= MAX_SIZE) ? size : MAX_SIZE;
    users = (User*) malloc(sizeof(User));
    for (uint i = 0; i < size; i++){
        printf("User #%d:\n",i+1);
        users[i].id = i;
        printf("Enter login: ");
        scanf("%s",buffer);
        users[i].login = (char*) malloc(strlen(buffer)+1);
        strcpy(users[i].login, buffer);
        printf("Enter password: ");
        scanf("%s",buffer);
        users[i].password = (char*) malloc(strlen(buffer)+1);
        strcpy(users[i].password,buffer);
    }
    for (uint i = 0; i < size; i++){
        PrintUser(&users[i]);
    }
    FreeUser(&users, size);
    return 0;
}