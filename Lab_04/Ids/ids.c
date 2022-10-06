## pierwsza templatka

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define IN_LINE_COMMENT 1
#define IN_BLOCK_COMMENT 2
#define IN_STRING 4
#define IN_ID 8

#define MAX_ID_LEN 64
#define MAX_IDS 1024

//int index_cmp(const void*, const void*);
//int cmp(const void*, const void*);

char tab[MAX_IDS][MAX_ID_LEN];

char *keywords[] = {
	"auto", "break", "case", "char",
	"const", "continue", "default", "do",
	"double", "else", "enum", "extern",
	"float", "for", "goto", "if",
	"int", "long", "register", "return",
	"short", "signed", "sizeof", "static",
	"struct", "switch", "typedef", "union",
	"unsigned", "void", "volatile", "while"
};

int find_idents()
{
	char napis[MAX_IDS];
	int result=0;
	int cudzyslow=0, komentarz=0;
	while(scanf("%c", napis)!=EOF)
	{	if(napis[0]=='\n')
		{
			printf("NOWA LINIA");
		}
	
		if(cudzyslow)
		{
			printf("CUDZYSLOW");
		}		
		else if(komentarz)
		{
			printf("KOMENTARZ");
		}
		else if(isalpha(napis[0]) || napis[0]=='_')
		{
		int idents=0;
			for(int i=0; i<sizeof(keywords)/sizeof(keywords[0]); i++)
			{	
				long unsigned int size_of_word=strlen(napis);
				long unsigned int size_of_ids = strlen(keywords[i]); //sizeof(keywords[i][0]);
				if(size_of_ids==size_of_word)
				{
					for(int x=0; x<size_of_word && keywords[i][x]==napis[x]; x++)
					{	
						if(x==size_of_word-1)	idents=1;
					}
				}
			}
			if(!idents) ++result;
		}
	}
	return result;
}

int cmp(const void* first_arg, const void* second_arg) {
	char *a = *(char**)first_arg;
	char *b = *(char**)second_arg;
	return strcmp(a, b);
}

int index_cmp(const void* first_arg, const void* second_arg) {
	int a = *(int*)first_arg;
	int b = *(int*)second_arg;
	return strcmp(tab[a], tab[b]);
}

int main(void) {
	printf("%d\n", find_idents());
	return 0;
}

