const int MAXL = 100001; // The length of the string being inserted into the ST.
const int MAXD = 27;     // The size of the alphabet.

struct SuffixTree{
	int size, length, pCur, dCur, lCur, lBuf, text[MAXL];
	std::pair<int, int> suffix[MAXL];
	
	struct Node{
		int left, right, sLink, next[MAXD];
	}tree[MAXL * 2];
	
	int getLength(const int &rhs) {
		return tree[rhs].right ? tree[rhs].right - tree[rhs].left : length + 1 - tree[rhs].left;
	}
	void addLink(int &last, int node) {
		if (last != 0) tree[last].sLink = node;
		last = node;
	}
	int alloc(int left, int right = 0) {
		size++;
		memset(&tree[size], 0, sizeof(tree[size]));
		tree[size].left = left;
		tree[size].right = right;
		tree[size].sLink = 1;
		return size;
	}
	bool move(int node) {
		int length = getLength(node);
		if (lCur >= length) {
			lCur -= length;
			dCur += length;
			pCur = node;
			return true;
		}
		return false;
	}
	void init() {
		size = length = 0;
		lCur = dCur = lBuf = 0;
		pCur = alloc(0);
	}
	void extend(int x) {
		text[++length] = x;
		lBuf++;
		for (int last = 0; lBuf > 0; ) {
			if (lCur == 0) dCur = length;
			if (!tree[pCur].next[text[dCur]]) {
				int newleaf = alloc(length);
				tree[pCur].next[text[dCur]] = newleaf;
				suffix[length + 1 - lBuf] = std::make_pair(pCur, newleaf);
				addLink(last, pCur);
			} else {
				int nownode = tree[pCur].next[text[dCur]];
				if (move(nownode)) continue;
				if (text[tree[nownode].left + lCur] == x) {
					lCur++;
					addLink(last, pCur);
					break;
				}
				int newleaf = alloc(length), newnode = alloc(tree[nownode].left, tree[nownode].left + lCur);
				tree[nownode].left += lCur;
				tree[pCur].next[text[dCur]] = newnode;
				tree[newnode].next[x] = newleaf;
				tree[newnode].next[text[tree[nownode].left]] = nownode;
				suffix[length + 1 - lBuf] = std::make_pair(newnode, newleaf);
				addLink(last, newnode);
			}
			lBuf--;
			if (pCur == 1 && lCur > 0) lCur--, dCur++;
			else pCur = tree[pCur].sLink;
		}
	}
};
