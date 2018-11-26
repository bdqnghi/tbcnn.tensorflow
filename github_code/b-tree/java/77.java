package Lab7;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.Stack;
import java.util.StringTokenizer;

public class B {
	public static void main(String[] args) {
		InputStream inputStream = System.in;
		OutputStream outputStream = System.out;
		InputReader in = new InputReader(inputStream);
		PrintWriter out = new PrintWriter(outputStream);
		Task solver = new Task();
		solver.solve(in, out);
		out.close();
	}

	static class Task {

		public void solve(InputReader in, PrintWriter out) {
			int casenum = in.nextInt();
			for (int t = 1; t < casenum + 1; t++) {
				int n = in.nextInt();
				// build tree
				TreeNode[] BST = new TreeNode[n + 1];
				for (int i = 1; i < BST.length; i++) {
					BST[i] = new TreeNode(in.nextInt(), null, null);
				}
				boolean isBST = true;
				boolean[] isnotroot = new boolean[n + 1];
				for (int i = 1; i < n; i++) {
					int p = in.nextInt();
					int c = in.nextInt();
					isnotroot[c] = true;
					if (BST[c].value < BST[p].value) {
						if (BST[p].left == null) {
							BST[p].setLeft(BST[c]);
						} else {
							isBST = false;
						}
					} else if (BST[c].value > BST[p].value) {
						if (BST[p].right == null) {
							BST[p].setRight(BST[c]);
						} else {
							isBST = false;
						}
					} else {
						// no the same nodes
						isBST = false;
					}
				}
				// find root
				TreeNode root = null;
				for (int i = 1; i < isnotroot.length; i++) {
					if (!isnotroot[i]) {
						root = BST[i];
						break;
					}
				}

				// judge
				if (!isBST) {
					out.printf("Case #%d: NO\n", t);
					continue;
				}

				// in order
				if (isBST(root, BST)) {
					out.printf("Case #%d: YES\n", t);
				} else {
					out.printf("Case #%d: NO\n", t);
				}
			}
		}

		public boolean isBST(TreeNode root, TreeNode[] BST) {
			if (root == null) {
				return true;
			}
			Stack<TreeNode> stack = new Stack<>();
			TreeNode pre = null;
			while (root != null || !stack.isEmpty()) {
				while (root != null) {
					stack.push(root);
					root = root.left;
				}
				root = stack.pop();
				if (pre != null && root.value <= pre.value) {
					return false;
				}
				pre = root;
				root = root.right;
			}
			return true;
		}

		public class TreeNode {
			int value;
			TreeNode left;
			TreeNode right;

			public TreeNode(int value, TreeNode left, TreeNode right) {
				this.value = value;
				this.left = left;
				this.right = right;
			}

			public void setLeft(TreeNode left) {
				this.left = left;
			}

			public void setRight(TreeNode right) {
				this.right = right;
			}
		}
	}

	static class InputReader {
		public BufferedReader reader;
		public StringTokenizer tokenizer;

		public InputReader(InputStream stream) {
			reader = new BufferedReader(new InputStreamReader(stream), 32768);
			tokenizer = null;
		}

		public String next() {
			while (tokenizer == null || !tokenizer.hasMoreTokens()) {
				try {
					tokenizer = new StringTokenizer(reader.readLine());
				} catch (IOException e) {
					throw new RuntimeException(e);
				}
			}
			return tokenizer.nextToken();
		}

		public int nextInt() {
			return Integer.parseInt(next());
		}

		public long nextLong() {
			return Long.parseLong(next());
		}

		public double nextDouble() {
			return Double.parseDouble(next());
		}

		public char[] nextCharArray() {
			return next().toCharArray();
		}

		// public boolean hasNext() {
		// try {
		// return reader.ready();
		// } catch(IOException e) {
		// throw new RuntimeException(e);
		// }
		// }
		public boolean hasNext() {
			try {
				String string = reader.readLine();
				if (string == null) {
					return false;
				}
				tokenizer = new StringTokenizer(string);
				return tokenizer.hasMoreTokens();
			} catch (IOException e) {
				return false;
			}
		}

		public BigInteger nextBigInteger() {
			return new BigInteger(next());
		}

		public BigDecimal nextBigDecinal() {
			return new BigDecimal(next());
		}
	}
}