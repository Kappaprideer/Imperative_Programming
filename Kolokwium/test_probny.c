typedef struct {

   int size; // liczba napisów (długość tablicy)

   char **strings; // tablica wskaźników do napisów

} StringTable;

int st_insert(StringTable *st, const char *txt, int index)
{
if(index>st->size)
    return 1;
st->size+=1
realloc(st->strings, sizeof(st->strings)+sizeof(char)*index


}


return 0;
}





























// struct Data {
//     int tab[20];
//     int in_tab;   // liczba aktywnych elementów w tablicy tab
//     int sum;      // suma aktywnych elementów 
// }

// struct ListElement {
//     struct Data  data;
//     struct ListElement *prev;
//     struct ListElement *next;
// }


// struct List{
// struct ListElement *head;
// }

// void initList(struct List* plist)
// {
// *plist=malloc(sizeof(struct List));
// plist->head=NULL;
// }
// void addelement(struct List* plist, const struct Data *data)
// {
// struct ListElement  *new = malloc(sizeof(struct ListElement));
// new->next=NULL;
// new->prev=NULL;
// new->data=data
// struct ListElement *element;
// element=plist->head;
// whlie(element)
// {}}

// void print_above(const struct List* plist,  int threshold)
// {
// struct ListElement *element=plist->head;
// for(element; element!=0; element=element->next)
// {
// if(element->data->->sum>threshold)
// {
// for(int i=0; i<element->data->int_tab; i++)
// printf("%d ",element->data->tab[i];)
// }}}


// void print_if(const struct List* plist,  int (*pred)(const struct Data*data))
// {
// ListElement *element=plist->head;
// for(element; element != 0 ; element=element->next)
// {
// if(pred(element->data))
// for(int i=0; i<elemnt->data->in_tab; i++)
// printf("%d ", element->data->tab[i]);
// }
// }
// int Predicate_function(const struct Data *data)
// {
// return data->sum%2==0;
// }

// void test_print_if(const struct List* plist)
// {
// print_if(plist,Predicate_function);
// }

