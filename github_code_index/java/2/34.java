public class AvlTree {

AvlNode position;

AvlNode avlTree;

public AvlNode makeEmpty(AvlNode t) {

if(t != null) {

makeEmpty(t.getLeft());

makeEmpty(t.getRight());

t = null;

}

return null;

}

public AvlNode find(int value, AvlNode t) {

if (t == null) {

return null;

}

if (value < t.getValue()) {

return find(value, t.getLeft());

}

else	 if(value > t.getValue()) {

return find(value, t.getRight());

}

else

return t;

}

public AvlNode findMin(AvlNode t) {

if (t == null) {

return null;

}

else 	 if(t.getLeft() == null)

return t;

else

return findMin(t.getLeft());

}

public AvlNode findMax(AvlNode t) {

if(t != null)

while(t.getRight() != null)

t = t.getRight();

return t;

}

public static int getHeight (AvlNode position) {

if (position == null)

return -1;

else

return position.getHeight();

}

public static int max (int lhs, int rhs) {

return lhs > rhs ? lhs : rhs;

}

public static AvlNode singleRotateWithLeft (AvlNode k2) {

AvlNode k1;

k1 = k2.getLeft();

k2.setLeft(k1.getRight());

k1.setRight(k2);

k2.setHeight(max(getHeight(k2.getLeft()),	 getHeight(k2.getRight()))+1);

k1.setHeight(max(getHeight(k1.getLeft()),k2.getHeight())+1);

return k1;

}

public static AvlNode singleRotateWithRight (AvlNode k1) {

AvlNode k2;

k2 = k1.getRight();

k1.setRight(k2.getLeft());

k2.setLeft(k1);

k1.setHeight(max(getHeight(k1.getLeft()),	 getHeight(k1.getRight()))+1);

k2.setHeight(max(getHeight(k2.getRight()),k1.getHeight())+1);

return k2;

}

public static AvlNode doubleRotateWithLeft (AvlNode k3) {

k3.setLeft(singleRotateWithRight(k3.getLeft()));

return singleRotateWithLeft(k3);

}

public static AvlNode doubleRotateWithRight (AvlNode k1) {

k1.setRight(singleRotateWithLeft(k1.getRight()));

return singleRotateWithRight(k1);

}

public AvlNode insert (int value, AvlNode t) {

if(t == null) {

t = new AvlNode(value);

}

else	 if(value < t.getValue()) {

t.setLeft(insert(value,t.getLeft()));

if(getHeight(t.getLeft())-getHeight(t.getRight()) == 2)

if(value < t.getLeft().getValue())

t = singleRotateWithLeft(t);

else

t = doubleRotateWithLeft(t);

}

else 	 if(value > t.getValue()) {

t.setRight(insert(value,t.getRight()));

if(getHeight(t.getRight())-getHeight(t.getLeft()) == 2)

if(value > t.getRight().getValue())

t = singleRotateWithRight(t);

else

t = doubleRotateWithRight(t);

}

t.setHeight(max(getHeight(t.getLeft()),	 getHeight(t.getRight()))+1);

return t;

}

public int retrieve (AvlNode t) {

return t.getValue();

}

public void preOrder(AvlNode t) {

System.out.println(t.getValue());

if(t.getLeft() != null) {

preOrder(t.getLeft());

}

if(t.getRight() != null) {

preOrder(t.getRight());

}

}

public static void main(String[] args) {

AvlTree at = new AvlTree();

AvlNode t;

AvlNode position;

int i;

int j = 0;

t = at.makeEmpty(null);

for(i=0; i<50; i++, j = (j+7)%50){

t = at.insert(j,t);
}

	for(i=0; i<50; i++){
	
		if((position = at.find(i,t)) == null ||	 at.retrieve(position) != i){
		
		System.out.println(�Error at �+i);
		}
		System.out.println(�Min is �+at.retrieve(at.findMin(t))+	 � Max is �+at.retrieve(at.findMax(t)));	 at.preOrder(t);
		
	}

}

}