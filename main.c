#include"libs/lista_ordenada.h"



int main() {
    int erro;
    List *L = Create_list(&erro);
    List *G = Create_list(&erro);
    //printf("%d\n", isListEmpty(L));
    insert_elem(L, "xixi", &erro);
    printf("%d\n", isListEmpty(L));
    insert_elem(L, "cu", &erro);
    insert_elem(L, "pinto xixi bosta cOco", &erro);
    insert_elem(L, "mijo", &erro);
    printList(L, &erro);

    insert_elem(G, "xixi", &erro);
    insert_elem(G, "bst", &erro);
    insert_elem(G, "dst", &erro);
    insert_elem(G, "cu", &erro);
    printList(G, &erro);

    List *C = CompareLists(L, G, &erro);
    printList(C, &erro);

    List *M = MergeLists(L, G, &erro);
    printList(M, &erro);

    DestroyList(L);
    DestroyList(G);
    DestroyList(C);
}