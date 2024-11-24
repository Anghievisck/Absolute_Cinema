#ifndef USER_H
#define USER_H

typedef struct list List;
typedef struct tree Tree;

typedef struct user{
    int numero_usp;
    char* nome;

    int degree;
    struct user *nextL, *nextR;

    List *movies;
}User;

void InsertUser(Tree**, User*, int*);

User* FindUser(Tree*, int);

void DeleteUser(User **);
void DeleteUsers(User **);

#endif
