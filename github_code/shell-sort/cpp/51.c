#ifndef __OOMTKSYS_SHELLSORT_H__
#define __OOMTKSYS_SHELLSORT_H__
/*
 *  Copyright (C) 2008 by Filip Brcic <brcha@gna.org>
 *
 *  This file is part of OOMTK
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/** @file shellsort.h
 * @brief Shell-sort
 */

#include <cstddef>

/**
 * @brief Shell-sort the @p array of size @p length
 * 
 * Shell-sort is better (here) than quicksort as it doesn't use recursion and it is
 * generally faster for shorter arrays.
 * 
 * For more info on shell-sort take a look at any computer science book. My source of
 * reference is <em>Numerical Recipies in C++, 3rd edition, chapter 8.1.1</em>.
 * 
 * @note Implement operator > for the type
 */
template <typename T>
void shellsort(T * array, size_t length)
{
  int i, j, inc;
  T v;
  
  inc = 1;
  do
  {
    inc *= 3;
    inc ++;
  } while (inc <= length);
  
  do
  {
    inc /= 3;
    for (i = inc; i < length; i++)
    {
      v = array[i];
      j = i;
      while (array[j-inc] > v)
      {
	array[j] = array[j-inc];
	j -= inc;
	if (j < inc)
	  break;
      }
      array[j] = v;
    }
  } while (inc > 1);
}

#endif /* __OOMTKSYS_SHELLSORT_H__ */
