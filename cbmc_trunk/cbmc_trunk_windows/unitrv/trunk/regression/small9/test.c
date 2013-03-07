struct L
{
  struct L *next;
  int data;
};

void f1(int a1, int b1, struct L *l)
{
  if(!l)
    l->data=a1;
}

void f2(int a2, int b2, struct L *l)
{
  if(!l)
    l->data=a2;
}

