

typedef unsigned int  size_t;
//struct _listitem_t {
//  void  *data;
//  struct _listitem_t  *prev;
//  struct _listitem_t  *next;
//};
//typedef struct _listitem_t  listitem_t;
struct list_t {
  int  item_count;
  //listitem_t  *head;
};
//typedef struct list_t  list_t;
extern void  *malloc(size_t  size);


int  main();

int  access2(struct list_t  **lst)
{
  struct list_t  *mem_2;

      mem_2 = *lst;
      if (mem_2 == 0)
    	  access2(&mem_2);
      return mem_2->item_count+1;

}



int  main()
{
  struct list_t  *list;
  void  *tmp;

	struct list_t locvar[2];
	//struct list_t *ptr = locvar;
//tmp = locvar; //malloc(sizeof(struct list_t ) );
list = (struct list_t *) locvar;//(tmp);
return access2(&list);

}


