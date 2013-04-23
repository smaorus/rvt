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

