#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_STR_LEN 64

typedef struct Vector {
	void *data;
	size_t element_size;
	size_t size;
	size_t capacity;
} Vector;

typedef struct Person {
	int age;
	char first_name[MAX_STR_LEN];
	char last_name[MAX_STR_LEN];
} Person;


// Allocate vector to initial capacity (block_size elements),
// Set element_size, size (to 0), capacity
void init_vector(Vector *vector, size_t block_size, size_t element_size)
{
	if(element_size==sizeof(int))
		vector->data=(int *)malloc(block_size*element_size);
	else if(element_size==sizeof(char))
		vector->data=(char *)malloc(block_size*element_size);
	else if(element_size==sizeof(Person))
		vector->data=(Person *)malloc(block_size*element_size);
	vector->element_size=element_size;
	vector->size=0;
	vector->capacity=block_size;

}

// If new_capacity is greater than the current capacity,
// new storage is allocated, otherwise the function does nothing.
void reserve(Vector *vector, size_t new_capacity)
{
	if(vector->capacity<new_capacity)
	{	
		// void *new=realloc(vector->data, new_capacity*(vector->element_size));
		// memcpy(new,vector->data,vector->size);
		// vector->data=new;
		vector->data=realloc(vector->data, new_capacity*(vector->element_size));
		vector->capacity=new_capacity;
	}
}

// Resizes the vector to contain new_size elements.
// If the current size is greater than new_size, the container is
// reduced to its first new_size elements.

// If the current size is less than new_size,
// additional zero-initialized elements are appended
void resize(Vector *vector, size_t new_size)
{	
	if(vector->size>new_size)
	{
		vector->size=new_size;
	}
	if(new_size>vector->capacity)
		reserve(vector,new_size);
	if(vector->element_size==sizeof(int))
	{
		int* tmp =(int *)vector->data;
		for(size_t i=vector->size; i<new_size; i++)
		{
			tmp[i]=0;
		}
	}
	vector->size=new_size;
}

// Add element to the end of the vector
void push_back(Vector *vector, void *value)
{	
	if(vector->size+1>vector->capacity)
		reserve(vector, vector->capacity*2);

	if(vector->element_size==sizeof(int))
	{
		int *tmp= (int *) vector->data;
		int *value1= (int *) value;
		tmp[(vector->size)] = *value1;
		vector->size+=1;
	}
	else if(vector->element_size==sizeof(char))
	{
		char *tmp= (char *) vector->data;
		char *value1= (char *) value;
		tmp[(vector->size)] = *value1;
		vector->size+=1;
	}
	else
	{
		Person * tmp= (Person *) vector->data;
		Person * value1 = (Person *) value;
		tmp[vector->size] = *value1;
		vector->size+=1;
	}
}

// Remove all elements from the vector
void clear(Vector *vector)
{
	vector->data=realloc(vector->data,vector->size*vector->element_size);
	vector->size=0;
}

// Remove the last element from the vector
// void pop_back(Vector *vector);

// Insert new element at index (0 <= index <= size) position
void insert(Vector *vector, int index, void *value)
{	
	if(vector->size+1>vector->capacity)
		reserve(vector, (vector->size)*2);

	if(vector->element_size==sizeof(int))
	{
		int *tmp= (int*) vector->data;
		int *v= (int*) value;
		for(size_t i=vector->size; i>index; i--)
		{
			tmp[i]=tmp[i-1];
		}
		tmp[index]=*v;
		vector->size+=1;
	}
	else if(vector->element_size==sizeof(char))
	{
		char *tmp= (char*) vector->data;
		char *v= (char*) value;
		for(size_t i=vector->size; i>index; i--)
		{
			tmp[i]=tmp[i-1];
		}
		tmp[index]=*v;
		vector->size+=1;
	}
	else
	{
		Person *tmp= (Person*) vector->data;
		Person *v= (Person*) value;
		for(size_t i=vector->size; i>index; i--)
		{
			tmp[i]=tmp[i-1];
		}
		tmp[index]=*v;
		vector->size+=1;
	}
}

// Erase element at position index
void erase(Vector *vector, int index)
{
	if(vector->element_size==sizeof(int))
	{	
		int *tmp= (int *) vector->data;
		for(int i=index; i<(int)vector->size-1; i++)
				tmp[i]=tmp[i+1];
		vector->size-=1;	
	}
	else if(vector->element_size==sizeof(char))
	{	
		char *tmp= (char *) vector->data;
		for(int i=index; i<(int)vector->size-1; i++)
				tmp[i]=tmp[i+1];
		vector->size-=1;	
	}
	else
	{	
		Person *tmp= (Person *) vector->data;
		for(int i=index; i<(int)vector->size-1; i++)
				tmp[i]=tmp[i+1];
		vector->size-=1;	
	}
}

// Erase all elements that compare equal to value from the container
void erase_value(Vector *vector, void *value, int(*cmp)(const void*, const void*))
{
	for(int i=0; i<vector->size; i++)
	{
		if(cmp(vector->data+((vector->element_size)*i),value)==0)
			erase(vector,i);
	}
}

// Erase all elements that satisfy the predicate from the vector
void erase_if(Vector *vector, int (*predicate)(void *))
{	
	for(int j=0; j<vector->size; j++)
		for(int i=0; i<vector->size; i++)
		{
			if(predicate(vector->data+(i*vector->element_size))==1)
				erase(vector,i);
		}
}

