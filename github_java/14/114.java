// Introduced in Chapter 17
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

/** BTree storing many ints on disk. */
public class BTree implements Serializable {

	/** Directory where files are stored. */
	public static final String DIR = "data/";

	static {
		new File(DIR).mkdirs();
	}

	/** Id number of the root node. */
	private int rootId;

	/** A new BTree is initially empty. */
	public BTree() {
		BTreeNode root = new BTreeNode(true);
		this.rootId = root.getId();
		root.writeToDisk();
		this.writeToDisk();
	}

	/**
	 * Add target to this BTree and write any modified nodes to disk.
	 * 
	 * @param target
	 */
	public void add(int target) {
		BTreeNode root = BTreeNode.readFromDisk(this.rootId);
		if (root.isFull()) {
			BTreeNode parent = new BTreeNode(root);
			this.rootId = parent.getId();
			this.writeToDisk();
			parent.add(target);
		} else {
			root.add(target);
		}
	}

	/**
	 * Return true if this BTree contains target.
	 * 
	 * @param target
	 * @return contem
	 */
	public boolean contains(int target) {
		BTreeNode node = BTreeNode.readFromDisk(this.rootId);
		while (node != null) {
			double d = node.indexOf(target);
			int i = (int) d;
			if (i == d) {
				return true;
			} else {
				node = node.getChild(i);
			}
		}
		return false;
	}

	/**
	 * Read a previously saved BTree from disk.
	 * 
	 * @return this
	 */
	public static BTree readFromDisk() {
		try {
			ObjectInputStream in = new ObjectInputStream(new FileInputStream(
					DIR + "btree"));
			try {
				return (BTree) (in.readObject());
			} finally {
				in.close();
			}
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(1);
			return null;
		}
	}

	/**
	 * Remove target from this BTree.
	 * 
	 * @param target
	 */
	public void remove(int target) {
		BTreeNode root = BTreeNode.readFromDisk(rootId);
		root.remove(target);
		if ((root.size() == 1) && (!(root.isLeaf()))) {
			BTreeNode child = root.getChild(0);
			root.deleteFromDisk();
			rootId = child.getId();
			writeToDisk();
		}
	}

	/** Write this BTree to disk. */
	public void writeToDisk() {
		try {
			ObjectOutputStream out = new ObjectOutputStream(
					new FileOutputStream(DIR + "btree"));
			out.writeObject(this);
			out.close();
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(1);
		}
	}

}