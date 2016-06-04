int global1, global2;

int f1(int a1, int b1)
{
  global1=1;
  return a1+1;
}

int f2(int a2, int b2)
{
  global1=1;
  return a2+global1;
}
