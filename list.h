#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

typedef struct gen_list_node gen_list_node;
typedef struct gen_list gen_list;
typedef struct gen_listf gen_listf;

gen_listf* import_gen_listf();
gen_list* gen_list_create(int size);
gen_list_node* gen_list_new_node(void* data, int size);
typedef void (*gen_list_print_data)(void* data);

void gen_list_print(gen_list*, gen_list_print_data);
void gen_list_push(gen_list*, void* data);
void gen_list_add(gen_list*, void* data);
void* gen_list_pop(gen_list* tail);
void* gen_list_remove(gen_list*);
void gen_list_reverse(gen_list*);
void gen_list_insert(gen_list*, int, void* data);
void* gen_list_delete(gen_list* ,int);
void* gen_list_data(gen_list* list,int index);
void gen_list_clear(gen_list* list);
void gen_list_merge_sort(gen_list* list, int (*gen_list_comparator)(void* data1, void* data2));
void gen_list_swap(gen_list_node** n1, gen_list_node** n2);
void* gen_list_first(gen_list* list, int (*gen_list_comparator)(void* data));
gen_list* gen_list_select(gen_list* list, int (*gen_list_comparator)(void* data));
int (*gen_list_comparator)(void* data, ...);
gen_list* gen_list_copy(gen_list* l);
void gen_list_concat(gen_list* list1, gen_list* list2);
gen_list* gen_list_merge(gen_list* list1, gen_list* list2);

struct gen_list_node   {
    void* data;
    gen_list_node *next;
};

struct gen_list {
    gen_list_node* head;
    gen_list_node* tail;
    int size;
    int count;
};

gen_list_node* gen_list_new_node(void* data, int size)    {
    gen_list_node *temp = malloc(sizeof(gen_list_node));
    void* value = malloc(size);
    memcpy (value, data, size);
    temp->data = value;
    temp->next = NULL;
    return temp;
}

gen_list* gen_list_create(int size) {
    gen_list* l = malloc(sizeof(gen_list));
    l->head = NULL;
    l->tail = NULL;
    l->count = 0;
    l->size = size;
    return l;
}

void gen_list_print(gen_list* l, void (*gen_list_print_data)(void*))  {
    gen_list_node *p = l->head;
    while (p != NULL)   {
        gen_list_print_data(p->data);
        p = p->next;
    }
    printf("\n");
}

void gen_list_reverse(gen_list* l)    {
    gen_list_node *currn = (l->head);
    gen_list_node *prevn = NULL;
    gen_list_node *nextn = NULL;
    while (currn != NULL)   {
        nextn = currn->next;
        currn->next = prevn;
        prevn = currn;
        currn = nextn;
    }
    (l->head) = prevn;
}

void gen_list_push(gen_list* l, void* data)  {
    gen_list_node *new_node = gen_list_new_node(data, l->size);
    if ((l->head) == NULL)  {
        (l->head) = new_node;
        (l->tail) = (l->head);
    }
    else    {
        (l->tail)->next = new_node;
        (l->tail) = (l->tail)->next;
    }
    (l->count)++;
}

void* gen_list_pop(gen_list* l)  {
    void* res = NULL;
    if (l->head != NULL)    {
        if (l->head->next == NULL)    {
            res = (l->head)->data;
            (l->head) = NULL;
            (l->tail) = NULL;
        }
        else    {
            res = (l->tail)->data;
            gen_list_node *p = (l->head);
            while (p->next->next != NULL)
                p = p->next;
            free(p->next);
            p->next = NULL;
            (l->tail) = p;
        }
        (l->count)--;
    }
    return res;
}

void gen_list_add(gen_list* l, void* data)   {
    gen_list_node *new_node = gen_list_new_node(data, l->size);
    if ((l->head) == NULL)  {
        (l->head) = new_node;
        (l->tail) = (l->head);
    }
    else   {
        new_node->next = (l->head);
        (l->head) = new_node;
    }
    (l->count)++;
}

void* gen_list_remove(gen_list* l)  {
    void* res = NULL;
    if ((l->head) != NULL)  {
        if (l->head == l->tail) {
            res = (l->head)->data;
            (l->head) = NULL;
            (l->tail) = NULL;            
        }
        else    {
            res = (l->head)->data;
            (l->head) = (l->head)->next;
        }
        (l->count)--;
    }
    return res;
}

void gen_list_insert(gen_list* l, int pos, void* n)    {
    if(pos <= l->count)  {
        if(pos==0)
            gen_list_add(l,n);
        else if(pos==(l->count))
            gen_list_push(l,n);
        else  {
            gen_list_node *temp = l->head;
            gen_list_node *new_node = gen_list_new_node(n, l->size);
            for(int i=0; i<(pos-1); i++)
                temp = temp->next;
            new_node->next = temp->next;
            temp->next = new_node;
            (l->count)++;
        }
    }
}

