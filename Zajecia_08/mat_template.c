#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define TAB_SIZE  1000
#define BUF_SIZE  1000

double get(int cols, int row, int col, const double *A)
{
	return A[(col*row)+cols];
}

void set(int cols, int row, int col, double *A, double value)
{
	A[(col*row)+cols]=value;
}

void prod_mat(int rowsA, int colsA, int colsB, double *A, double *B, double *AB)
{
	for(int i=0; i<rowsA; i++)
	{
		for(int k=0; k<colsB; k++)
		{
			double value=0;
			for(int j=0; j<colsA; j++)
			{
				double first=get(j,i,colsA,A);
				double second=get(k,j,colsB,B);
				value+=first*second;
			}
			set(k,i,colsB,AB,value);
		}
	}
}

void read_mat(int rows, int cols, double *t)
{
	for(int i=0; i<rows*cols; i++)
		scanf("%lf", t+i);
}

void print_mat(int rows, int cols, double *t)
{
	for(int i=0; i<rows*cols; i++)
	{
		printf("%.2f ", t[i]);
		if((i+1)%cols==0)
			printf("\n");
	}	
}

int read_char_lines(char *tab[])
{
	char text[TAB_SIZE];
	int lines=0;
	while(fgets(text, TAB_SIZE, stdin)!=NULL)
	{
		tab[lines]= malloc(strlen(text)*sizeof(char));
		for(int i=0; i<strlen(text); i++)
		{
			tab[lines][i]=text[i];
		}
		++lines;
	}
	return lines;
}

void write_char_line(char *tab[], int n)
{
	long unsigned int size=strlen(tab[n]);
	for(int i=0; i<size; i++)
	{
		printf("%c", tab[n][i]);
	}
}

void delete_lines(char *tab[], int line_count);

int read_dbl_lines_v1(double *ptr_tab[])
{
	char number[TAB_SIZE],znak;
	double wynik=0;
	int lines=0, indeks=-1;
	while(scanf("%s", number)!=EOF)
	{
		wynik=atoi(number);
		znak=getc(stdin);
		ptr_tab[0][++indeks]=wynik;
		if(znak=='\n')
		{
			ptr_tab[++lines]=&ptr_tab[0][indeks+1];			
		}
		ungetc(znak, stdin);
	}
	return lines;
}

void write_dbl_line_v1(double *ptr_tab[], int n)
{
	double* gdzie=ptr_tab[n-1];
	while(gdzie!=ptr_tab[n])
	{
		printf("%.2f ", *gdzie);
		gdzie+=1;
	}
}

int main(void) {
	int to_do;

	scanf ("%d", &to_do);

	double A[TAB_SIZE], B[TAB_SIZE], C[TAB_SIZE];
	int n, lines_counter, rowsA,colsA,rowsB,colsB;
	char *char_lines_table[TAB_SIZE];
	double series_table[TAB_SIZE];
	double *ptr_table[TAB_SIZE];

	switch (to_do) {
		case 1:
			scanf("%d %d",&rowsA,&colsA);
			read_mat(rowsA, colsA, A);
			scanf("%d %d",&rowsB,&colsB);
			read_mat(rowsB, colsB, B);
			prod_mat(rowsA,colsA,colsB,A,B,C);
			print_mat(rowsA,colsB,C);
			break;
		
		case 2:
			scanf("%d",&n);
			ptr_table[0] = series_table;
			lines_counter = read_dbl_lines_v1(ptr_table);
			write_dbl_line_v1(ptr_table,n);
			break;
		
		case 3:
			scanf("%d", &n);
			lines_counter = read_char_lines(char_lines_table);
			write_char_line(char_lines_table,n);
			// delete_lines(char_lines_table,lines_counter);
			break;
		
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
	}
	return 0;
}

