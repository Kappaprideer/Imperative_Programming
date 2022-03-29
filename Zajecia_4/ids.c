#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEWLINE '\n'

#define IN_LINE_COMMENT 1
#define IN_BLOCK_COMMENT 2
#define IN_STRING 4
#define IN_ID 8

#define MAX_ID_LEN 64
#define MAX_IDS 1024

int index_cmp(const void*, const void*);
int cmp(const void*, const void*);

char new[300][130];
char line[128];
int i;
int j;
int indeks = 0;
int st = 0;
int dlugosc;
int punkt = 0;
int znacznik;

char tab[MAX_IDS][MAX_ID_LEN];

char* keywords[] = {"auto",     "break",   "case",   "char",     "const",
                    "continue", "default", "do",     "double",   "else",
                    "enum",     "extern",  "float",  "for",      "goto",
                    "if",       "int",     "long",   "register", "return",
                    "short",    "signed",  "sizeof", "static",   "struct",
                    "switch",   "typedef", "union",  "unsigned", "void",
                    "volatile", "while"};

int cmp(const void* first_arg, const void* second_arg) {
    char* a = (char*)first_arg;
    char* b = (char*)second_arg;
    return strcmp(a, b);
}

int index_cmp(const void* first_arg, const void* second_arg) {
    int a = (int)first_arg;
    int b = (int)second_arg;
    return strcmp(tab[a], tab[b]);
}
int find_idents(){

    while (fgets(line, 128, stdin)) {
        i = 0;
        while (line[i] != NEWLINE) {
            punkt = 0;
            if (st == 1) {
                if (line[i - 1] == '*' && line[i] == '/') {
                    st = 0;
                }
            }
            if (st == 2) {
                if (line[i] == '\"') {
                    if (line[i - 1] == '\\') {
                        if (line[i - 2] == '\\') {
                            st = 0;
                            punkt = 1;
                        }
                    }

                    else {
                        st = 0;
                        punkt = 1;
                    }
                }
            }
            if (st == 3) {
                if (line[i] == '\'') {
                    if (line[i - 1] == '\\') {
                        if (line[i - 2] == '\\') {
                            st = 0;
                            punkt = 1;
                        }
                    }

                    else {
                        st = 0;
                        punkt = 1;
                    }
                }
            }
            if (st == 0) {
                if (line[i] == '/' && line[i + 1] == '/') {
                    line[i + 1] = NEWLINE;
                }
                if (line[i] == '/' && line[i + 1] == '*') {
                    st = 1;
                    if (line[i + 1] != NEWLINE)
                        i++;
                }
                if (line[i] == '"' && punkt == 0) {
                    st = 2;
                }
                if (line[i] == '\'' && punkt == 0) {
                    st = 3;
                }
                if ((isalpha(line[i+1]) || line[i+1]=='_') &&
                    st == 0) {
                    if (isalpha(line[i+1]) || line[i+1]=='_') {
                    } else {
                        j = i + 2;
                        dlugosc = 1;
                        while (((((int)line[j] >= 65 && (int)line[j] <= 90) ||
                                 ((int)line[j] >= 97 && (int)line[j] <= 122)) ||
                                ((int)line[j] >= 48 && (int)line[j] <= 57)) ||
                               (int)line[j] == 95) {
                            dlugosc++;
                            j++;
                        }
                        j = i + 1;
                        for (int k = 0; k <= 31; k++) {
                            znacznik = 0;
                            for (int l = 0; l < dlugosc; l++) {
                                if (keywords[k][l] != line[j + l])
                                    znacznik = 1;
                            }
                            if (znacznik == 0) {
                                if (((((int)keywords[k][dlugosc] >= 65 &&
                                       (int)keywords[k][dlugosc] <= 90) ||
                                      ((int)keywords[k][dlugosc] >= 97 &&
                                       (int)keywords[k][dlugosc] <= 122)) ||
                                     ((int)keywords[k][dlugosc] >= 48 &&
                                      (int)keywords[k][dlugosc] <= 57)) ||
                                    (int)keywords[k][dlugosc] == 95) {
                                    znacznik = 1;
                                } else
                                    break;
                            }
                        }
                        if (znacznik == 1) {
                            for (int k = 0; k < indeks; k++) {
                                znacznik = 0;
                                for (int l = 0; l < dlugosc; l++) {
                                    if (new[k][l] != line[j + l])
                                        znacznik = 1;
                                }
                                if (znacznik == 0) {
                                    if (((((int)new[k][dlugosc] >= 65 && (int)new[k][dlugosc] <= 90) ||
                                          ((int)new[k][dlugosc] >= 97 && (int)new[k][dlugosc] <= 122)) ||
                                         ((int)new[k][dlugosc] >= 48 && (int)new[k][dlugosc] <= 57)) ||
                                        (int)new[k][dlugosc] == 95) {
                                        znacznik = 1;
                                    } else
                                        break;
                                }
                            }
                        }
                        if (znacznik == 1) {
                            for (int k = 0; k < dlugosc; k++)
                                new[indeks][k] = line[j + k];
                            indeks++;
                        }
                    }
                }
                if (i == 0 && (((((int)line[i] >= 65 && (int)line[i] <= 90) ||
                                 ((int)line[i] >= 97 && (int)line[i] <= 122))) ||
                               (int)line[i] == 95)) {
                    j = i + 1;
                    dlugosc = 1;
                    while (((((int)line[j] >= 65 && (int)line[j] <= 90) ||
                             ((int)line[j] >= 97 && (int)line[j] <= 122)) ||
                            ((int)line[j] >= 48 && (int)line[j] <= 57)) ||
                           (int)line[j] == 95) {
                        dlugosc++;
                        j++;
                    }
                    j = i;
                    for (int k = 0; k <= 31; k++) {
                        znacznik = 0;
                        for (int l = 0; l < dlugosc; l++) {
                            if (keywords[k][l] != line[j + l])
                                znacznik = 1;
                        }
                        if (znacznik == 0) {
                            if (((((int)keywords[k][dlugosc] >= 65 &&
                                   (int)keywords[k][dlugosc] <= 90) ||
                                  ((int)keywords[k][dlugosc] >= 97 &&
                                   (int)keywords[k][dlugosc] <= 122)) ||
                                 ((int)keywords[k][dlugosc] >= 48 &&
                                  (int)keywords[k][dlugosc] <= 57)) ||
                                (int)keywords[k][dlugosc] == 95) {
                                znacznik = 1;
                            } else
                                break;
                        }
                    }
                    if (znacznik == 1) {
                        for (int k = 0; k < indeks; k++) {
                            znacznik = 0;
                            for (int l = 0; l < dlugosc; l++) {
                                if (new[k][l] != line[j + l])
                                    znacznik = 1;
                            }
                            if (znacznik == 0) {
                                if (((((int)new[k][dlugosc] >= 65 && (int)new[k][dlugosc] <= 90) ||
                                      ((int)new[k][dlugosc] >= 97 && (int)new[k][dlugosc] <= 122)) ||
                                     ((int)new[k][dlugosc] >= 48 && (int)new[k][dlugosc] <= 57)) ||
                                    (int)new[k][dlugosc] == 95) {
                                    znacznik = 1;
                                } else
                                    break;
                            }
                        }
                    }
                    if (znacznik == 1) {
                        for (int k = 0; k < dlugosc; k++)
                            new[indeks][k] = line[j + k];
                        indeks++;
                    }
                }
            }
            i++;
        }
    }
    return indeks;
}
int main(void) {

    printf("%d\n", find_idents());
    return 0;
}
