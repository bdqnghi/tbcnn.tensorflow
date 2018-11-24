/*
 * Copyright (C) 2017 Chris Tarazi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../include/stack.h"

void stackInitialize(Stack * const s)
{
	s->size = 0;
}

/**
 * Pop an element from the stack and return it.
 * @param s: the instance of the Stack.
 * @return:  return the popped element.
 */
ElemStack stackPop(Stack * const s)
{
	if (s->size == 0) {
		ElemStack elem = {"."};
		return elem;
	}

	ElemStack elem = s->element[s->size - 1];
	s->size--;

	return elem;
}

/**
 * Push an element to the stack.
 * @param s: the instance of the Stack.
 * @param el: the element to push to the stack.
 */
void stackPush(Stack * const s, ElemStack const el)
{
	if (s->size < MAX_STACK_SIZE) {
		s->element[s->size++] = el;
	}
}

/**
 * List the contents of the stack top to bottom.
 * @param s: the instance of the Stack.
 */
void stackList(Stack * const s)
{
	if (s->size > 0) {
		std::cout << "Top\n";
		for (int i = s->size - 1; i >= 0; --i)
			std::cout << "\t" << s->element[i].path << "\n";
		std::cout << "Bottom\n";
	}
}
