package jobs.toolkit.alg.tree;

import jobs.toolkit.alg.tree.RedBlackTreeNode.Color;

public class RedBlackTree<V> extends BaseTree<RedBlackTreeNode, RedBlackTree<V>>{


	public RedBlackTree() {
		this.root = RedBlackTreeNode.NIL;
	}
	/**
	 * 对节点x进行左旋操作
	 * 左旋操作目标点x必须是右孩子不为NIL节点的任意节点, 
	 * 旋转的目标是, 让x的右孩子节点y成为新的子树根节点,
	 * 而x成为y的左孩子, y的左孩子成为x的右孩子
	 * @param x
	 */
	void leftRotate(RedBlackTreeNode x){
		//获取x的右孩子并标记为y
		RedBlackTreeNode y = x.right();
		//让y的左孩子成为x的右孩子
		x.setRightChild(y.left());
		//如果y左孩子不是NIL则y的左孩子的parent指向x
		if (y.left() != RedBlackTreeNode.NIL) y.left().setParent(x);
		//y的parent指向x的parent, y成为子树根节点
		y.setParent(x.parent());
		//如果原来的子树根节点x的parent为NIL, 证明x为树根, 
		//而此时y已经成为新的子树节点, y也应该成为新的树根.
		if (x.parent() == RedBlackTreeNode.NIL) this.root = y;
		//如果x是parent的左孩子, 则新的子树根y也应该是左孩子
		else if (x == x.parent().left()) x.parent().setLeftChild(y);
		//如果x是parent的右孩子, 则新的子树根y也应该是右孩子
		else x.parent().setRightChild(y);
		//x成为y的左孩子
		y.setLeftChild(x);
		//x的parent指向y
		x.setParent(y);
	}
	/**
	 * 对节点y进行右旋操作, 实际是leftRotabe的逆操作
	 * 右旋操作的目标点y必须是左孩子不为NIL节点的任意节点,
	 * 旋转的目的是: 让y的左孩子x成为新的子树根节点, 而y成为x的右孩子, 
	 * x的右孩子成为y的左孩子
	 * @param y
	 */
	void rightRotate(RedBlackTreeNode y){
		//获取y的左孩子并标记为x
		RedBlackTreeNode x = y.left();
		//让x的右孩子成为y的左孩子
		y.setLeftChild(x.right());
		//如果x的右孩子不是NIL节点, 则x的右孩子的parent应该指向y
		if (x.right() != RedBlackTreeNode.NIL) x.right().setParent(y);
		//x的parent应该指向y的parent, x成为新的子树根节点
		x.setParent(y.parent());
		//如果y的parent是NIL, 证明y是树根, 则x应该也是新的树根
		if (y.parent() == RedBlackTreeNode.NIL) this.root = x;
		//如果y不是树根, y是其parent的左孩子, 则x成为其parent的左孩子
		else if (y == y.parent().left()) y.parent().setLeftChild(x);
		//如果y是其parent的右孩子, 则x成为其parent的右孩子
		else y.parent().setRightChild(x);
		//y成为x的右孩子
		x.setRightChild(y);
		//y的parent指向x
		y.setParent(x);
	}
	/**
	 * 使用节点v替换u节点
	 * @param u
	 * @param v
	 */
	void transplant(RedBlackTreeNode u, RedBlackTreeNode v){
		if(u.parent() == RedBlackTreeNode.NIL) this.root = v;
		else if(u == u.parent().left()) u.parent().setLeftChild(v);
		else u.parent().setRightChild(v);
		v.setParent(u.parent());
	}
	/**
	 * 寻找以x为根节点的子树中代表最小值得节点
	 * @param z
	 */
	RedBlackTreeNode mininum(RedBlackTreeNode x){
		while (x.left() != RedBlackTreeNode.NIL) {
			x = x.left();
		}
		return x;
	}
	@Override
	public RedBlackTree<V> delete(RedBlackTreeNode z){
		/* 从红黑树中删除节点, 删除后需要使用z的子树节点来填充z的位置, 因此有四种情况
		 * 1.z的左孩子为空, 此时只需用z的右孩子替换z
		 * 2.z的右孩子为空, 此时只需用z的左孩子替换z
		 * 3.z的左右孩子均不为空, 并且z后继节点y是z的右孩子, 此时用y替换z
		 * 4.z的左右孩子均不为空, 并且z后继节点y不是z的直接子节点, 使用y的右孩子替换y原来的位置, 使用y替换到z的位置 */
		RedBlackTreeNode y = z;
		RedBlackTreeNode x = RedBlackTreeNode.NIL;
		Color backup = y.isBlack() ? Color.Black : Color.Red;
		//case one
		if(z.left() == RedBlackTreeNode.NIL){
			x = z.right();
			transplant(z, z.right());
		}else if(z.right() == RedBlackTreeNode.NIL){
			x = z.left();
			transplant(z, z.left());
		}else{
			//找到z的(中序遍历)后继节点
			y = this.mininum(z.right());
			backup = y.isBlack() ? Color.Black : Color.Red;
			x = y.right();
			if(y.parent() == z) x.setParent(y);
			else{
				transplant(y, y.right());
				y.setRightChild(z.right());
				y.right().setParent(y);
			}
			transplant(z, y);
			y.setLeftChild(z.left());
			y.left().setParent(y);
			if(z.isBlack()) y.switchToBlack(); else y.switchToRed();
		}
		return this;
	}

