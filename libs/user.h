#ifndef USER_H
#define USER_H

typedef struct list List;
typedef struct tree Tree;

typedef struct user{
    int numero_usp;
    char* nome;

    int degree, fb;
    struct user *nextL, *nextR;

    List *movies;
}User;

User* CreateUser(int, char*, List*, int*);
void InsertUser(Tree**, User*, int*);


User* FindUser(Tree*, int);

void DeleteUser(User **);
void DeleteUsers(User **);

#endif
