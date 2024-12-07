#ifndef BST_H
#define BST_H

typedef struct user User;

typedef struct tree{
    User *root;
}Tree;

Tree* CreateTree(int*);
int IsTreeEmpty(Tree*);
void Delete(Tree**);

void BalanceTree(Tree**, int n);
//User* RotateLeft(User*);
//User* RotateRight(User*);
int insert_in_tree(User **p, User *x);
int Tree_height(Tree *A);

void PrintTree(Tree*, char*, char*, char*);

#endif