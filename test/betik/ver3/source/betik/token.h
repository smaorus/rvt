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

#include "common.h"

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

#endif // token_h

