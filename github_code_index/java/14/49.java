import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class BTree<E> {

  protected int sequence = 1;

  private final String name;

  private final int order;

  private BTreeNode<E> root;

  public BTree(String name, int order) throws IOException {
    this.name = name;
    this.order = order;
    File file = new File(name + ".db");
    if (file.exists()) {
      DataInputStream in = new DataInputStream(new FileInputStream(file));
      try {
        sequence = in.readInt();
        int rootId = in.readInt();
        order = in.readInt();
        this.root = read(rootId);
      }
      finally {
        in.close();
      }
    }
    else {
      this.root = new BTreeNode<E>(sequence++, order);
      this.root.write(name);
      this.write();
    }
  }

  public E get(int key) throws IOException {
    return get(root, key);
  }

  public boolean has(int key) throws IOException {
    return get(root, key) != null;
  }

  protected E get(BTreeNode<E> x, int k) throws IOException {
    int i = 0;
    while (i < x.length && k > x.keys[i]) {
      i++;
    }
    if (i < x.length && k == x.keys[i]) {
      return x.values[i];
    }
    if (x.leaf) {
      return null;
    }
    BTreeNode<E> child = x.read(i, name, order);
    return get(child, k);
  }

  protected void splitChild(BTreeNode<E> x, int i, BTreeNode<E> y)
    throws IOException {
    BTreeNode<E> z = new BTreeNode<E>(sequence++, order);
    z.leaf = y.leaf;
    z.length = order - 1;
    for (int j = 0; j < order - 1; j++) {
      z.keys[j] = y.keys[j + order];
      z.values[j] = y.values[j + order];
    }
    if (!y.leaf) {
      for (int j = 0; j < order; j++) {
        z.childrenId[j] = y.childrenId[j + order];
        z.childrenNode[j] = y.childrenNode[j + order];
      }
    }
    y.length = order - 1;
    for (int j = x.length; j > i + 1; i--) {
      x.childrenId[j + 1] = x.childrenId[j];
      x.childrenNode[j + 1] = x.childrenNode[j];
    }
    x.childrenId[i + 1] = z.id;
    x.childrenNode[i + 1] = z;
    for (int j = x.length - 1; j > i; i--) {
      x.keys[j + 1] = x.keys[j];
      x.values[j + 1] = x.values[j];
    }
    x.keys[i] = y.keys[order - 1];
    x.values[i] = y.values[order - 1];
    x.length++;
    y.write(name);
    z.write(name);
    x.write(name);
  }

  public void put(int key, E value) throws IOException {
    if (!put(root, key, value)) {
      add(key, value);
    }
  }

  protected boolean put(BTreeNode<E> x, int k, E value) throws IOException {
    int i = 0;
    while (i < x.length && k > x.keys[i]) {
      i++;
    }
    if (i < x.length && k == x.keys[i]) {
      x.values[i] = value;
      return true;
    }
    if (x.leaf) {
      return false;
    }
    BTreeNode<E> child = x.read(i, name, order);
    return put(child, k, value);
  }

  public void add(int key, E value) throws IOException {
    BTreeNode<E> r = root;
    if (r.length == 2 * order - 1) {
      BTreeNode<E> s = new BTreeNode<E>(sequence++, order);
      root = s;
      s.leaf = false;
      s.length = 0;
      s.childrenId[0] = r.id;
      s.childrenNode[0] = r;
      splitChild(s, 0, r);
      addNonfull(s, key, value);
    }
    else {
      addNonfull(r, key, value);
    }
    this.write();
  }

  protected void addNonfull(BTreeNode<E> x, int key, E value)
    throws IOException {
    int i = x.length - 1;
    if (x.leaf) {
      while (i >= 0 && key < x.keys[i]) {
        x.keys[i + 1] = x.keys[i];
        x.values[i + 1] = x.values[i];
        i--;
      }
      x.keys[i + 1] = key;
      x.values[i + 1] = value;
      x.length++;
      x.write(name);
    }
    else {
      while (i >= 0 && key < x.keys[i]) {
        i--;
      }
      i++;
      BTreeNode<E> y = x.read(i, name, order);
      if (y.length == 2 * order - 1) {
        splitChild(x, i, y);
        if (key > x.keys[i]) {
          i++;
          y = x.read(i, name, order);
        }
      }
      addNonfull(y, key, value);
    }
  }

  protected BTreeNode<E> read(int id) throws IOException {
    DataInputStream in =
      new DataInputStream(new FileInputStream(name + "." + id + ".db"));
    try {
      BTreeNode<E> node = new BTreeNode<E>(id, order);
      node.leaf = in.readBoolean();
      node.length = in.readInt();
      for (int n = 0; n < node.length; n++) {
        node.keys[n] = in.readInt();
        node.values[n] = (E) in.readUTF();
      }
      for (int n = 0; n < node.length + 1; n++) {
        node.childrenId[n] = in.readInt();
      }
      return node;
    }
    finally {
      in.close();
    }
  }

  public void write() throws IOException {
    DataOutputStream out =
      new DataOutputStream(new FileOutputStream(name + ".db"));
    try {
      out.writeInt(sequence);
      out.writeInt(root.id);
      out.writeInt(order);
    }
    finally {
      out.close();
    }
  }

  public static class BTreeNode<E> {

    private final int id;

    public int[] keys;

    public E[] values;

    public int[] childrenId;

    public BTreeNode<E>[] childrenNode;

    public int length;

    public boolean leaf;

    public BTreeNode(int id, int order) {
      this.id = id;
      this.leaf = true;
      this.keys = new int[2 * order];
      this.values = (E[]) new Object[2 * order];
      this.childrenId = new int[2 * order + 1];
      this.childrenNode = new BTreeNode[2 * order + 1];
    }

    protected BTreeNode<E> read(int i, String name, int order)
      throws IOException {
      BTreeNode<E> node = childrenNode[i];
      if (node != null) {
        return node;
      }
      int id = childrenId[i];
      DataInputStream in =
        new DataInputStream(new FileInputStream(name + "." + id + ".db"));
      try {
        node = new BTreeNode<E>(id, order);
        node.leaf = in.readBoolean();
        node.length = in.readInt();
        for (int n = 0; n < node.length; n++) {
          node.keys[n] = in.readInt();
          node.values[n] = (E) in.readUTF();
        }
        for (int n = 0; n < node.length + 1; n++) {
          node.childrenId[n] = in.readInt();
        }
      }
      finally {
        in.close();
      }
      childrenNode[i] = node;
      return node;
    }

    public void write(String name) throws IOException {
      DataOutputStream out =
        new DataOutputStream(new FileOutputStream(name + "." + id + ".db"));
      try {
        out.writeBoolean(leaf);
        out.writeInt(length);
        for (int n = 0; n < length; n++) {
          out.writeInt(keys[n]);
          out.writeUTF(values[n].toString());
        }
        for (int n = 0; n < length + 1; n++) {
          out.writeInt(childrenId[n]);
        }
      }
      finally {
        out.close();
      }
    }
  }

  public static void main(String[] args) throws IOException {
    BTree<String> tree = new BTree<String>("test", 2);
    tree.get(44);
    tree.get(33);
    tree.get(55);
    tree.get(66);
    tree.get(50);
    tree.get(57);
    tree.put(44, "44");
    tree.put(33, "33");
    tree.put(55, "55");
    tree.put(66, "66");
    tree.put(50, "50");
    tree.put(57, "57");
  }

}
