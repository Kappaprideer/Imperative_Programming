#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define IN_LINE_COMMENT 1
#define IN_BLOCK_COMMENT 2
#define IN_SQUARE_BRACKET 3
#define IN_STRING 4
#define IN_ID 8

#define MAX_ID_LEN 64
#define MAX_IDS 1024
#define MAX_LINE 128

int index_cmp(const void*, const void*);
int cmp(const void*, const void*);

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
	int result=0, state=0, ilosc=0, dlugosc=0;
	int c, c_next;
	
	while ((c = getc(stdin)) != EOF) {
		switch (state) {

			case IN_LINE_COMMENT:
				if (c == '\n')	state = 0; // end of line comment
				break;

			case IN_BLOCK_COMMENT:
				if (c != '*') break;
				c_next = getc(stdin);
				if (c_next == '/') {
					state = 0; // end of block comment
				} else {
					ungetc(c_next, stdin);
				}
				break;

			case IN_STRING:
				if (c=='"') state = 0;
				break;

			case IN_ID:
				if (isalpha(c) || c=='_' || isdigit(c))
				{
					tab[ilosc][dlugosc]=(char)c;
					++dlugosc;
					break;
				}
				++ilosc;
				state=0;
				break;
				

			default:

				if (isalpha(c) || c=='_')
				{
					state=IN_ID;
					tab[ilosc][0]=(char)c;
					dlugosc=1;
					break;
				}

				else if (c=='"')
				{
					state=IN_STRING;
					break;
				}

				else if (c == '/')
				{
					c_next = getc(stdin);
					if (c_next == '/') {
						state = IN_LINE_COMMENT; // line comment begins		
						break;
					}
					if (c_next == '*') {
						state = IN_BLOCK_COMMENT; // block comment begins
						break;
					}
					ungetc(c_next, stdin);
					break;
				}
		}
	}
	
	int indeksy[ilosc], zawiera=0;
	for(int i=0; i<ilosc; i++) indeksy[i]=i;
	qsort(indeksy,(unsigned long int)ilosc,sizeof(int),index_cmp);
	
	
	for(int j=0; j<sizeof(keywords)/sizeof(keywords[0]); j++)
	{
		if(strcmp(keywords[j],tab[indeksy[0]])==0)
		{
			zawiera=1;
			break;
		}	
	}
	if(zawiera==0) ++result;
	




	for(int i=1; i<ilosc; i++)
	{
		zawiera=0;
		if(strcmp(tab[indeksy[i-1]], tab[indeksy[i]])!=0)
		{	
			for(int j=0; j<sizeof(keywords)/sizeof(keywords[0]); j++)
			{
				if(strcmp(keywords[j],tab[indeksy[i]])==0)
				{	

					zawiera=1;
					break;
				}	
			}
			if(zawiera==0)
			{	
				printf("Dodaje %s do wyniku\n", tab[indeksy[i]]);
				++result;
			}
		}
		
	}
	printf("TABLICA\n");
	for(int i=0; i<ilosc; i++)
	{
		printf("%s\n", tab[indeksy[i]]);
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

print"lol"
print"\""
print"// " main()
print" twoja()stara
"print/ twoja    stara  /*

1
2
3
8

\
*/
for(int i; i<0; i++);
