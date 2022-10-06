#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REL_SIZE 1000
#define MAX_RANGE 1000

typedef struct {
	int first;
	int second;
} pair;

// Add pair to existing relation if not already there
int add_relation (pair*, int, pair);

// Read number of pairs, n, and then n pairs of ints
int read_relation(pair*);

// Case 1:
// The relation R is reflexive if xRx for every x in X
int is_reflexive(pair*, int);
// The relation R on the set X is called irreflexive
// if xRx is false for every x in X
int is_irreflexive(pair*, int);
// A binary relation R over a set X is symmetric if:
// for all x, y in X xRy <=> yRx
int is_symmetric(pair*, int);
// A binary relation R over a set X is antisymmetric if:
// for all x,y in X if xRy and yRx then x=y
int is_antisymmetric(pair*, int);
// A binary relation R over a set X is asymmetric if:
// for all x,y in X if at least one of xRy and yRx is false
int is_asymmetric(pair*, int);
// A homogeneous relation R on the set X is a transitive relation if:
// for all x, y, z in X, if xRy and yRz, then xRz
int is_transitive(pair*, int);

// Case 2:
// A partial order relation is a homogeneous relation that is
// reflexive, transitive, and antisymmetric
int is_partial_order(pair*, int);
// A total order relation is a partial order relation that is connected
int is_total_order(pair*, int);
// Relation R is connected if for each x, y in X:
// xRy or yRx (or both)
int is_connected(pair*, int);
int find_max_elements(pair*, int, int*);
int find_min_elements(pair*, int, int*);
int get_domain(pair*, int, int*);

// Case 3:
int composition (pair*, int, pair*, int, pair*);

int cmp (pair p1, pair p2) {
	if (p1.first == p2.first) return p1.second - p2.second;
	return p1.first - p2.first;
}

