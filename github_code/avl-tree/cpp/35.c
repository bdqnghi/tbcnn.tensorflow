struct node // структура для представления узлов дерева
{
	int key;
	int value;
	unsigned char height;
	node * left;
	node * right;
	node(int k, int v) { key = k; value = v; left = right = 0; height = 1; }
};

typedef node * AVL;

unsigned char height(AVL p)
{
	return p ? p->height : 0;
}

int bfactor(AVL p)
{
	return height(p->right) - height(p->left);
}

void fixheight(AVL p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr ? hl : hr) + 1;
}

AVL rotateright(AVL p) // правый поворот вокруг p
{
	AVL q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

AVL rotateleft(AVL q) // левый поворот вокруг q
{
	AVL p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

AVL balance(AVL p) // балансировка узла p
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

AVL insert(AVL p, int k, int v) // вставка ключа k в дерево с корнем p
{
	if (!p) return new node(k, v);
	if (k<p->key)
		p->left = insert(p->left, k, v);
	else
		p->right = insert(p->right, k, v);
	return balance(p);
}

AVL findmin(AVL p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left ? findmin(p->left) : p;
}

AVL removemin(AVL p) // удаление узла с минимальным ключом из дерева p
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

AVL remove(AVL p, int k) // удаление ключа k из дерева p
{
	if (!p) return 0;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else //  k == p->key 
	{
		AVL q = p->left;
		AVL r = p->right;
		delete p;
		if (!r) return q;
		AVL min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

AVL finda(AVL p, int k, AVL last) // ищет ближайший элемент с меньшим ключом
{
	if (!p) return last;
	if (k > p->key)
	{
		last = p;
		return finda(p->right, k, last);
	}
	else
		return finda(p->left, k, last);
}

AVL finde(AVL p, int k) // ищет элемент с ключом k
{
	if (!p) return 0;
	if (k > p->key)
		return finde(p->right, k);
	else if (k < p->key)
		return finde(p->left, k);
	else
		return p;
}