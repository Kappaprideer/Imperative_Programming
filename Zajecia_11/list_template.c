#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1024
#define MEMORY_ALLOCATION_ERROR  -1
#define LIST_ERROR               -2
#define PROGRAM_ERROR            -3

struct tagList;
typedef void (*ConstDataFp)(const void*);
typedef void (*DataFp)(void*);
typedef  int (*CompareDataFp)(const void*, const void*);
typedef void (*InsertInOrder)(struct tagList*, void*);

typedef struct tagListElement {
	struct tagListElement *next;
	void                  *data;
} ListElement;

typedef struct tagList {
	ListElement *head;
	ListElement *tail;
	ConstDataFp dump_data;
	DataFp      free_data;
	CompareDataFp compare_data;
	InsertInOrder insert_sorted;
} List;

// -----------------------------------------------------------------
// generic functions - they are common for all instances of the list
// (independent of the data type)
// -----------------------------------------------------------------

void init_list(List *p_list, ConstDataFp dump_data, DataFp free_data,
			   CompareDataFp compare_data, InsertInOrder insert_sorted) {
	p_list->dump_data=dump_data;
	p_list->free_data=free_data;
	p_list->compare_data=compare_data;
	p_list->insert_sorted=insert_sorted;
}

// Print all elements of the list
void dump_list(const List* p_list) {

	ListElement *tmp;
	tmp = p_list->head;
	while(tmp)
	{
		p_list->dump_data(tmp->data);
		tmp=tmp->next;
	}
}

// Print elements of the list if comparable to data
void dump_list_if(List *p_list, void *data) {
	ListElement *element;
	element = p_list->head;
	while(element)
	{
		if(p_list->compare_data(data,element->data)==0)
			p_list->dump_data(element->data);
		element=element->next;
	}
}

// Free all elements of the list
void free_list(List* p_list) {

	void* first;
	p_list->tail=NULL;
	while(p_list->head)
	{
		first=p_list->head;
		p_list->head=p_list->head->next;
		p_list->free_data(first);
	}
}

// Push element at the beginning of the list
void push_front(List *p_list, void *data){
	ListElement *element = malloc(sizeof(ListElement));
	if (element == NULL ) exit(MEMORY_ALLOCATION_ERROR);
	element->data=data;
	if(p_list->head)
	{
		element->next=p_list->head;
		p_list->head=element;
	}
	if (!p_list->head)
	{
		element->next=NULL;
	 	p_list->head=element;
	 	p_list->tail=element;
	}

}

// Push element at the end of the list
void push_back(List *p_list, void *data) {
	ListElement *element = malloc(sizeof(ListElement));
	if(element == NULL) exit(MEMORY_ALLOCATION_ERROR);
	element->data = data;
	element->next = NULL;
	if(p_list->tail) p_list->tail->next = element;
	p_list->tail = element;
	if(!p_list->head) p_list->head = p_list->tail;
}

// Remove the first element
void pop_front(List *p_list) {
	void *first;
	if(p_list->head)
	{
		first=p_list->head;
		p_list->head=p_list->head->next;
		free(first);
	}
}

// Reverse the list
void reverse(List *p_list) {
	ListElement* one = malloc(sizeof(ListElement));
	ListElement* two = malloc(sizeof(ListElement));
	ListElement* three = malloc(sizeof(ListElement));
	
	two=p_list->head;
	
	void* tmp = p_list->head;
	p_list->head=p_list->tail;
	p_list->tail=tmp;
	
	one=NULL;
	if(two)
	{	
		three=two->next;
		while(three)
		{
			two->next=one;
			one=two;
			two=three;
			three=three->next;
		}
		two->next=one;
	}

}

// insert element preserving the ordering (defined by insert_sorted function)
void insert_in_order(List *p_list, void *data) {
	p_list->insert_sorted(p_list, data);
}

// find element in sorted list after which to insert given element
ListElement* find_insertion_point(const List *p_list, void* p_element) {
	ListElement* first;
	if(p_list->compare_data(p_element,p_list->head)<0)
	{
		return NULL;
	}
	first=p_list->head;
	while(first)
	{
		if(p_list->compare_data(first->data, p_element)<0 && (first->next==NULL || p_list->compare_data(p_element,first->next->data)<0))
			return first;
		first=first->next;
	}
	return first;
}

// Insert element after 'previous'
void push_after(List *p_list, void *data, ListElement *previous) {

	ListElement* element=malloc(sizeof(ListElement));
	element->data=data;

	if(previous==NULL)
	{
		element->next=p_list->head;
		p_list->head=element;
	}
	else
	{
	element->next=previous->next;
	previous->next=element;
	if(element->next==NULL) p_list->tail = element;
	}	
}

// Insert element preserving order (no counter)
void insert_elem(List *p_list, void *p_data) {
	ListElement* tmp;
	tmp = p_list->head;
	int exist=0;
	while(tmp)
	{
		if(p_list->compare_data(p_data,tmp->data)==0)
			exist=1;
		tmp=tmp->next;
	}
	if(!exist) push_after(p_list, p_data, find_insertion_point(p_list, p_data));
}

