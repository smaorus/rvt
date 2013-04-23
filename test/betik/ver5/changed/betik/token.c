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

#include "token.h"

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

void unget_token(tokenizer_t* t)
{
	int prev_source_index = *(int*)stack_pop(t->index_stack);
	if (t->source_index <= prev_source_index) {
		t->source_index = prev_source_index;
		return;
	}
	do {
		t->source_index--;
		if ('\n' == t->source[t->source_index]) {
			t->line_number--;
		}
	} while (t->source_index > prev_source_index);
}

#include "seatest.h"

static void tokenizer_test1()
{
	tokenizer_t* t = (tokenizer_t*)malloc(sizeof(tokenizer_t));
	init_tokenizer(t, " 1 \"asd\" 3");
	assert_int_equal(TT_NUMBER, get_token(t));
	assert_int_equal(TT_STRING, get_token(t));
	assert_int_equal(TT_NUMBER, get_token(t));
	unget_token(t);
	unget_token(t);
	unget_token(t);
	assert_int_equal(TT_NUMBER, get_token(t));
	assert_int_equal(TT_STRING, get_token(t));
	assert_int_equal(TT_NUMBER, get_token(t));
	release_tokenizer(t);
	free(t);
}

void tokenizer_test_fixture(void)
{
	test_fixture_start();
	run_test(tokenizer_test1);
	test_fixture_end();
}

