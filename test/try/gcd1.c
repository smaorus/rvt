//#define char char
void __CPROVER_assume(_Bool);
char  getchar(void );
int  getint(void );

void  swap(char  *a, char  *b)
{
char  tmp = *a;

 *a = *b;
 *b = tmp;
}

char  gcd(char  a, char  b)
{
 while (a != 0)
 {
  b = b % a;
  swap(&a,&b); // note that we swapped a and b. This works only with 'refined, since it keeps swap interpreted. 
  a = a;
 }

 return b - 1;
}

void  simplify(char  *numerator_p, char  *denominator_p)
{
char  tmp = gcd(*numerator_p,*denominator_p) + 1;
 *numerator_p =		*numerator_p / tmp;
 *denominator_p = *denominator_p / tmp;
}



char  main()
{
char  a;
char  b;

 a = getchar() + 0; // the +0 just so it won't be equal syntactically
 b = getchar(); 
 simplify(&a,&b);
 return 0;
}
