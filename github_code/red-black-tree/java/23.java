package copy.java.util;

import java.util.ArrayList;
import java.util.List;
import java.util.TreeMap;

/**
 * This class provide two static methods to print the java.util.TreeMap instance as 
 * the corresponding tree-structure. Unless the console supports color print then 
 * before tree's print invoke the method 'setColorPrintSupport(false)', by default
 * supposes supported color print. This class works on the base of {@link TreeMapCopy}.
 * 
 * @author e-polischuk
 * @see TreeMapCopy
 * @since 1.8
 *
 */
public final class TreeMapPrinter {
    /**
     * The field defines an approach of red-black-tree print:
     * if console supports color print - {@code true} (by default),
     * unless - {@code false}, thus node's color will be shown by
     * the corresponding sign - 'b' of 'r'.
     */
    private static boolean colorPrintSupport = true;
    
    private TreeMapPrinter() {}
    
    /**
     * Prints {@code java.util.TreeMap} instance as the corresponding tree-structure 
     * dilative down.
     * 
     * @param <K> the type of keys maintained by {@code java.util.TreeMap}
     * @param <V> the type of mapped {@code java.util.TreeMap} values
     * @param tree the {@code java.util.TreeMap} instance;
     * @throws NullPointerException if tree is {@code null}.
     */
    public synchronized static <K, V> void printTree(TreeMap<K, V> tree) {
	if (tree == null) throw new NullPointerException();
	TreeMapCopy<K, V> duplicate = new TreeMapCopy<>(tree);
	printRedBlackTree(getPrintArrayOf(duplicate), unitOf(duplicate), false);
    }
    
    /**
     * Prints {@code java.util.TreeMap} instance as the corresponding tree-structure 
     * dilative up.
     * 
     * @param <K> the type of keys maintained by {@code java.util.TreeMap}
     * @param <V> the type of mapped {@code java.util.TreeMap} values
     * @param tree the {@code java.util.TreeMap} instance;
     * @throws NullPointerException if tree is {@code null}.
     */
    public synchronized static <K, V> void printReversedTree(TreeMap<K, V> tree) {
	if (tree == null) throw new NullPointerException();
	TreeMapCopy<K, V> duplicate = new TreeMapCopy<>(tree);
	printRedBlackTree(getPrintArrayOf(duplicate), unitOf(duplicate), true);
    }
    
    /**
     * In case unless the console supports red-black-tree's color print, then
     * use this method with {@code false} argument before invoke of 
     * {@code printTree(TreeMap)} or {@code printReversedTree(TreeMap)}, thus
     * instead corresponding node's color near the each printed node's value 
     * will be the corresponding sign - 'b' or 'r'. By default supposes that 
     * color print is supported.
     * 
     * @param withColor {@code false} unless console supports color print, 
     * 			{@code true} - by default.
     */
    public static void setColorPrintSupport(boolean withColor) {
	colorPrintSupport = withColor;
    }
    
    /** 
     * By default returns {@code true} what supposes - the console supports color print,
     * unless - {@code false}.
     * 
     * @return {@link #colorPrintSupport}
     *  */
    public static boolean isColorPrintSupport() {
	return colorPrintSupport;
    }

    private static <K, V> TreeMapCopy.Entry<K, V>[][] getPrintArrayOf(TreeMapCopy<K, V> tree) {
	TreeMapCopy.Entry<K, V> root = rootOf(tree);
	int hight = hightOf(root);
	int width = (int) Math.pow(2, hight) - 1;
	TreeMapCopy.Entry<K, V>[][] array = emptyArrayOf(hight + 1);
	fillInArray(array, root, hight, width);
	return array;
    }
    
    private static <K, V> int unitOf(TreeMapCopy<K, V> map) {
	int unit = map.isEmpty() ? 0 : map.firstKey().toString().length();
	for (K k : map.keySet()) {
	    if (k.toString().length() > unit) 
		unit = k.toString().length();
	}
	return unit + (colorPrintSupport ? 0 : 1);
    }
    
    private static <K, V> TreeMapCopy.Entry<K, V> rootOf(TreeMapCopy<K, V> map) {
	for (java.util.Map.Entry<K, V> e : map.entrySet()) {
	    TreeMapCopy.Entry<K, V> entry = (TreeMapCopy.Entry<K, V>) e;
	    if (entry.parent == null) 
		return entry;
	}
	return null;
    }
    
    private static <K, V> int hightOf(TreeMapCopy.Entry<K, V> root) {
	List<Integer> list = new ArrayList<>();
	searchHight(root, list, 0);
	int max = 0;
	for (int i : list) {
	    if (max < i) max = i;
	}
	return max;
    }
    
    private static <K, V> void searchHight(TreeMapCopy.Entry<K, V> root, List<Integer> list, int level) {
	if (root == null) return;
	list.add(level);
	if (root.left != null)
	    searchHight(root.left, list, level + 1);
	if (root.right != null)
	    searchHight(root.right, list, level + 1);
    }

    @SuppressWarnings({ "unchecked" })
    private static <K, V> TreeMapCopy.Entry<K, V>[][] emptyArrayOf(int hight) {
	int width = (int) Math.pow(2, hight) - 1;
	return new TreeMapCopy.Entry[hight][width];
    }
    
    private static <K, V> void fillInArray(TreeMapCopy.Entry<K, V>[][] array, TreeMapCopy.Entry<K, V> root, int hight, int width) {
	if (root == null) return;
	array[hight][width] = root;
	int shift = (int) Math.pow(2, hight - 1);
	if (root.left != null)
	    fillInArray(array, root.left, hight - 1, width - shift);
	if (root.right != null)
	    fillInArray(array, root.right, hight - 1, width + shift);
    }

    private static <K, V> void printRedBlackTree(TreeMapCopy.Entry<K, V>[][] printArray, int unit, boolean reversed) {
	int hight = reversed ? 0 : printArray.length - 1;
	int end = reversed ? printArray.length : -1;
	while (hight != end) {
	    for (int width = 0; width < printArray[hight].length; width++) {
		printEntry(printArray[hight][width], hight, width, unit);
	    }
	    System.out.println();
	    hight = reversed ? hight + 1 : hight - 1;
	}
    }

    private static <K, V> void printEntry(TreeMapCopy.Entry<K, V> entry, int hight, int width, int unit) {
	String g = colorPrintSupport ? "\u001B[32m" : "";
	String x = colorPrintSupport ? "\u001B[0m" : "";
	if (entry == null) {
	    String gap = space(unit, '.');
	    String empty = space(unit, '_' );
	    int end = (int) Math.pow(2, hight) - 1;
	    int div = (int) Math.pow(2, hight + 1);
	    String space = (width == end || (width - end) % div == 0) ? empty : gap;
	    System.out.print(g+ space +x);
	} else {
	    String r = colorPrintSupport ? "\u001B[31;1m" : "";
	    String colorSign = colorPrintSupport ? "" : (entry.color ? "b" : "r");
	    String key = entry.key.toString() + colorSign;
	    String node = entry.color ? key : r+ key + x;
	    String shift = key.length() == unit ? "" : g+ space(unit - key.length(), ' ') +x;
	    System.out.print(shift + node);
	}
    }
    
    private static String space(int size, char sign) {
	StringBuilder sb = new StringBuilder();
	while (size-- > 0)
	    sb.append(sign);
	return sb.toString();
    }
    
}
