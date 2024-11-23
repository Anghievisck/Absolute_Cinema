#ifndef BST_H
#define BST_H

typedef struct user User;

typedef struct tree{
    User *root;
}Tree;

Tree* Create();
int IsTreeEmpty(Tree*);
void Delete(Tree**);

void BalanceTree(Tree**);
User* RotateLeft(User*);
User* RotateRight(User*);

void PrintTree(Tree*);

#endif
