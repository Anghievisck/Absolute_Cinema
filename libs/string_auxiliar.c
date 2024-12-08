#include"string_auxiliar.h"

//funcao auxiliar que transforma todos os chars em uppercase
void to_uppercase(Elem str) { 
    if (str == NULL) {
        return; // Handle NULL input
    }

    Elem ptr = str; // salva o ponteiro original

    while (*ptr != '\0') {
        *ptr = toupper((unsigned char)*ptr); // converte caracteres para caixa alta
        if(*ptr == '\n')
            *ptr = '\0';
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
        *ptr = tolower((unsigned char)*ptr); // converte caracteres para caixa baixa
        if(*ptr == '\n')
            *ptr = '\0';
        ptr++;
    }
}

//Escreve um determinado prompt no terminal e recebe strings até a string ser um número
int GetInteger(char* prompt, char* errorPrompt) {
    char* placeholder = (char*)malloc(sizeof(char) * LENGTH);

    while (1) {
        printf("%s", prompt);
        fgets(placeholder, LENGTH, stdin);

        if(*placeholder == '\n') {
            fgets(placeholder, LENGTH, stdin);
        }

        // Remover '\n', se presente
        placeholder[strcspn(placeholder, "\n")] = '\0';
        

        // Verificar se todos os caracteres são dígitos
        int isValid = 1;
        for (int i = 0; i < strlen(placeholder); i++) {
            if (!isdigit(placeholder[i])) {
                isValid = 0;
                break;
            }
        }

        if (isValid) {
            int value = atoi(placeholder);
            free(placeholder);
            return value;
        }

        printf("%s", errorPrompt);
    } //fim do while
}

//Escreve um determinado prompt e retorna uma string, procurando resolver problemas de pegar o caratere '\n'
char* GetString(char* prompt) {
    char* placeholder = (char*)malloc(sizeof(char) * LENGTH);
    printf("%s", prompt);
    fgets(placeholder, LENGTH, stdin);

    if(*placeholder == '\n') {
        fgets(placeholder, LENGTH, stdin);
    }

    // Remover '\n', se presente
    placeholder[strcspn(placeholder, "\n")] = '\0';
    return placeholder;
}