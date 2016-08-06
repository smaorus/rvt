
#include <stdlib.h>


//void swap(int **ppi, int **ppj) {
//	int tmp = **ppj + 1;
//	**ppj = **ppi;
//	**ppi = tmp - 1;
//}

typedef struct _listitem_t {
	void* data;
	struct _listitem_t* prev;
	struct _listitem_t* next;
} listitem_t;

typedef struct {
	int item_count;
	listitem_t* head;
} list_t;



list_t* create_list(list_t *list)
{
    if (list->head == NULL)
	list->item_count = 0;
	list->head = NULL;

	return list;
}

int access2(list_t** lst) {
	return (*lst)->item_count+0;
}

int access(list_t** lst) {
	return access2(lst);
}


int mainLow (unsigned int k) {
  list_t* list = (list_t*)malloc(sizeof(list_t));

  create_list(list);
  access(&list);
  list->head = (listitem_t*)malloc(sizeof(listitem_t));
  return 0;
}

int main (void) {
  unsigned int k = 5;
  mainLow(k);
  return 0;
}