void print_int_array(int *array, int n) {
	printf("%d\n", n);
	for (int i = 0; i < n; ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

int main(void) {
	int to_do;
	pair relation[MAX_REL_SIZE];
	pair relation_2[MAX_REL_SIZE];
	pair comp_relation[MAX_REL_SIZE];
	int domain[MAX_REL_SIZE];

	scanf("%d",&to_do);
	int size = read_relation(relation);
	int ordered, size_2, n_domain;

	switch (to_do) {
		case 1:
			printf("%d ", is_reflexive(relation, size));
			printf("%d ", is_irreflexive(relation, size));
			printf("%d ", is_symmetric(relation, size));
			printf("%d ", is_antisymmetric(relation, size));
			printf("%d ", is_asymmetric(relation, size));
			printf("%d\n", is_transitive(relation, size));
			break;
		
		case 2:
			ordered = is_partial_order(relation, size);
			n_domain = get_domain(relation, size, domain);
			printf("%d %d\n", ordered, is_total_order(relation, size));
			print_int_array(domain, n_domain);
			if (!ordered) break;
			int max_elements[MAX_REL_SIZE];
			int min_elements[MAX_REL_SIZE];
			int no_max_elements = find_max_elements(relation, size, max_elements);
			int no_min_elements = find_min_elements(relation, size, min_elements);
			print_int_array(max_elements, no_max_elements);
			print_int_array(min_elements, no_min_elements);
			break;
			
		case 3:
			size_2 = read_relation(relation_2);
			printf("%d\n", composition(relation, size,
			   relation_2, size_2, comp_relation));
			break;
		
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
		
	}
	return 0;
}

void swap(int* a, int* b)
{
	int tmp= *a;
	*a=*b;
	*b=tmp;
}

int add_relation(pair* list_of_pairs, int size, pair new_to_add){
	for(int i=0; i<size; i++)
		if(!cmp(list_of_pairs[i],new_to_add)) return size;
	list_of_pairs[size]=new_to_add;
	return ++size;}
int read_relation(pair* pary)
{
	int n=0, size=0;
	pair new;
	scanf("%d", &n);
	for(int i=0; i<n; i++)
	{
		scanf("%d %d", &new.first, &new.second);
		size=add_relation(pary,size,new);
	}
	return size;
}
int is_reflexive(pair* list, int size)
{
	for(int i=0; i<size; i++)
	{	
		int x=list[i].first, exist=0;
		for(int j=0; j<size; j++)
		{
			if(list[j].first==x && list[j].second==x) exist=1;
			 
		}
		if(!exist) return 0;
	}
	return 1;
}
int is_irreflexive(pair* pairs, int size)
{
	for(int i=0; i<size; i++)
	{	
		int x=pairs[i].first;
		for(int j=0; j<size; j++)
		{
			if(pairs[j].first==x && pairs[j].second==x) return 0;
			 
		}
	}
	return 1;
}
int is_symmetric(pair* pairs, int size)
{
	for(int i=0; i<size; i++)
	{
		int x=pairs[i].first;
		int y=pairs[i].second;
		int exist=0;
		for(int j=0; j<size; j++)
		{
			if(pairs[j].first==y && pairs[j].second==x) exist=1;
		}
		if(!exist) return 0;
	}
	return 1;
}
int is_antisymmetric(pair* pairs, int size)
{
	for(int i=0; i<size; i++)
	{
		int x=pairs[i].first;
		int y=pairs[i].second;
		for(int j=0; j<size; j++)
		{
			if(pairs[j].first==y && pairs[j].second==x && x!=y) return 0;
		}
	}
	return 1;	
}
int is_asymmetric(pair* pairs, int size)
{
	for(int i=0; i<size; i++)
	{
		int x=pairs[i].first;
		int y=pairs[i].second;
		for(int j=0; j<size; j++)
		{
			if(pairs[j].first==y && pairs[j].second==x) return 0;
		}
	}
	return 1;
}
int is_transitive(pair* pairs, int size)
{	
	int include_z=0, exist=0;
	for(int i=0; i<size; i++)
	{	
		for(int j=0; j<size; j++)
		{
			if(pairs[i].second==pairs[j].first)
			{	
				exist=0;
				include_z=0;
				for(int k=0; k<size; k++)
				{
				if(pairs[k].first==pairs[j].second) include_z=1;
				if(pairs[k].first==pairs[i].first && pairs[k].second==pairs[j].second) exist=1;
				}	
				if(include_z && !exist) return 0;
			}
		}
	}
	return 1;
}

//Case 2
int get_domain(pair pairs[], int size, int tablica[])
{	
	int n=0;
	for(int i=0; i<size; i++)
	{	
		int first_exlude=0, second_exlude=0;
		for(int j=0; j<n; j++)
		{
			if(tablica[j]==pairs[i].first)	first_exlude=1;
			if(tablica[j]==pairs[i].second) second_exlude=1;
		}
		if(!first_exlude)	tablica[n++]=pairs[i].first;
		if(!second_exlude && pairs[i].first!=pairs[i].second) tablica[n++]=pairs[i].second;
	}
	for(int i=0; i<n; i++)
		for(int j=0; j<n-i-1; j++)
			if(tablica[j]>tablica[j+1]) swap(&tablica[j], &tablica[j+1]);
return n;
}
int is_partial_order(pair* list, int size)
{
	if(is_reflexive(list,size) && is_antisymmetric(list,size) && is_transitive(list, size)) return 1;
	return 0;
}

int is_total_order(pair* list, int size)
{
if(is_partial_order(list,size))
{
	int domain[MAX_REL_SIZE];
	int counter=0, n=0;
	n=get_domain(list,size,domain);
	for(int i=0; i<n; i++)
	{
		counter=0;
		for(int j=0; j<size; j++)
		{
			if(list[j].first==domain[i] || list[j].second==domain[i]) ++counter;
		}
		if(counter<n) return 0;
	}
	return 1;
}
return 0;
}

int find_max_elements(pair* pairs, int size, int *result)
{
	int n=0, is_multiply=0, include=0;
	for(int i=0; i<size; i++)
	{
		is_multiply=0, include=0;
		for(int j=0; j<size; j++)
		{
			if(pairs[j].first==pairs[i].first && pairs[j].second==pairs[i].first) include=1;
			if(pairs[j].first==pairs[i].first && pairs[j].second!=pairs[i].first) is_multiply=1;
		}
		if(include && !is_multiply)
		{	
			int new=1;
			for(int x=0; x<n; x++)
			{
				if(result[x]==pairs[i].first) new=0;
			}
			if(new) result[n++]=pairs[i].first;
		}
	}
	for(int i=0; i<n; i++)
		for(int j=0; j<n-i-1; j++)
			if(result[j]>result[j+1]) swap(&result[j], &result[j+1]);
	return n;
}
int find_min_elements(pair* pairs, int size, int *result)
{
	int n=0, is_multiply=0, include=0;
	for(int i=0; i<size; i++)
	{
		is_multiply=0, include=0;
		for(int j=0; j<size; j++)
		{
			if(pairs[j].second==pairs[i].second && pairs[j].first==pairs[i].second) include=1;
			if(pairs[j].second==pairs[i].second && pairs[j].first!=pairs[i].second) is_multiply=1;
		}
		if(include && !is_multiply)
		{	
			int new=1;
			for(int x=0; x<n; x++)
			{
				if(result[x]==pairs[i].second) new=0;
			}
			if(new) result[n++]=pairs[i].second;
		}
	}
	for(int i=0; i<n; i++)
		for(int j=0; j<n-i-1; j++)
			if(result[j]>result[j+1]) swap(&result[j], &result[j+1]);
	return n;
}

//Case 3
int composition (pair *S, int size_S,pair *R, int size_R, pair result[])
{
	int n=0;
	for(int i=0; i<size_S; i++)
	{

		for(int j=0; j<size_R; j++)
		{	
			int exist=0;
			if(R[j].first==S[i].second)
			{
				for(int x=0; x<n; x++)
				{
					if(result[x].first==S[i].first && result[x].second==R[j].second) exist=1;
				}
				if(!exist)
				{
					result[n].first=S[i].first;
					result[n].second=R[j].second;
					++n;
				}
			}
		}
		
	}	

	return n;
}