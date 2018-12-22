package jitd;

public class SplayBST {
	public static int inorderNodeIndex = 0;

	/***************************************************************************
	 * Splay tree function.
	 * **********************************************************************/
	public static Cog splayTheCog(Cog h,long key) {

		if (h == null) return null;
		if (h instanceof BTreeCog) {
			BTreeCog root = (BTreeCog)h;
			//System.out.println("current root of BTreeCog : " + root.sep + " against key : " + key );
			int cmp1 = Long.compare(key, root.sep);
			if (cmp1 < 0) {
				// reached leaves in tree, so we're done
				if (root.lhs == null || !(root.lhs instanceof BTreeCog)) {
					return root;
				} else {
					BTreeCog left = (BTreeCog) root.lhs;
					int cmp2 = Long.compare(key, left.sep);
					if (cmp2 < 0) {
						left.lhs = splayTheCog(left.lhs, key);
						h = rotateTheCogToRight(h);
					} else if (cmp2 > 0) {
						left.rhs = splayTheCog(left.rhs, key);
						if (left.rhs != null)
							((BTreeCog)h).lhs = rotateTheCogToLeft(left);
					}

					if (((BTreeCog)h).lhs == null) return h;
					else                return rotateTheCogToRight(h);
				}
			}

			else if (cmp1 > 0) { 
				// reached leaves in tree, so we're done
				if (root.rhs == null || !(root.rhs instanceof BTreeCog)) {
					return root;
				} else {
					BTreeCog right = (BTreeCog) root.rhs;
					int cmp2 = Long.compare(key, right.sep);
					if (cmp2 < 0) {
						right.lhs  = splayTheCog(right.lhs, key);
						if (right.lhs != null)
							((BTreeCog)h).rhs = rotateTheCogToRight(right);
					} else if (cmp2 > 0) {
						right.rhs = splayTheCog(right.rhs, key);
						h = rotateTheCogToLeft(h);
					}

					if (((BTreeCog)h).rhs == null) return h;
					else                 return rotateTheCogToLeft(h);
				}
			}
		}
		return h;
	}

	// right rotate the cog
	private static Cog rotateTheCogToRight(Cog h) {
		if (h instanceof BTreeCog && ((BTreeCog) h).lhs instanceof BTreeCog)  {
			BTreeCog root = (BTreeCog)h;	
			BTreeCog left = (BTreeCog)root.lhs;
			root.lhs = left.rhs;
			left.rhs = root;
			return left;
		}
		return h;
	}


	// left rotate the cog
	private static Cog rotateTheCogToLeft(Cog h) {
		if (h instanceof BTreeCog && ((BTreeCog) h).rhs instanceof BTreeCog) {
			BTreeCog root = (BTreeCog)h;	
			BTreeCog right = (BTreeCog)root.rhs;
			root.rhs = right.lhs;
			right.lhs = root;
			return right;
		}
		return h;
	}

	public static void print(String prefix, boolean isTail, Cog cog) {
		if (cog != null) {
			if (cog instanceof BTreeCog) {
				System.out.println(prefix + (isTail ? "└── " : "├── ") + ((BTreeCog)cog).sep);

				print(prefix + (isTail ? "    " : "│   "), false, ((BTreeCog)cog).lhs);
				print(prefix + (isTail ? "    " : "│   "), false, ((BTreeCog)cog).rhs);
			} else {
				System.out.println(prefix + (isTail ? "└── " : "├── ") + cog.toString());
			}			
		}
	}

	public static int getDepth(Cog cog) {
		int depth = 0;
		if (cog != null) {
			depth = 1;
			if (cog instanceof BTreeCog) {
				depth = depth + Math.max(getDepth(((BTreeCog)cog).lhs),
						getDepth(((BTreeCog)cog).rhs));
			}
		}
		return depth;
	}

	public static int getBTreeNodesCount(Cog cog) {
		if (cog != null && cog instanceof BTreeCog) {
			return getBTreeNodesCount(((BTreeCog)cog).lhs)
					+ getBTreeNodesCount(((BTreeCog)cog).rhs)
					+ 1;
		}

		return 0;		
	}

	public static Long findMedianKey(Cog cog, Integer n) {
		if(n == null) {
			n = getBTreeNodesCount(cog);
		}
		Long med = findMedianBTreeSeperator(cog, n);
		inorderNodeIndex = 0;
		return med;	   
	}

	public static Long findMedianBTreeSeperator(Cog cog, int n) {
		if(cog != null && cog instanceof BTreeCog) {
			Long med = findMedianBTreeSeperator(((BTreeCog)cog).lhs, n);
			if (med != null) return med;
			if (inorderNodeIndex == n/2) return ((BTreeCog)cog).sep;
			inorderNodeIndex++;
			return findMedianBTreeSeperator(((BTreeCog)cog).rhs, n);
		}			
		return null;
	}

}