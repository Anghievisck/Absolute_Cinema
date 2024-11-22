#include "bst.h"
#include "lista_ordenada.h"

typedef struct user{
    int numero_usp;
    char* nome;

    struct user *nextL, *nextR;
    List *favoriteMovies;
}User;

void InsertUser(Tree*);
void InsertMovie(User*);

User* FindUser(Tree*, int);

void DeleteUser(User **u);
