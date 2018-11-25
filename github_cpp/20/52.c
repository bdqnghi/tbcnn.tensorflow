#include "header.h"

int main()
{
	RB_trees *tree = NULL;
	int key, choose;
	char color;
	ifstream file("rb_tree.txt");

	while (!file.eof())
	{
		file >> color;
		file >> key;
		Add(tree, key, color);
	}

	Print(tree, 0);
	Menu(tree);

	Check_RB(tree, 0);//проверка на красночёрность
	result_check();//вывод результата проверки

	Coloring(tree, 0);//можно ли раскрасить
	result_coloring();//ответ, можно ли раскрасить

    return 0;
}

