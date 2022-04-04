#include <stdio.h>
#include <math.h>

#define SIZE 40

void read_vector(double x[], int n) {
	for(int i = 0; i < n; ++i) {
		scanf("%lf", x++);
	}
}

void print_vector(double x[], int n) {
	for(int i = 0; i < n; ++i) {
		printf("%.4f ", x[i]);
	}
	printf("\n");
}

void read_mat(double A[][SIZE], int m, int n) {
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < n; ++j) {
			scanf("%lf", &A[i][j]);
		}
	}
}

void print_mat(double A[][SIZE], int m, int n) {
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < n; ++j) {
			printf("%.4f ", A[i][j]);
		}
		printf("\n");
	}
}

void print_mat_ind(double A[][SIZE], int m, int n, const int indices[]);

// 5.1
// Calculate matrix product, AB = A X B
// A[m][p], B[p][n]
void mat_product(double A[][SIZE], double B[][SIZE], double AB[][SIZE], int m, int p, int n)
{
	// m- liczba wierzy A p- liczba komlumn A, p- liczba wierszy B, n- liczba kolumn B
	//A[m][p] B[p][n]
	for(int i=0; i<m*n; i++)
	{
		double tmp=0;
		for(int j=0; j<p; j++)
		{
			tmp+=A[i/m][j]*B[j][i%n];
		}
		AB[i/m][i%n]=tmp;
	}

}

// Calculate matrix - vector product
void mat_vec_product(double A[][SIZE], const double b[], double Ab[], int m, int n);


void backward_substit(double A[][SIZE], double x[], int n);


void backward_substitution_index(double A[][SIZE], const int indices[], double x[], int n);


// 5.2
// Matrix triangulation and determinant calculation - simplified version
// (no rows' swaps). If A[i][i] == 0, function returns NAN.
// Function may change A matrix elements.
double gauss_simplified(double A[][SIZE], int n)
{
	double determinant=1;
	for(int column=0; column<n; column++)
	{
		double element=A[column][column];
		if(element==0) return NAN;

		for(int j=column+1; j<n; j++)
		{	
			double razy=A[j][column];
			for(int i=0; i<n; i++)
			{
				A[j][i]-=(A[column][i]/element)*razy;
			}
			
		}
	}
	for(int x=0; x<n; x++)
	{
		if(A[x][x]==0) return NAN;
		determinant*=A[x][x];
	}
	return determinant;
}

// 5.3
// Matrix triangulation, determinant calculation, and Ax = b solving - extended version
// (Swap the rows so that the row with the largest, leftmost nonzero entry is on top. While
// swapping the rows use index vector - do not copy entire rows.)
// If max A[i][i] < eps, function returns 0.
// If det != 0 && b != NULL && x != NULL then vector x should contain solution of Ax = b.

double gauss(double A[][SIZE], const double b[], double x[], const int n, const double eps)
{
	int indeksy[n];
	double det=1;
    for(int i=0; i<n; i++) indeksy[i]=i;

    for(int i=0; i<n; i++)
	{   
        for(int j=i+1; j<n; j++)
        {
			if(fabs(A[indeksy[i]][i])<fabs(A[indeksy[j]][i]))
            {
			det*=-1;
			int tmp=indeksy[i];
			indeksy[i]=indeksy[j];
			indeksy[indeksy[j]]=tmp;
            }
        }

		double element=A[indeksy[i]][i];
        for(int j=i+1; j<n; j++)
		{	
			if(fabs(element)<eps) return 0;
            double razy=A[indeksy[j]][i];
			for(int x=0; x<n; x++)
			{
				A[indeksy[j]][x]-=(A[indeksy[i]][x]/element)*razy;
			}
		}
	
	}

    for(int i=0; i<n; i++)	det*=A[indeksy[i]][i];
	for(int i=0; i<n; i++) if(b[i]==0) return 0;

	

    



 return det;
}


// 5.4
// Returns the determinant; B contains the inverse of A (if det(A) != 0)
// If max A[i][i] < eps, function returns 0.
double matrix_inv(double A[][SIZE], double B[][SIZE], int n, double eps)
{





return 0;	
}

int main(void) {

	double A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
	double b[SIZE], x[SIZE], det, eps = 1.e-13;

	int to_do;
	int m, n, p;

	scanf ("%d", &to_do);

	switch (to_do) {
		case 1:
			scanf("%d %d %d", &m, &p, &n);
			read_mat(A, m, p);
			read_mat(B, p, n);
			mat_product(A, B, C, m, p, n);
			print_mat(C, m, n);
			break;
			
		case 2:
			scanf("%d", &n);
			read_mat(A, n, n);
			printf("%.4f\n", gauss_simplified(A, n));
			break;
		
		case 3:
			scanf("%d", &n);
			read_mat(A,n, n);
			read_vector(b, n);
			det = gauss(A, b, x, n, eps);
			printf("%.4f\n", det);
			if(det) print_vector(x, n);
			break;
		
		case 4:
			scanf("%d", &n);
			read_mat(A,n,n);
			printf("%.4f\n",matrix_inv(A, B, n, eps));
			print_mat(B, n, n);
			break;
		
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	
	}
	return 0;
}