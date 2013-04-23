typedef enum {
	TT_NONE=    0,
	TT_IDENT=   1,
	TT_NUMBER=  2,
	TT_STRING=  3,
	TT_EOF=     4,
	TT_UNKNOWN= 5,
	TT_OP_AND=  10,
	TT_OP_OR=   11,
} token_type_t;

typedef struct {
	//int      top;
	//void*    buffer;
	unsigned item_length;
} stack_t;

typedef struct {
	//char* source;
	int source_index;
	stack_t* index_stack;
	//void* token_value;
	//token_type_t token_type;
	//int line_number;
} tokenizer_t;

typedef struct {
  tokenizer_t  *t;
} parser_t;

parser_t *gP;

int eatwhitespace(tokenizer_t* t)
{
	t->source_index++;
	return 1;
}

int call_eatwhitespace(parser_t** p) {
	int res = 0;
	//t = 0;
	res = eatwhitespace((*p)->t);
	//++t->index_stack->item_length;
	return res;
}

int main() {
	call_eatwhitespace(&gP);
	return ++gP->t->index_stack->item_length;
}
