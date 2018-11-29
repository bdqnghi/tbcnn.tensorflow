public class editdistance {
	static int min(int n1, int n2) {
		if (n1 <= n2)
			return n1;
		else {
			return n2;
		}
	}

	static int editdistance(String s1, String s2, int i1, int i2) {
		if (i1 >= s1.length()) {
			if (i2 >= s2.length())
				return 0;
			else {
				return s2.length() - i2;
			}
		} else {
			if (i2 >= s2.length())
				return s1.length() - i1;
			else {
				if (s1.charAt(i1) == s2.charAt(i2))
					return editdistance(s1, s2, i1 + 1, i2 + 1);
				else {
					int p1 = editdistance(s1, s2, i1 + 1, i2) + 1;
					int p2 = editdistance(s1, s2, i1, i2 + 1) + 1;
					int p3 = editdistance(s1, s2, i1 + 1, i2 + 1) + 1;
					return min(min(p1, p2), p3);
				}
			}
		}

	}

	public static void main(String[] args) {
		System.out.println(editdistance("asegbxih", "inebxi", 0, 0));
	}
}
