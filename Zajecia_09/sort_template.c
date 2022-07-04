#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR_LEN 64
#define MAX_PERSONS 1024

typedef struct Person {
	int age;
	char first_name[MAX_STR_LEN];
	char last_name[MAX_STR_LEN];
} Person;

// Sort according to age (decreasing)
// When ages equal compare first name and then last name
int cmp_person(const void *p1, const void *p2)
{
Person *h1 = (Person *)p1;
Person *h2 = (Person *)p2;
if(h1->age > h2->age) return -1;
if(h1->age < h2->age) return 1;
if(strcmp(h1->first_name, h2->first_name)!=0) return strcmp(h1->first_name, h2->first_name);
return strcmp(h1->last_name, h2->last_name);
}

// Read data to Person array (till EOF)
int read_person_array(Person *persons)
{
	int n=0;
	char line[MAX_STR_LEN];
	while(fgets(line, MAX_STR_LEN, stdin)!=NULL && strlen(line)>1)
	{
	sscanf(line,"%d %s %s", &persons[n].age, persons[n].first_name, persons[n].last_name);
	++n;
	}
	return n;
}

// Print Person array
void print_person_array(Person *persons, int n)
{
	for(int i=0; i<n; i++)
	{
		printf("%d %s %s\n", persons[i].age, persons[i].first_name, persons[i].last_name);
	}
}

// Sort women first (woman's first name ends with 'a');
// Then sort women by age and men by last name
// Line consists of: age, first_name, last_name
// (int that order)
int cmp_lines(const void *l1, const void *l2)
{
	char *p1 =(char *)l1;
	char *p2 =(char *)l2;
	int age1=0, age2=0;
	char name1[MAX_STR_LEN], name2[MAX_STR_LEN], last1[MAX_STR_LEN], last2[MAX_STR_LEN];
	sscanf(p1,"%d %s %s", &age1, name1, last1);
	sscanf(p2,"%d %s %s", &age2, name2, last2);
	if(name1[strlen(name1)-1]=='a' && name2[strlen(name2)-1]!='a') return -1;
	if(name1[strlen(name1)-1]!='a' && name2[strlen(name2)-1]=='a') return 1;
	if(name1[strlen(name1)-1]=='a' && name2[strlen(name2)-1]=='a')
		return age1-age2;
	return strcmp(last1,last2);

}

// Read lines with students' data (as text)
int read_lines(char lines[][MAX_STR_LEN])
{
	int n=0;
	char text[MAX_STR_LEN];
	while(fgets(text, MAX_STR_LEN, stdin)!=NULL && strlen(text)>1)
	{
	strcpy(lines[n],text);
	++n;
	}
	return n;
}

// Print sorted lines
void print_lines(char lines[][MAX_STR_LEN], int n)
{
	int age=0;
	char first[MAX_STR_LEN], second[MAX_STR_LEN];
	for(int i=0; i<n; i++)
	{
		sscanf(lines[i], "%d %s %s", &age, first, second);
		printf("%d %s %s\n", age, first, second); 
	}
}

// -------------------------------------------------

int read_int() {
	char buf[MAX_STR_LEN];
	int n;
	fgets(buf, MAX_STR_LEN, stdin);
	sscanf(buf, "%d", &n);
	return n;
}

int main(void) {
	int to_do = read_int();
	int n;
	Person persons[MAX_PERSONS];
	char lines[MAX_PERSONS][MAX_STR_LEN];
	switch (to_do) {
		case 1:
			n = read_person_array(persons);
			qsort(persons, (size_t)n, sizeof(Person), cmp_person);
			print_person_array(persons, n);
			break;
		
		case 2:
			n = read_lines(lines);
			qsort(lines, (size_t) n, MAX_STR_LEN, cmp_lines);
			print_lines(lines, n);
			break;
		
		default:
			printf("Nothing to do for %d\n", to_do);
			break;
	}
}

