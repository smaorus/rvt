#include <stdlib.h>
#include <assert.h>


#define STACK_SIZE 1024


typedef struct {
	int      top;
	void*    buffer;
	unsigned item_length;
} stack_t;


stack_t* create_stack(unsigned item_length)
{
	assert(item_length != 0);

	stack_t* s = (stack_t*)malloc(sizeof(stack_t));

	assert(s);

	s->top = 0;
	s->buffer = malloc(STACK_SIZE * item_length);

	assert(s->buffer != NULL);

	s->item_length = item_length;

	return s;
}

int main() {
	stack_t* s = create_stack(10);
	return 0;
}
