

float  rv_mult(float  x, float  y);
float  rv_div(float  x, float  y);
int  rv_mod(int  x, int  y);
typedef enum { TT_NONE = 0, TT_IDENT = 1, TT_NUMBER = 2, TT_STRING = 3, TT_EOF = 4, TT_UNKNOWN = 5, TT_OP_AND = 10, TT_OP_OR = 11 } token_type_t;
typedef struct {
  unsigned int  item_length;
} stack_t;
typedef struct {
  int  source_index;
  stack_t  *index_stack;
} tokenizer_t;
typedef struct {
  tokenizer_t  *t;
} parser_t;
parser_t  *gP;
int  eatwhitespace(tokenizer_t  *t);

int  call_eatwhitespace(parser_t  **p);

int  main();

int  eatwhitespace(tokenizer_t  *t)
{
  ++t->source_index;
  return 1;
}


int  call_eatwhitespace(parser_t  **p)
{
  int  res;

  res = eatwhitespace((*p)->t);
  return res;
}


int  main()
{
  call_eatwhitespace(&gP);
  return ++gP->t->index_stack->item_length;
}



void __CPROVER_assume(_Bool);

/* Hub functions for indirect function calls: */
