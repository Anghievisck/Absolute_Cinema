#include"libs/lista_ordenada.h"



int main() {
    int erro;
    List *L = Create_list(&erro);
    List *G = Create_list(&erro);
    insert_elem(L, "xixi", &erro);
    insert_elem(L, "cub", &erro);
    insert_elem(L, "pinto xixi bosta cOco", &erro);
    insert_elem(L, "cua", &erro);
    remove_elem(L, "mijo", &erro);
    printf("%d\n", ListSize(L));
    printf("encontrou cu %d\n", search_elem(L, "cu", &erro));
    printf("encontrou xixi %d\n", search_elem(L, "xixi", &erro));
    printList(L, &erro);


    insert_elem(G, "xixi", &erro);
    insert_elem(G, "bst", &erro);
    insert_elem(G, "dst", &erro);
    insert_elem(G, "cu", &erro);
    printf("%d\n", ListSize(G));
    printList(G, &erro);

    List *C = CompareLists(L, G, &erro);
    printf("%d\n", ListSize(C));
    printList(C, &erro);

    List *M = MergeLists(L, G, &erro);
    printf("%d\n", ListSize(M));
    printList(M, &erro);

    DestroyList(L);
    DestroyList(G);
    DestroyList(C);
    DestroyList(M);
}