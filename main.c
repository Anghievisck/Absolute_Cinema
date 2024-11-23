#include"libs/lista_ordenada.h"



char* copy_to_mutable_buffer(const char* str) {
    if (str == NULL) {
        return NULL; // Handle NULL input
    }

    // Allocate memory for the mutable buffer
    char* buffer = malloc(strlen(str) + 1); // +1 for the null terminator
    if (buffer == NULL) {
        return NULL; // Memory allocation failed
    }

    // Copy the string into the buffer
    strcpy(buffer, str);

    return buffer; // Return the pointer to the mutable buffer
}

char* to_uppercase(char* str) {
    if (str == NULL) {
        return NULL; // Handle NULL input
    }

    char* ptr = str; // Save the original pointer

    while (*ptr != '\0') {
        *ptr = toupper((unsigned char)*ptr); // Convert character to uppercase
        ptr++;
    }

    return str; // Return the original pointer
}

int main() {
    int erro;
    List *L = Create_list(&erro);
    //printf("%d\n", isListEmpty(L));
    insert_elem(L, "xixi", &erro);
    printf("%d\n", isListEmpty(L));
    insert_elem(L, "cu", &erro);
    insert_elem(L, "pinto", &erro);
    insert_elem(L, "mijo", &erro);
    printf("%d encontrou mijo\n", search_elem(L, "mijo", &erro));
    printf("%d encontrou xoxota\n", search_elem(L, "xoxota", &erro));
    printList(L);
}