	@Override
	public RedBlackTree<V> insert(RedBlackTreeNode z) {
		RedBlackTreeNode x = this.root;
		RedBlackTreeNode y = RedBlackTreeNode.NIL;

		while (x != RedBlackTreeNode.NIL) {
			y = x;
			if(z.key().compareTo(x.key())< 0) x = x.left();
			else x = x.right();
		}
		z.setParent(y);
		if (y == RedBlackTreeNode.NIL) this.root = z;
		else if (z.key().compareTo(y.key()) < 0) y.setLeftChild(z);
		else y.setRightChild(z);
		z.setLeftChild(RedBlackTreeNode.NIL);
		z.setRightChild(RedBlackTreeNode.NIL);
		z.switchToRed();
		return this.fixup(z);
	}
	/**
	 * 调整红黑树
	 * 由于新插入节点z是红色的, 且z的两个孩子节点均为为NIL节点, 因此如果z节点的插入破坏了红黑树, 则有两种可能, 可能也只可能破坏红黑树的性质2, 4
	 * 1.如果树为空树, z是第一个插入的节点, 则破坏性质2
	 * 2.如果树不为空, 并且z的父节点为红色, 则破坏性质4
	 * 根据这两种情况, 则可以确定加入z的父节点为红色, 则必然破坏了红黑树性质, 或者破坏性质2、或者破坏性质4
	 * 通过循环调整, 一旦z的父节点为黑色了, 则此时证明, 性质4不会被破坏, 性质2有可能破坏, 只需在最后将树根的颜色置为黑色即可
	 * @param z
	 * @return
	 */
	RedBlackTree<V> fixup(RedBlackTreeNode z){
		while (z.parent().isRed()) {
			if (z.parent() == z.parent().parent().left()) {
				z = fixupLeft(z);
			}else{
				z = fixupRight(z);
			}
		}
		this.root.switchToBlack();
		return this;
	}
	RedBlackTreeNode fixupLeft(RedBlackTreeNode z){
		if (z.parent().parent().right().isRed()) {
			return caseOneLeft(z);
		} else {
			if (z == z.parent().right()) {
				z = caseTwoLeft(z);
			}
			return caseThreeLeft(z);
		}
	}
	RedBlackTreeNode fixupRight(RedBlackTreeNode z){
		if (z.parent().parent().left().isRed()) {
			return caseOneRight(z);
		} else {
			if (z == z.parent().left()) {
				z = caseTwoRight(z);
			}
			return caseThreeRight(z);
		}
	}
	/**
	 * case 1:如果z节点的叔叔节点为红色, 则进入情况1, 如果为黑色, 则转向情况2和情况3
	 * 对于情况1, 可以确定z、z的父节点以及z的叔叔节点为红色的, 而z的祖父节点为黑色, 此时破坏红黑树性质4(红节点不能有红孩子), 可以通过修改节点的颜色来调整红黑树
	 * 修改z的父节点为黑色, 来修正被z与z父节点均为红色破坏的性质4; 同时修改z的祖父节点为红色, z的叔叔节点为黑色来保证性质5和性质
	 * 通过这种方式可以在不破坏性质5的前提下先调整局部(但是有可能还是破坏着性质4或2), 然后让z指针指向其祖父节点, 通过循环继续考察
	 * @param z
	 * @return 新的z指针
	 */
	RedBlackTreeNode caseOneLeft(RedBlackTreeNode z){
		z.parent().switchToBlack();
		z.parent().parent().right().switchToBlack();
		z.parent().parent().switchToRed();
		return z.parent().parent();
	}
	/**
	 * case 2:如果z节点的叔叔节点为黑色, 并且z是其父节点的右孩子, 则进入情况2
	 * 对于情况2, 可以确定z和z的父节点为红色, 此时可以通过以z的父节点为轴进行左旋, 同时让z指向z的父节点, 使情况2转化为情况3  
	 * @param z
	 * @return
	 */
	RedBlackTreeNode caseTwoLeft(RedBlackTreeNode z){
		z = z.parent();
		leftRotate(z);
		return z;
	}
	/**
	 * case 3:如果z节点的叔叔节点为黑色, 并且z是其父节点的左孩子, 则进入情况3
	 * 对于情况3, 可以确定z、z父为红色, z的叔节点以及z的祖父节点为黑色, 性质4被破坏, 可以通过修改z父为黑色, z祖父为红色, 这样就可以在局部保证性质4和性质5
	 * 但由于z的祖父被修改为红色, 则有可能在z祖父的上面破坏红黑树性质, 则需要以z的祖父节点为轴进行一次右旋调整
	 * 在右旋操作中, z的祖父节点下移, z的父节点上移, z的原祖父节点成为z的兄弟节点, 由于z的父节点修改为黑色, 而z的原祖父节点成为z的兄弟, 则可以保证红黑树性质4不被破坏
	 * 此时表明红黑树调整完毕, 无需再次迭代了
	 * @param z
	 * @return
	 */
	RedBlackTreeNode caseThreeLeft(RedBlackTreeNode z){
		z.parent().switchToBlack();
		z.parent().parent().switchToRed();
		rightRotate(z.parent().parent());
		return z;
	}

	RedBlackTreeNode caseOneRight(RedBlackTreeNode z){
		z.parent().switchToBlack();
		z.parent().parent().left().switchToBlack();
		z.parent().parent().switchToRed();
		return z.parent().parent();
	}
	RedBlackTreeNode caseTwoRight(RedBlackTreeNode z){
		z = z.parent();
		rightRotate(z);
		return z;
	}
	RedBlackTreeNode caseThreeRight(RedBlackTreeNode z){
		z.parent().switchToBlack();
		z.parent().parent().switchToRed();
		leftRotate(z.parent().parent());
		return z;
	}
}
