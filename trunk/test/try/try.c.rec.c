

float  rv_mult(float  x, float  y);
float  rv_div(float  x, float  y);
int  rv_mod(int  x, int  y);
enum Elem { ELEM0 = 0, ELEM1 = 1, ELEM2 = 2 };
struct B {
  int  a;
  enum Elem  b;
};
typedef struct B  B_t;
void  g(B_t  *pb, B_t  *src, enum Elem  c);

int  main(void );

unsigned char  Loop_g_while1(B_t  *cur, B_t  **rvp_pb);


void  g(B_t  *pb, B_t  *src, enum Elem  c)
{
  B_t  *cur;

  {
    cur = src;
    pb->a = 0;
    {
      Loop_g_while1(cur,&pb);
    }

    pb->a += cur->a;
    return;
  }

}

unsigned char  Loop_g_while1(B_t  *cur, B_t  **rvp_pb)
{
  if( !(cur->a != 0) )
    return 0;

  {
    (*rvp_pb)->a++;
  }

  return 0;
}



int  main(void )
{
  B_t  b1;
  B_t  b2;

  {
    b2.b = (enum Elem ) (0);
    g(&b1,&b2,b2.b);
    return 0;
  }

}


