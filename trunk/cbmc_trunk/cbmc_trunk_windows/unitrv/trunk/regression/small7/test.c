int *gp;
int z;

int f1(int a1, int b1)
{
  if(gp)
    *gp=a1;
  else
    z=1;

  return 0;
}

int f2(int a2, int b2)
{
  if(gp)
    *gp=a2;

  return 0;
}
