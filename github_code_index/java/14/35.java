//Generic binary Tree
class bnode{
	int value;
	bnode left, right;
	bnode(int val){
		this.value=val;
		this.left = null;
		this.right = null;
	}
}

public class bTree {
	bnode root=null;

	void add(int val){
		bnode newnode= new bnode(val);
		bnode curr = this.root;
		bnode parent = null;

		if(this.root == null){
			this.root = newnode;
			System.out.println("Inserted at root \t"+newnode.value);
		}
		else{
				System.out.println("Current Left and Right\t"+curr.left+"\t"+curr.right);

				if(curr.left == null){
					curr.left = newnode;
					System.out.println("Inserted Left\t" +newnode.value);
					return;
				}
				if(curr.right ==  null){
					curr.right = newnode;
					System.out.println("Inserted Right\t" +newnode.value);
					return;
				}
			}
	}
	
	void preOrder(bnode root){
		if(root != null){
			System.out.println(root.value);
			preOrder(root.left);
			preOrder(root.right);
		}
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		bTree b = new bTree();
		b.add(5);
		b.add(6);
		b.add(7);
		b.add(20);
		b.add(21);
		b.preOrder(b.root);
	}

}
