int global1;

int f1(int a1)
{
  global1++;
  return 0;
}

int f2(int a2)
{
  global1=1;
  return 0;
}

