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

int GetInteger(char* prompt, char* errorPrompt){
    char* placeholder = (char*)malloc(sizeof(char) * LENGTH);

    printf("%s", prompt);

    fgets(placeholder, LENGTH, stdin);
    //printf("placeholder: %s\n", placeholder);
    //printf("*placeholder: %c\n", *placeholder);

    //printf("Eh digito? %d\n", isdigit(*placeholder));

    char* digits = (char*)malloc(strlen(placeholder)+1);

    strcpy(digits, placeholder);
    for(int i = 0; i < strlen(placeholder); i++){
        if(!isdigit(*placeholder)){
            printf("%s", errorPrompt);
            return GetInteger(prompt, errorPrompt);
        }

        placeholder++;
    }

    return atoi(digits);
}