// ---------------------------------------------------------------
// type-specific definitions
// ---------------------------------------------------------------

// int element

typedef struct DataInt {
	int id;
} DataInt;

void dump_int(const void *d) {
	int* x = (int*) d;
	printf("%d ",*x);
}

void free_int(void *d) {
	free(d);
}

int cmp_int(const void *a, const void *b) {
	int one = ((DataInt*)a)->id;
	int two = ((DataInt*)b)->id;
	return one-two;
}

DataInt *create_data_int(int v) {
	DataInt* tmp= malloc(sizeof(DataInt));
	tmp->id=v;
	return tmp;
}

// Word element

typedef struct DataWord {
	char *word;
	int counter;
} DataWord;

void dump_word (const void *d) {
	char * x = ((DataWord *)d)->word;
	printf("%s\n", x);
}

void dump_word_lowercase (const void *d) {
	char * x = ((DataWord *)d)->word;
	printf("%s\n", x);
}

void free_word(void *d) {
	free(d);
}

// conpare words case insensitive
int cmp_word_alphabet(const void *a, const void *b) {
	char * one = ((DataWord*)a)->word;
	char * two = ((DataWord*)b)->word;
	return strcmp(one,two);
}

int cmp_word_counter(const void *a, const void *b) {
	int one = ((DataWord*)a)->counter;
	int two = ((DataWord*)b)->counter;
	return two-one;
}

// insert element; if present increase counter
void insert_elem_counter(List *p_list, void *data) {
	ListElement* tmp;
	tmp = p_list->head;
	int exist=0;
	while(tmp)
	{
		DataWord* one = (DataWord*) tmp;
		if(p_list->compare_data(data,tmp->data)==0)
		{
			exist=1;
			one->counter+=1;
		}
		tmp=tmp->next;
	}
	if(!exist) push_after(p_list, data, find_insertion_point(p_list, data));
}

// read text, parse it to words, and insert those words to the list
// in order given by the last parameter (0 - read order,
// 1 - alphabetical order)
void stream_to_list(List *p_list, FILE *stream, int order) {
	char line[128];
	char znaki[]=".,?!:;- 	\n\r";
	if(order==0)
	{
	while(fgets(line, 128, stdin)!=NULL)
	{	
		char *words;
		words=strtok(line, znaki);
		while(words != NULL)
		{
			DataWord* one = malloc(sizeof(DataWord));
			one->word = malloc(sizeof(words));
			one->word=strdup(words);
			push_back(p_list, one);
			words=strtok(NULL, znaki);
		}
	}
	}
	else
	{
	while(fgets(line, 128, stdin)!=NULL)
	{	
		char *words;
		words=strtok(line, znaki);
		while(words != NULL)
		{
			DataWord* one = malloc(sizeof(DataWord));
			one->word = malloc(sizeof(words));
  			for(char *p=words; *p; p++) *p=tolower(*p);
			one->word=strdup(words);
			one->counter=0;
			printf("WCZYTUJE DANE\n");
			insert_elem_counter(p_list,one);
			words=strtok(NULL, znaki);
		}
	}
	}
}

// test integer list
void list_test(List *p_list, int n) {
	char op[2];
	int v;
	for (int i = 0; i < n; ++i) {
		scanf("%s", op);
		switch (op[0]) {
			case 'f':
				scanf("%d", &v);
				push_front(p_list, create_data_int(v));
				break;
			case 'b':
				scanf("%d", &v);
				push_back(p_list, create_data_int(v));
				break;
			case 'd':
				pop_front(p_list);
				break;
			case 'r':
				reverse(p_list);
				break;
			case 'i':
				scanf("%d", &v);
				insert_in_order(p_list, create_data_int(v));
				break;
			default:
				printf("No such operation: %s\n", op);
				break;
		}
	}
}

int main(void) {
	int to_do, n;
	List list;

	scanf ("%d", &to_do);
	switch (to_do) {
		case 1: // test integer list
			scanf("%d",&n);
			init_list(&list, dump_int, free_int,
					  cmp_int, insert_elem);
			list_test(&list, n);
			dump_list(&list);
			free_list(&list);
			break;
		
		case 2: // read words from text, insert into list, and print
			init_list(&list, dump_word, free_word,
					  cmp_word_alphabet, insert_elem_counter);
			stream_to_list(&list, stdin, 0);
			dump_list(&list);
			free_list(&list);
			break;
		case 3: // read words, insert into list alphabetically, print words encountered n times
			scanf("%d",&n);
			init_list(&list, dump_word_lowercase, free_word,
			          cmp_word_alphabet, insert_elem_counter);
			stream_to_list(&list, stdin, 1);
			list.compare_data = cmp_word_counter;
			DataWord data = { NULL, n };
//			list.dump_data = dump_word_lowercase;
			dump_list_if(&list, &data);
			printf("\n");
			free_list(&list);
			break;
		
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}

