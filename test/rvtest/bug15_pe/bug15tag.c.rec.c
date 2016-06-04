

int  main();

unsigned char  Loop_main_while1(int  *rvp_x, int  *rvp_rvretval);


int  main()
{
  int  rvretval = 0;
  int  y;
  int  x = 1;

  {
    Loop_main_while1(&x,&rvretval);
  }

  return x * 2;
}

unsigned char  Loop_main_while1(int  *rvp_x, int  *rvp_rvretval)
{
  int  y; /* was originally declared outside but is used inside the loop only */
  if( !(*rvp_x < 10) )
    return 0;

  {
    y = 2 + *rvp_x;
    *rvp_x = y + y;
  }

  {
    return Loop_main_while1(rvp_x,rvp_rvretval);
  }
  return 0;
}




void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
