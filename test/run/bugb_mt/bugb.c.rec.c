

float  rv_mult(float  x, float  y);
float  rv_div(float  x, float  y);
int  rv_mod(int  x, int  y);
enum Elem { ELEM0, ELEM1, ELEM2 };
typedef struct B {
  int  a;
  char  b;
  enum Elem  c;
  struct B  *next;
} B_t;
int  getA(B_t  *src);

void  g(B_t  *pb, B_t  *src, enum Elem  c);

int  main();

int  getA(B_t  *src)
{
  B_t  tmp = { 0, '\0', ELEM0, 0 };

  if (src != 0)
    return src->a;
  return getA(&tmp);
}


unsigned char  Loop_g_while1(B_t  **rvp_cur, B_t  **rvp_pb);


void  g(B_t  *pb, B_t  *src, enum Elem  c)
{
  B_t  *cur = src;

  if (pb == 0 || src == 0)
    return;
  pb->a = getA(0);
  {
    Loop_g_while1(&cur,&pb);
  }

  pb->b = cur->b;
}

unsigned char  Loop_g_while1(B_t  **rvp_cur, B_t  **rvp_pb)
{
  if( !((*rvp_cur)->next != 0) )
    return 0;

    (*rvp_pb)->b = 0;
  return 0;
}



int  main()
{
  B_t  b1;
  B_t  b2;

  g(&b1,&b2,b2.c);
  return 0;
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
