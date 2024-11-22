typedef struct User;

typedef struct {
    User *root;
}Tree;

Tree* Create();
int IsTreeEmpty(Tree*);
void Delete(Tree**);