void* gen_list_delete(gen_list* l, int pos)   {
    void* res = NULL;
    if((pos < l->count) && (l->head != NULL))   {
        if (pos == 0)
            res = gen_list_remove(l);
        else    {
            gen_list_node *temp = l->head;
            for(int i=0; i<(pos-1); i++)
                temp = temp->next;
            res = temp->next->data;
            temp->next = temp->next->next;
            (l->count)--;
        }
    }
    return res;
}

void gen_list_clear(gen_list* l) 
{ 
   gen_list_node* current = l->head; 
   gen_list_node* next; 
  
   while (current != NULL)  
   { 
       next = current->next; 
       free(current); 
       current = next; 
   } 
    l->head = NULL; 
}

void* gen_list_data(gen_list* l,int n)    {
    if(n < l->count) {
        gen_list_node *p = l->head;
        for (int i=0; i<n; i++) {
            p = p->next;
        }
        return p->data;
    }
    return NULL;
}

void gen_list_merge_sort(gen_list* l, int (*gen_list_comparator)(void*, void*)) 
{ 
    gen_list_node** head = &(l->head);
	int len = l->count;

	if (*head == NULL) 
		return; 
	gen_list_node* start1 = NULL, *end1 = NULL; 
	gen_list_node* start2 = NULL, *end2 = NULL; 
	gen_list_node* prevend = NULL; 

	for (int gap = 1; gap < len; gap = gap*2) { 
		start1 = *head; 
		while (start1) { 
			bool isFirstIter = 0; 
			if (start1 == *head) 
				isFirstIter = 1; 

			int counter = gap; 
			end1 = start1; 
			while (--counter && end1->next) 
				end1 = end1->next; 

			start2 = end1->next; 
			if (!start2) 
				break; 
			counter = gap; 
			end2 = start2; 
			while (--counter && end2->next) 
				end2 = end2->next; 

			gen_list_node* temp = end2->next; 

            gen_list_node* temp1 = NULL; 
            if (gen_list_comparator(start1->data,start2->data)) { 
                gen_list_swap(&start1, &start2); 
                gen_list_swap(&end1, &end2); 
            } 

            gen_list_node* astart = start1, *aend = end1; 
            gen_list_node* bstart = start2, *bend = end2; 
            gen_list_node* bendnext = (end2)->next; 
            while (astart != aend && bstart != bendnext) { 
                if (gen_list_comparator(astart->next->data, bstart->data)) { 
                    temp1 = bstart->next;
                    bstart->next = astart->next; 
                    astart->next = bstart; 
                    bstart = temp1; 
                } 
                astart = astart->next; 
            } 
            if (astart == aend) 
                astart->next = bstart; 
            else
                end2 = end1; 

            if (isFirstIter) 
                *head = start1; 
            else
                prevend->next = start1; 

            prevend = end2; 
            start1 = temp; 
        } 
        prevend->next = start1; 
	}
    gen_list_node* p = *head;
    while(p->next != NULL)  {
        p = p -> next;
    }
    l->tail = p;
}

void gen_list_swap(gen_list_node** n1, gen_list_node** n2) {
    gen_list_node* temp = *n1;
    *n1 = *n2;
    *n2 = temp; 
}

void* gen_list_first(gen_list* l, int (*gen_list_comparator)(void*)) {
    gen_list_node* p = l->head;
    void * data = NULL;
    while(!(gen_list_comparator)(p->data) && p != NULL)    {
        p = p->next;
    }
    if(p != NULL)   {
        data = p->data;
    }
    return data;
}

gen_list* gen_list_select(gen_list* l, int (*gen_list_comparator)(void*)) {
    gen_list* res = gen_list_create(l->size);
    gen_list_node* p = l->head;
    while(p != NULL)    {
        if(gen_list_comparator(p->data))    {
            gen_list_push(res,p->data);
        }
        p = p->next;
    }
    return res;
}

gen_list* gen_list_copy(gen_list* l) {
    gen_list* res = gen_list_create(l->size);
    gen_list_node* p = l->head;
    while(p != NULL)    {
        gen_list_push(res,p->data);
        p = p->next;
    }
    return res;
}

gen_list* gen_list_merge(gen_list* list1, gen_list* list2) {
    gen_list* res = gen_list_create(list1->size);
    gen_list_node* p = list1->head;
    while(p != NULL)    {
        gen_list_push(res,p->data);
        p = p->next;
    }
    p = list2->head;
    while(p != NULL)    {
        gen_list_push(res,p->data);
        p = p->next;
    }
    return res;
}

void gen_list_concat(gen_list* list1, gen_list* list2) {
    list1->tail->next = list2->head;
    list1->tail = list2->tail; 
}

/*
void* gen_list_to_array(gen_list* l)   {
    char* res = malloc(sizeof((l->count)*(l->size)));
    gen_list_node* p = l->head;
    for(int i=0; i<l->count; i++)   {
        char* des = res + i*(l->size);
        char* src = (char*)p->data;
        memcpy(des, src, (l->size));
        p = p->next;
    }
    return res;
}
*/