// Request the removal of unused capacity
void shrink_to_fit(Vector *vector)
{
	vector->data=realloc(vector->data,(vector->size*vector->element_size));
	vector->capacity=vector->size;
}

// Print integer vector
void print_vector_int(Vector *vector)
{
	int * tmp=(int *) vector->data;
	printf("%ld\n", vector->capacity);
	for (size_t i=0; i<vector->size; i++)
		{
		printf("%d ", tmp[i]);
		}
}

// Print char vector
void print_vector_char(Vector *vector)
{
	char * tmp=(char *) vector->data;
	printf("%ld\n", vector->capacity);
	for(size_t i=0; i<vector->size; i++)
		printf("%c ", tmp[i]);
}

// Print vector of Person
void print_vector_person(Vector *vector)
{
	Person *tmp= (Person*) vector->data;
	printf("%ld\n", vector->capacity);
	for(size_t i=0; i<vector->size; i++)
		{
			printf("%d %s %s\n", tmp[i].age, tmp[i].first_name, tmp[i].last_name);
		}
}

// integer comparator - increasing order
int int_cmp(const void *v1, const void *v2)
{
	int * value1= (int *) v1;
	int * value2 = (int *) v2;
	if(*value1<*value2)
		return -1;
	if (*value1==*value2)
		return 0;
	return 1;
}

// char comparator - lexicographical order (case sensitive)
int char_cmp(const void *v1, const void *v2)
{
	char *a=(char *)v1;
	char *b=(char *)v2;
	if(*a<*b)
		return -1;
	if(*a==*b)
		return 0;
	return 1;
}

// Person comparator:
// Sort according to age (decreasing)
// When ages equal compare first name and then last name
int person_cmp(const void *p1, const void *p2)
{
Person *h1 = (Person *)p1;
Person *h2 = (Person *)p2;
if(h1->age > h2->age) return -1;
if(h1->age < h2->age) return 1;
if(strcmp(h1->first_name, h2->first_name)!=0) return strcmp(h1->first_name, h2->first_name);
return strcmp(h1->last_name, h2->last_name);
}

// predicate: check if number is even
int is_even(void *value)
{
	int *number =(int *) value;
	if(*number%2==0)
		return 1;
	return 0;
}	

// predicate: check if char is a vowel
int is_vowel(void *value)
{
	char *v = (char *) value;
	if(*v=='a' || *v=='e' || *v=='o' || *v=='u' || *v=='i' || *v=='y' || *v=='A' || *v=='E' || *v=='O' || *v=='U' || *v=='I' || *v=='Y')
		return 1;
	return 0;
}

// predicate: check if person is older than 25
int is_older_than_25(void *person)
{
	Person * someone = (Person *) person;
	if(someone->age>25)
		return 1;
	return 0;
}

// -------------------------------------------------------------

void read_int(void* value) {
	scanf("%d", (int*)value);
}

void read_char(void* value) {
	char c[2];
	scanf("%s", c);
	*(char*)value = c[0];
}

void read_person(void* value) {
	Person *person = (Person*)value;
	scanf("%d %s %s", &person->age, person->first_name, person->last_name);
}

void vector_test(Vector *vector, int n, void(*read)(void*),
		 int (*cmp)(const void*, const void*), int(*predicate)(void*)) {
	char op[2];
	int index;
	size_t size;
	void *v = malloc(vector->element_size);
	for (int i = 0; i < n; ++i) {
		scanf("%s", op);
		switch (op[0]) {
			case 'p': // push_back
				read(v);
				push_back(vector, v);
				break;
			case 'i': // insert
				scanf("%d", &index);
				read(v);
				insert(vector, index, v);
				break;
			case 'e': // erase
				scanf("%d", &index);
				read(v);
				erase(vector, index);
				erase_value(vector, v, cmp);
				break;
			case 'd': // erase (predicate)
				erase_if(vector, predicate);
				break;
			case 'r': // resize
				scanf("%zu", &size);
				resize(vector, size);
				break;
			case 'c': // clear
				clear(vector);
				break;
			case 'f': // shrink
				shrink_to_fit(vector);
				break;
			case 's': // sort
				qsort(vector->data, vector->size,
				      vector->element_size, cmp);
				break;
			default:
				printf("No such operation: %s\n", op);
				break;
		}
	}
	free(v);
}


int main(void) {
	int to_do, n;
	Vector vector_int, vector_char, vector_person;

	scanf("%d%d", &to_do, &n);

	switch (to_do) {
		case 1:
			init_vector(&vector_int, 4, sizeof(int));
			vector_test(&vector_int, n, read_int, int_cmp, is_even);
			print_vector_int(&vector_int);
			free(vector_int.data);
			break;
		case 2:
			init_vector(&vector_char, 2, sizeof(char));
			vector_test(&vector_char, n, read_char, char_cmp, is_vowel);
			print_vector_char(&vector_char);
			free(vector_char.data);
			break;
		case 3:
			init_vector(&vector_person, 2, sizeof(Person));
			vector_test(&vector_person, n, read_person, person_cmp, is_older_than_25);
			print_vector_person(&vector_person);
			free(vector_person.data);
			break;
		default:
			printf("Nothing to do for %d\n", to_do);
			break;
	}

	return 0;
}
