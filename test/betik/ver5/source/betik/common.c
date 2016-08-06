/*
 Betik
 Copyright (C) 2010 cenan ozen <cenan.ozen[at]gmail.com>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

#define STACK_SIZE 1024

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

void destroy_stack(stack_t* s)
{
	assert(s);
	assert(s->buffer);

	free(s->buffer);
	memset(s, 0, sizeof(stack_t));
	free(s);
}

void stack_push(stack_t* s, void* item)
{
	assert(s);
	assert(s->buffer);
	assert(item);

	unsigned char* ptr = (unsigned char*)s->buffer;
	ptr += s->item_length * s->top;
	memcpy(ptr, item, s->item_length);
	s->top++;
}

const void* stack_pop(stack_t* s)
{
	assert(s);
	assert(s->buffer);
	assert(s->top > 0);

	unsigned char* ptr = (unsigned char*)s->buffer;
	s->top--;
	ptr += s->item_length * s->top;
	return ptr;
}

