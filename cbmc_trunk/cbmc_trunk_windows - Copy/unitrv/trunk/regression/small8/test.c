struct L
{
  struct L *next;
  int data;
};

struct L *l;

int f1(void)
{
  int some;
  
  if(l==0)
    some=5;
  else
  {
    if(l->next!=0)
      some=l->next->data;
    else
      some=10;
  }
  
  l=0;

  return some;
}

int f2(void)
{
  int some;

  if(l==0)
    some=5;
  else
  {
    if(l->next!=0)
      some=l->next->data;
    else
      some=10;
  }

  l=0;

  return some;
}

