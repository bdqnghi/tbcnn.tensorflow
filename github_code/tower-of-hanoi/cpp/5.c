#include "towerofhanoi.h"

TowerOfHanoi::TowerOfHanoi(int n)
    : n_Disk(n), n_Moves(0)
{
    if (n < 3 || n > 7)
        throw static_cast<std::string>("Error");
    for (int i = 0; i < n; ++i)
        tower[0].push(n - i);
}

bool TowerOfHanoi::moveDisk(int i, int j)
{
    if (i < 0 || i > 2 || j < 0 || j > 2 || i == j || tower[i].is_Empty())
        return false;
    if (tower[j].is_Empty() || tower[i].get_Top() < tower[j].get_Top())
    {
        tower[j].push(tower[i].pop());
        n_Moves++;
        undo_Stack.push(j * 10 + i);
        redo_Stack.clear();
        return true;
    }
    return false;
}

void TowerOfHanoi::undo()
{
    if(!undo_Stack.is_Empty())
    {
        char tmp = undo_Stack.pop();
        int i = tmp / 10;
        int j = tmp % 10;
        --n_Moves;
        tower[j].push(tower[i].pop());
        redo_Stack.push(j * 10 + i);
    }
}

void TowerOfHanoi::redo()
{
    if (!redo_Stack.is_Empty())
    {
        char tmp = redo_Stack.pop();
        int i = tmp / 10;
        int j = tmp % 10;
        ++n_Moves;
        tower[j].push(tower[i].pop());
        undo_Stack.push(j * 10 + i);
    }
}


char* TowerOfHanoi::getTower(int i, char *v)
{

    if (!tower[i].is_Empty())
    {
        char tmp = tower[i].pop();
        *v = tmp;
        getTower(i, v + 1);
        tower[i].push(tmp);
    }
    return v;
}

char* TowerOfHanoi::getTower(int i, int &n)
{
    if (i < 0 || i > 3 )
        return 0;
    n = tower[i].size();
    return getTower(i, new char[n]);
}
