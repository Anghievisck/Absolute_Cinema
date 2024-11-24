#include"string_auxiliar.h"

//funcao auxiliar que transforma todos os chars em uppercase
void to_uppercase(Elem str) { 
    if (str == NULL) {
        return; // Handle NULL input
    }

    Elem ptr = str; // salva o ponteiro original

    while (*ptr != '\0') {
        *ptr = toupper((unsigned char)*ptr); // converte caracteres para caixa alta
        ptr++;
    }
}

//funcao auxiliar que transforma todos os chars após um espaço em uppercase
void to_uppercase_after_space(Elem str) { 
    if (str == NULL) {
        return; // Handle NULL input
    }

    Elem ptr = str; // salva o ponteiro original
    int space = 1;
    while (*ptr != '\0') {
        if(space == 1) {
            *ptr = toupper((unsigned char)*ptr); // converte caracteres para caixa alta
            space = 0;
        }
        if(*ptr == ' ') {
            space = 1;
        }
        
        ptr++;
    }
}

//funcao auxiliar que transforma todos os chars em lowercase
void to_lowercase(Elem str) { 
    if (str == NULL) {
        return; // Handle NULL input
    }

    Elem ptr = str; // salva o ponteiro original

    while (*ptr != '\0') {
        *ptr = tolower((unsigned char)*ptr); // converte caracteres para caixa alta
        ptr++;
    }
}