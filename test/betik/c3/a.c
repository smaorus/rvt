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
#ifndef common_h 
#define common_h 
struct stack { 
	int      top; 
	void*    buffer; 
	unsigned item_length; 
};
 #define stack_t struct stack
 
stack_t* create_stack(unsigned item_length); 
void destroy_stack(stack_t* s); 
void stack_push(stack_t* s, void* item); 
const void* stack_pop(stack_t* s); 
#endif // common_h 
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
#ifndef token_h 
#define token_h 
#define MAX_IDENT_LENGTH   64 
#define MAX_STRING_LENGTH  1024 
enum token_type { 
	TT_NONE=    0, 
	TT_IDENT=   1, 
	TT_NUMBER=  2, 
	TT_STRING=  3, 
	TT_EOF=     4, 
	TT_UNKNOWN= 5, 
	TT_OP_AND=  10, 
	TT_OP_OR=   11, 
};
 #define token_type_t enum token_type
 
struct tokenizer { 
	char* source; 
	int source_index; 
	stack_t* index_stack; 
	void* token_value; 
	token_type_t token_type; 
	int line_number; 
};
 #define tokenizer_t struct tokenizer
 
#endif // token_h 
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

#ifndef parser_h
#define parser_h

#endif // parser_h

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

int main(int argc, char* argv[])
{
	return 0;
}

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

#include <stdio.h>
#include <stdlib.h>


static int is_whitespace(char c)
{
	return ((c == ' ') || (c == '\t') || (c == '\r') || (c == '\n'));
}

static int is_alpha(char c)
{
	if (c < 0)
	{
		return 1;
	}
	return (((c >= 'a') && (c <= 'z')) || 
	        ((c >= 'A') && (c <= 'Z')) ||
	        (c == '_'));
}

static int is_alphanum(char c)
{
	return (is_alpha(c) || isdigit(c));
}

static int is_digit(char c)
{
	return ((c >= '0') && (c <= '9'));
}

static struct {
	char* str;
	token_type_t token_type;
} keywords[] = {
	{"and",    TT_OP_AND},
	{"or",     TT_OP_OR},
};

void init_tokenizer(tokenizer_t* t, char* source)
{
	t->source = (char*)malloc(strlen(source) + 1);
	strcpy(t->source, source);
	t->source_index = 0;
	t->index_stack = create_stack(sizeof(int));
	t->token_value = NULL;
	t->token_type = TT_NONE;
	t->line_number = 1;
}

void release_tokenizer(tokenizer_t* t)
{
	free(t->source);
	free(t->token_value);
	destroy_stack(t->index_stack);
	memset(t, 0, sizeof(tokenizer_t));
}

static void eatwhitespace(tokenizer_t* t)
{
eatwhitespace_begin:

	while (is_whitespace(t->source[t->source_index])) {
		if ('\n' == t->source[t->source_index]) {
			t->line_number++;
		}
		t->source_index++;
	}

	// single line comments
	if (t->source[t->source_index] == '#') {
		while (t->source[t->source_index] != '\n') {
			// incase there is a comment on the last line
			// or the only line is a comment line then
			// we should check for an EOF
			if (t->source[t->source_index] == '\0') {
				break;
			}
			t->source_index++;
		}
		goto eatwhitespace_begin;
	}

	// multi line comments
	if (('/' == t->source[t->source_index]) &&
	    ('*' == t->source[t->source_index+1])) {
		t->source_index += 2;
		while (t->source[t->source_index] != '\0') {
			if (('*' == t->source[t->source_index]) &&
			    ('/' == t->source[t->source_index+1])) {
				t->source_index += 2;
				break;
			}
			t->source_index++;
		}
		goto eatwhitespace_begin;
	}

}


static void tokenize_number(tokenizer_t* t)
{
	t->token_type == TT_NUMBER;
	t->token_value = malloc(sizeof(int));
	(*(int*)(t->token_value)) = t->source[t->source_index++] - '0';
	while (is_digit(t->source[t->source_index])) {
		(*(int*)(t->token_value)) *= 10;
		(*(int*)(t->token_value)) += t->source[t->source_index] - '0';
	}
}

static void tokenize_identifier(tokenizer_t* t)
{
	int i = 0;

	t->token_value = (char*)malloc(MAX_IDENT_LENGTH);
	((char*)(t->token_value))[i++] = t->source[t->source_index++];
	while (is_alphanum( t->source[t->source_index])) {
		((char*)(t->token_value))[i++] = t->source[t->source_index++];
		if (MAX_IDENT_LENGTH == i) {
			fprintf(stderr, "MAX_IDENT_LENGTH reached :%d\n", t->line_number);
			exit(1);
		}
	}
	((char*)(t->token_value))[i] = '\0';
	for (i = 0; i < sizeof(keywords) / sizeof(keywords[0]); ++i) {
		if (strcmp(((char*)(t->token_value)), keywords[i].str) == 0) {
			t->token_type = keywords[i].token_type;
			return;
		}
	}
	t->token_type = TT_IDENT;
}

static void tokenize_string(tokenizer_t* t)
{
	int i = 0;

	t->token_value = malloc(MAX_STRING_LENGTH);
	t->source_index++;
	while (t->source[t->source_index] != '"') {
		if (t->source[t->source_index] == '\\') {
			if (t->source[t->source_index+1] == 'n') {
				((char*)(t->token_value))[i++] = '\n';
				t->source_index += 2;
			}
			else if (t->source[t->source_index+1] == '"') {
				((char*)(t->token_value))[i++] = '\"';
				t->source_index += 2;
			}
			else if (t->source[t->source_index+1] == '\\') {
				((char*)(t->token_value))[i++] = '\\';
				t->source_index += 2;
			}
			else {
				((char*)(t->token_value))[i++] = '\\';
				t->source_index++;
			}
		}
		else {
			((char*)(t->token_value))[i++] = t->source[t->source_index++];
		}
		if (i >= MAX_STRING_LENGTH) {
			fprintf(stderr, "max inline string length reached\n");
			exit(EXIT_FAILURE);
		}
	}
	((char*)(t->token_value))[i] = '\0';
	t->source_index++; // eat last "
	t->token_type = TT_STRING;
}

token_type_t get_token(tokenizer_t* t)
{
	if (t->token_value) {
		free(t->token_value);
		t->token_value = NULL;
	}

	eatwhitespace(t);

	stack_push(t->index_stack, &t->source_index);

	if ('\0' == t->source[t->source_index]) {
		t->token_type = TT_EOF;
		return TT_EOF;
	}

	if (is_digit(t->source[t->source_index])) {
		tokenize_number(t);
		return TT_NUMBER;
	}

	if (is_alpha(t->source[t->source_index])) {
		tokenize_identifier(t);
		return TT_IDENT;
	}

	if ('"' == t->source[t->source_index]) {
		tokenize_string(t);
		return TT_STRING;
	}

	return TT_UNKNOWN;
}

