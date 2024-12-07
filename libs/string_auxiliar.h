#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define LENGTH 100

typedef char* Elem;

void to_uppercase(Elem str);
void to_uppercase_after_space(Elem str);
void to_lowercase(Elem str);

int GetInteger(char* prompt, char* errorPrompt);
char* GetString(char* prompt);