int *gp;

int f1(void)
{
  if(gp)
    return *gp+1;
  else
    return 0;
}

int f2(void)
{
  if(gp)
    return *gp+1;
  else
    return 0;
}

