#ifndef SP_UTIL_PROBLEM_TOWER_OF_HANOI_H
#define SP_UTIL_PROBLEM_TOWER_OF_HANOI_H

#include <stack/DynamicStack.h>

// https://bradfieldcs.com/algos/recursion/tower-of-hanoi/

/* # Tower of Hanoi
 * Rules:
 * 1. Only one disk can be moved at a time.
 * 2. Each move consists of taking the upper disk from one of the stacks and
 *    placing it on top of another stack i.e. a disk can only be moved if it is
 *    the uppermost disk on a stack.
 * 3. No disk may be placed on top of a smaller disk.
 *
 *      from            to
 *       |              |
 *     | 1 |            |
 *    |  2  |           |
 *   |   3   |          |
 * ------+--------------+---------
 */
namespace sp {
// [3, 2, 1]
void
tower_of_hanoi(DynamicStack<int> &from, DynamicStack<int> &to) noexcept;
}

#endif
