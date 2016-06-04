

float  rv_mult(float  x, float  y);
float  rv_div(float  x, float  y);
int  rv_mod(int  x, int  y);
typedef struct B {
  int  a;
  struct B  *next;
} B_t;
void  g(B_t  *pb, B_t  *src, int  c);

int  main();

unsigned char  Loop_g_while1(B_t  **rvp_cur, B_t  **rvp_pb);


void  g(B_t  *pb, B_t  *src, int  c)
{
  B_t  *cur = src;

  pb->a = 0;
  {
    Loop_g_while1(&cur,&pb);
  }

  pb->a += cur->a;
}

unsigned char  Loop_g_while1(B_t  **rvp_cur, B_t  **rvp_pb)
{
  if( !((*rvp_cur)->a != 0) )
    return 0;

  {
    (*rvp_pb)->a += 1;
    *rvp_cur = (*rvp_cur)->next;
  }

  return 0;
}



int  main()
{
  B_t  b1;
  B_t  b2;

  g(&b1,&b2,b2.a);
  return 0;
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
