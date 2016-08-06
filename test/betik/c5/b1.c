#include <ctype.h>

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

typedef struct {
	int      top;
	void*    buffer;
	unsigned item_length;
} stack_t;

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
	char* source;
	int source_index;
	stack_t* index_stack;
	void* token_value;
	token_type_t token_type;
	int line_number;
} tokenizer_t;

void init_tokenizer(tokenizer_t* t, char* source);
void release_tokenizer(tokenizer_t* t);
token_type_t get_token(tokenizer_t* t);
void unget_token(tokenizer_t* t);

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


typedef struct {
	tokenizer_t* t;
} parser_t;

#endif // parser_h

#ifndef SEATEST_H
#define SEATEST_H
#include <stdio.h>

/*
Declarations
*/

void seatest_test_fixture_start(char* filepath);
void seatest_test_fixture_end( void );
void seatest_simple_test_result(int passed, char* reason, const char* function, unsigned int line);
void seatest_assert_true(int test, const char* function, unsigned int line);
void seatest_assert_false(int test, const char* function, unsigned int line);
void seatest_assert_int_equal(int expected, int actual, const char* function, unsigned int line);
void seatest_assert_float_equal(float expected, float actual, float delta, const char* function, unsigned int line);
void seatest_assert_double_equal(double expected, double actual, double delta, const char* function, unsigned int line);
void seatest_assert_string_equal(char* expected, char* actual, const char* function, unsigned int line);
void seatest_assert_string_ends_with(char* expected, char* actual, const char* function, unsigned int line);
void seatest_assert_string_starts_with(char* expected, char* actual, const char* function, unsigned int line);
void seatest_assert_string_contains(char* expected, char* actual, const char* function, unsigned int line);
void seatest_assert_string_doesnt_contain(char* expected, char* actual, const char* function, unsigned int line);
int seatest_should_run( char* fixture, char* test);
void seatest_run_test(void);
void seatest_setup();
void seatest_teardown();

/*
Assert Macros
*/

#define assert_true(test) do { seatest_assert_true(test, __FUNCTION__, __LINE__); } while (0)
#define assert_false(test) do {  seatest_assert_false(test, __FUNCTION__, __LINE__); } while (0)
#define assert_int_equal(expected, actual) do {  seatest_assert_int_equal(expected, actual, __FUNCTION__, __LINE__); } while (0)
#define assert_string_equal(expected, actual) do {  seatest_assert_string_equal(expected, actual, __FUNCTION__, __LINE__); } while (0)
#define assert_n_array_equal(expected, actual, n) do { int count; for(count=0; count<n; count++) { char s[100]; sprintf(s,"Expected %d to be %d at position %d", actual[count], expected[count], count); seatest_simple_test_result((expected[count] == actual[count]), s, __FUNCTION__, __LINE__);} } while (0)
#define assert_bit_set(bit_number, value) { seatest_simple_test_result(((1 << bit_number) & value), " Expected bit to be set" ,  __FUNCTION__, __LINE__); } while (0)
#define assert_bit_not_set(bit_number, value) { seatest_simple_test_result(!((1 << bit_number) & value), " Expected bit not to to be set" ,  __FUNCTION__, __LINE__); } while (0)
#define assert_bit_mask_matches(value, mask) { seatest_simple_test_result(((value & mask) == mask), " Expected all bits of mask to be set" ,  __FUNCTION__, __LINE__); } while (0)
#define assert_fail(message) { seatest_simple_test_result(0, message,  __FUNCTION__, __LINE__); } while (0)
#define assert_float_equal(expected, actual, delta) do {  seatest_assert_float_equal(expected, actual, delta, __FUNCTION__, __LINE__); } while (0)
#define assert_double_equal(expected, actual, delta) do {  seatest_assert_double_equal(expected, actual, delta, __FUNCTION__, __LINE__); } while (0)
#define assert_string_contains(expected, actual) do {  seatest_assert_string_contains(expected, actual, __FUNCTION__, __LINE__); } while (0)
#define assert_string_doesnt_contain(expected, actual) do {  seatest_assert_string_doesnt_contain(expected, actual, __FUNCTION__, __LINE__); } while (0)
#define assert_string_starts_with(expected, actual) do {  seatest_assert_string_starts_with(expected, actual, __FUNCTION__, __LINE__); } while (0)
#define assert_string_ends_with(expected, actual) do {  seatest_assert_string_ends_with(expected, actual, __FUNCTION__, __LINE__); } while (0)

/*
Fixture / Test Management
*/

void fixture_setup(void (*setup)( void ));
void fixture_teardown(void (*teardown)( void ));
#define run_test(test) do { if(seatest_should_run(__FILE__, #test)) {seatest_setup(); test(); seatest_teardown(); seatest_run_test(); }} while (0)
#define test_fixture_start() do { seatest_test_fixture_start(__FILE__); } while (0)
#define test_fixture_end() do { seatest_test_fixture_end();} while (0)
void fixture_filter(char* filter);
void test_filter(char* filter);

