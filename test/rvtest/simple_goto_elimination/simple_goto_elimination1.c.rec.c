

float  rv_mult(float  x, float  y);
float  rv_div(float  x, float  y);
int  rv_mod(int  x, int  y);
int  main();

unsigned char  Loop_main_do_while1(int  *rvp_i, int  *rvp_rvretval);


int  main()
{
  int  rvretval = 0;
  _Bool  rv_goto_label = 0;
  int  i = 0;

  {
    switch (Loop_main_do_while1(&i,&rvretval))
    {
    case 123:
      return rvretval;
    case 0:
      break;
    }

  }

  return 2;
}

unsigned char  Loop_main_do_while1(int  *rvp_i, int  *rvp_rvretval)
{
  _Bool  rv_goto_label; /* was originally declared outside but is used inside the loop only */
  {
  label:
    rv_goto_label = 0;
    (*rvp_i)++;
    if (*rvp_i == 9)
    {
      {
        *rvp_rvretval = 1;
        return 123;
      }

    }

  }

  if( *rvp_i > 0 )
  return 0;
}




void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
