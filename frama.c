float  rv_mult(float  x, float  y);float  rv_div(float  x, float  y);int  rv_mod(int  x, int  y);int  r(int  n);int  f(int  n);int  main(int  x);int  r(int  n)
{
  if (n < 0)
  {
    return 8;
  }

  return 5;
}
int  f(int  n)
{
  if (n <= 0)
  {
    return 1;
  }

  if (Frama_C_interval(1,5) < 0)
  {
    return 4;
  }

  else
  {
    return r(n);
  }

}
int  main(int  x)
{
  return f(x);
}
void  __CPROVER_assume(_Bool  rv_arg_1);