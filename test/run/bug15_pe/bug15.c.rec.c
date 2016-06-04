

int  main();

unsigned char  Loop_main_while1(int  *rvp_x, int  *rvp_rvretval);


int  main()
{
  int  rvretval = 0;
  int  x = 1;
  int  y;

  {
    Loop_main_while1(&x,&rvretval);
  }

  return x << 1;
}

unsigned char  Loop_main_while1(int  *rvp_x, int  *rvp_rvretval)
{
  int  y; /* was originally declared outside but is used inside the loop only */
  if( !(*rvp_x <= 9) )
    return 0;

  {
    y = *rvp_x + 2;
    *rvp_x = 2 * y;
  }

  return 0;
}




void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
