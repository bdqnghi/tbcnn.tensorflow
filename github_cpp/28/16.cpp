struct Tree
{

	int cnt = 1, rt = 0;

	int key, size, fa, son[2];
	void set(int _key, int _size, int _fa)
	{
		key = _key;
		size = _size;
		fa = _fa;
		son[0] = son[1] = 0;
	}
}T[MAXN];

inline void PushUp(int x)
{
	T[x].size = T[T[x].son[0]].size + T[T[x].son[1]].size + 1;
}

inline void Rotate(int x, int p) //0左旋 1右旋
{
	int y = T[x].fa;
	T[y].son[!p] = T[x].son[p];
	T[T[x].son[p]].fa = y;
	T[x].fa = T[y].fa;
	if (T[x].fa)
		T[T[x].fa].son[T[T[x].fa].son[1] == y] = x;
	T[x].son[p] = y;
	T[y].fa = x;
	PushUp(y);
	PushUp(x);
}

void Splay(int x, int To) //将x节点插入到To的子节点中
{
	while (T[x].fa != To)
	{
		if (T[T[x].fa].fa == To)
			Rotate(x, T[T[x].fa].son[0] == x);
		else
		{
			int y = T[x].fa, z = T[y].fa;
			int p = (T[z].son[0] == y);
			if (T[y].son[p] == x)
				Rotate(x, !p), Rotate(x, p); //之字旋
			else
				Rotate(y, p), Rotate(x, p); //一字旋
		}
	}
	if (To == 0) rt = x;
}

int find(int key) //返回值为key的节点 若无返回0 若有将其转移到根处
{
	int x = rt;
	while (x && T[x].key != key)
		x = T[x].son[key > T[x].key];
	if (x) Splay(x, 0);
	return x;
}

int prev() //返回比根值小的最大值 若无返回0 若有将其转移到根处
{
	int x = T[rt].son[0];
	if (!x) return 0;
	while (T[x].son[1])
		x = T[x].son[1];
	Splay(x, 0);
	return x;
}

int succ() //返回比根值大的最小值 若无返回0 若有将其转移到根处
{
	int x = T[rt].son[1];
	if (!x) return 0;
	while (T[x].son[0])
		x = T[x].son[0];
	Splay(x, 0);
	return x;
}

void Insert(int key) //插入key 并且将该节点转移到根处
{
	if (!rt)
		T[rt = cnt++].set(key, 1, 0);
	else
	{
		int x = rt, y = 0;
		while (x)
		{
			y = x;
			x = T[x].son[key > T[x].key];
		}
		T[x = cnt++].set(key, 1, y);
		T[y].son[key > T[y].key] = x;
		Splay(x, 0);
	}
}

void Delete(int key) //删除值为key的节点 若有重点只删其中一个 x的前驱移动到根处
{
	int x = find(key);
	if (!x) return;
	int y = T[x].son[0];
	while (T[y].son[1])
		y = T[y].son[1];
	int z = T[x].son[1];
	while (T[z].son[0])
		z = T[z].son[0];
	if (!y && !z)
	{
		rt = 0;
		return;
	}
	if (!y)
	{
		Splay(z, 0);
		T[z].son[0] = 0;
		PushUp(z);
		return;
	}
	if (!z)
	{
		Splay(y, 0);
		T[y].son[1] = 0;
		PushUp(y);
		return;
	}
	Splay(y, 0);
	Splay(z, y);
	T[z].son[0] = 0;
	PushUp(z);
	PushUp(y);
}

int GetPth(int p) //获得第p小的节点 并将其转移到根处
{
	if (!rt) return 0;
	int x = rt, ret = 0;
	while (x)
	{
		if (p == T[T[x].son[0]].size + 1)
			break;
		if (p > T[T[x].son[0]].size + 1)
		{
			p -= T[T[x].son[0]].size + 1;
			x = T[x].son[1];
		}
		else
			x = T[x].son[0];
	}
	Splay(x, 0);
	return x;
}

int GetRank(int key) //获得值<=key的节点个数 并将其转移到根处 若<key只需将<=换为<
{
	if (!rt) return 0;
	int x = rt, ret = 0, y;
	while (x)
	{
		y = x;
		if (T[x].key <= key)
		{
			ret += T[T[x].son[0]].size + 1;
			x = T[x].son[1];
		}
		else
			x = T[x].son[0];
	}
	Splay(y, 0);
	return ret;
}

