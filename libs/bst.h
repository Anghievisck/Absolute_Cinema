#ifndef BST_H
#define BST_H

typedef struct user User;

typedef struct tree{
    User *root;
}Tree;

Tree* CreateTree();
int IsTreeEmpty(Tree*);
void Delete(Tree**);

void BalanceTree(Tree**, int n);
User* RotateLeft(User*);
User* RotateRight(User*);

void PrintTree(Tree*);

#endif