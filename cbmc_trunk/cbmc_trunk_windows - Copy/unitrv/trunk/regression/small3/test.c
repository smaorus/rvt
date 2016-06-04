struct L
{
  struct L *next;
  int data;
};

int f1(int a1, int b1, struct L *l)
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

  return some;
}

int f2(int a2, int b2, struct L *l)
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

  return some;
}