int run_tests(void (*tests)(void));
#endif 
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

	s->buffer = malloc(STACK_SIZE * item_length);
	s->top = 0;

	assert(s->buffer != NULL);

	s->item_length = item_length;

	return s;
}

void destroy_stack(stack_t* s)
{
	assert(s->buffer);
	assert(s);

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
	++s->top;
}

const void* stack_pop(stack_t* s1)
{
	assert(s1->top > 0);
	assert(s1);
	assert(s1->buffer);

	unsigned char* ptr = (unsigned char*)s1->buffer;
	s1->top--;
	ptr += s1->item_length * s1->top;
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


void tokenizer_test_fixture(void);
void parser_test_fixture(void);

void all_unit_tests(void)
{
	tokenizer_test_fixture();
	parser_test_fixture();
}

int main(int argc, char* argv[])
{
	run_tests(all_unit_tests);
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


void init_parser(parser_t* p, char* source)
{
	p->t = (tokenizer_t*)malloc(sizeof(tokenizer_t));
	init_tokenizer(p->t, source);
}

void release_parser(parser_t* p)
{
	release_tokenizer(p->t);
	free(p->t);
}

void parse(parser_t* p)
{
	
}


static void parser_test1()
{
	parser_t* p = (parser_t*)malloc(sizeof(parser_t));
	init_parser(p, "1 2 3 4 5");
	assert_int_equal(TT_NUMBER, get_token(p->t));
	assert_int_equal(TT_NUMBER, get_token(p->t));
	assert_int_equal(TT_NUMBER, get_token(p->t));
	assert_int_equal(TT_NUMBER, get_token(p->t));
	assert_int_equal(TT_NUMBER, get_token(p->t));
	assert_int_equal(TT_EOF, get_token(p->t));
	release_parser(p);
	free(p);
}

void parser_test_fixture(void)
{
	test_fixture_start();
	run_test(parser_test1);
	test_fixture_end();
}


#ifdef WIN32
#else
unsigned int GetTickCount() { return 0;}
#endif

static int sea_tests_run = 0;
static int sea_tests_passed = 0;
static int sea_tests_failed = 0;
static char* seatest_current_fixture;

static void (*seatest_fixture_setup)( void ) = 0;
static void (*seatest_fixture_teardown)( void ) = 0;

void fixture_setup(void (*setup)( void ))
{
	seatest_fixture_setup = setup;
}
void fixture_teardown(void (*teardown)( void ))
{
	seatest_fixture_teardown = teardown;
}

void seatest_setup()
{
	if(seatest_fixture_setup != 0) seatest_fixture_setup();
}

void seatest_teardown()
{
	if(seatest_fixture_teardown != 0) seatest_fixture_teardown();
}

char* test_file_name(char* path)
{
	char* file = path + strlen(path);
	while(file != path && *file!= '\\' ) file--;
	if(*file == '\\') file++;
	return file;
}

static int seatest_fixture_tests_run;
static int seatest_fixture_tests_failed;

void seatest_simple_test_result(int passed, char* reason, const char* function, unsigned int line)
{
	if (!passed)
	{
		printf("%-20s Line %-5d %s\r\n", function, line, reason );
		sea_tests_failed++; 
	}
	else
	{
		sea_tests_passed++; 
	}	
}

void seatest_assert_true(int test, const char* function, unsigned int line)
{
	seatest_simple_test_result(test, "Should of been true", function, line);

}

void seatest_assert_false(int test, const char* function, unsigned int line)
{
	seatest_simple_test_result(!test, "Should of been false", function, line);	
}


void seatest_assert_int_equal(int expected, int actual, const char* function, unsigned int line)
{
	char s[100];
	sprintf(s, "Expected %d but was %d", expected, actual);
	seatest_simple_test_result(expected==actual, s, function, line);	
}

void seatest_assert_float_equal( float expected, float actual, float delta, const char* function, unsigned int line )
{
	char s[100];
	float result = expected-actual;
	sprintf(s, "Expected %f but was %f", expected, actual);
	if(result < 0.0) result = 0.0 - result;
	seatest_simple_test_result( result <= delta, s, function, line);	
}

void seatest_assert_double_equal( double expected, double actual, double delta, const char* function, unsigned int line )
{
	char s[100];
	double result = expected-actual;
	sprintf(s, "Expected %f but was %f", expected, actual);
	if(result < 0.0) result = 0.0 - result;
	seatest_simple_test_result( result <= delta, s, function, line);	
}

void seatest_assert_string_equal(char* expected, char* actual, const char* function, unsigned int line)
{
	char s[100];
	sprintf(s, "Expected %s but was %s", expected, actual);
	seatest_simple_test_result(strcmp(expected, actual)==0, s, function, line);	
}

void seatest_assert_string_ends_with(char* expected, char* actual, const char* function, unsigned int line)
{
	char s[100];
	sprintf(s, "Expected %s to end with %s", actual, expected);
	seatest_simple_test_result(strcmp(expected, actual+(strlen(actual)-strlen(expected)))==0, s, function, line);	
}

void seatest_assert_string_starts_with(char* expected, char* actual, const char* function, unsigned int line)
{
	char s[100];
	sprintf(s, "Expected %s to start with %s", actual, expected);
	seatest_simple_test_result(strncmp(expected, actual, strlen(expected))==0, s, function, line);	
}

void seatest_assert_string_contains(char* expected, char* actual, const char* function, unsigned int line)
{
	char s[100];
	sprintf(s, "Expected %s to be in %s", expected, actual);
	seatest_simple_test_result(strstr(expected, actual)!=0, s, function, line);	
}

void seatest_assert_string_doesnt_contain(char* expected, char* actual, const char* function, unsigned int line)
{
	char s[100];
	sprintf(s, "Expected %s not to have %s in it", actual, expected);
	seatest_simple_test_result(strstr(expected, actual)==0, s, function, line);	
}

void seatest_run_test(void)
{
	sea_tests_run++; 
}

void seatest_header_printer(char* s, int length, char f)
{
	int l = strlen(s);
	int d = (length- (l + 2)) / 2;
	int i;
	for(i = 0; i<d; i++) printf("%c",f);
	printf(" %s ", s);
	for(i = (d+l+2); i<length; i++) printf("%c",f);
	printf("\r\n");
}


void seatest_test_fixture_start(char* filepath)
{
	seatest_current_fixture = test_file_name(filepath);
	seatest_header_printer(seatest_current_fixture, 50, '-');
	seatest_fixture_tests_failed = sea_tests_failed;
	seatest_fixture_tests_run = sea_tests_run;
	seatest_fixture_teardown = 0;
	seatest_fixture_setup = 0;
}

void seatest_test_fixture_end()
{
	char s[100];
	sprintf(s, "%d run  %d failed", sea_tests_run-seatest_fixture_tests_run, sea_tests_failed-seatest_fixture_tests_failed);
	seatest_header_printer(s, 50, ' ');
	printf("\r\n");
}

static char* seatest_fixture_filter = 0;
static char* seatest_test_filter = 0;

void fixture_filter(char* filter)
{
	seatest_fixture_filter = filter;
}


void test_filter(char* filter)
{
	seatest_test_filter = filter;
}


int seatest_should_run( char* fixture, char* test)
{
	int run = 1;
	if(seatest_fixture_filter) 
	{
		if(strncmp(seatest_fixture_filter, fixture, strlen(seatest_fixture_filter)) != 0) run = 0;
	}
	if(seatest_test_filter) 
	{
		if(strncmp(seatest_test_filter, test, strlen(seatest_test_filter)) != 0) run = 0;
	}
	return run;
}

int run_tests(void (*tests)(void))
{
	unsigned long end;
	unsigned long start = GetTickCount();
	tests();	 
	end = GetTickCount();
	printf("\r\n\r\n==================================================\r\n");	 
	if (sea_tests_failed > 0) {
		printf("                      Failed\r\n");			
	}
	else {
		printf("               ALL TESTS PASSED\r\n");
	}
	printf("                 %d tests run\r\n", sea_tests_run);
	printf("                    in %d ms\r\n",end - start);
	printf("==================================================\r\n");

	getchar();
	return sea_tests_failed == 0;
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

static int is_digit(char d)
{
	return ((d >= '0') && (d <= '9'));
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

	/*while (is_whitespace(t->source[t->source_index])) {
		if ('\n' == t->source[t->source_index]) {
			t->line_number++;
		}*/
		++t->source_index;
	//}
#if 0
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
		//goto eatwhitespace_begin;
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
		//goto eatwhitespace_begin;
	}
#endif
}


static void tokenize_number(tokenizer_t* t)
{
	/* t->token_type == TT_NUMBER; */
	t->token_value = malloc(sizeof(int));
	(*(int*)(t->token_value)) = t->source[t->source_index++] - '0';
	while (is_digit(t->source[t->source_index])) {
		(*(int*)(t->token_value)) *= 10;
		(*(int*)(t->token_value)) += t->source[t->source_index];
		(*(int*)(t->token_value)) -= '0';
	}
}

static void tokenize_identifier(tokenizer_t* t)
{
	int i = 0;

	t->token_value = (char*)malloc(MAX_IDENT_LENGTH);
	((char*)(t->token_value))[i++] = t->source[t->source_index++];
	while (is_alphanum( t->source[t->source_index])) {
		((char*)(t->token_value))[i++] = t->source[t->source_index++];
		if (i == MAX_IDENT_LENGTH) {
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
	++t->source_index;
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
				t->source_index = 2 + t->source_index;
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

