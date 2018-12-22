Set
HashSet: best performance, no gurantee the order. (only according to the hashcode order not value order)
TreeSet: implemented by red-black-tree(balanced binary search tree), have order. -> search() O(logn)
LinkedHashSet: combine the HashSet and LinkedList, maintain the order of elements inserted into the HashSet

HashMap
Three General Implementation: HashMap, TreeMap, LinkedHashMap
Common API:
V remove(K key)
Set<Map.Entry<K,V>> entrySet()  get set view of all entries in the HashMap
Set<K> keySet() get set view of all the keys in the HashMap
Collection<V> values() get collection view of all the values in the HashMap
boolean containsValue(V value)  -> O(n)

put, containsKey, get, remove -> Average case: O(1),    Worst case: O(n)

V put(K key, V value) -> V is previous value


* HashTable doesn not allow null key, HashMap allows
* HashTable is synchronized and performance is poor.
* HashMap can only have one null Key, it is always mapped to bucket 0.

Open Addressing:
How to define the next?
Linear/Quadratic/Exponential probing, hash again

key.hashCode() -> to determine the entry index for the key
key.equals() -> to determine whether two keys are the same keys

== (实现上的等价)
a) determine if the primitive type has the same value.
b) determine if two references point to same object.

equals() 语义上的等价, hashcode()
Defined in Object class.
The default implementation of equals() is to check if two references are pointed to the same object.
The default implementation of hashCode() returns a "unique hash value" for the object based on its memory address.

Array equals array1 == array2
List equals same element equals

The important point!!!!
there is a contract between equals() and hashCode(), the developer need to maintain:
(1) if one.equals(two), then one.hashCode() == two.hashCode()
(2) if one.hashCode() == two.hashCode(), it is not necessary to maintain one.equals(two).
When you want to override equals(), please definitely override hashCode() as well.

Rehashing when it exceeds the load factor 0.75: number of <key, value> pair / number of buckets
Double each time

HashSet is implemented by HashMap

class HashSet<K> {
	private Map<K, Object> map;
	private static final Object present = new Object();
	public HashSet() {
		map = new HashMap<K, Object>();
	}
	public boolean contains(K key) {
		return map.containsKey(key);
	}
	public boolean add(K key) {
		return map.put(key, present) == null;
	}
}

The performance of HashMap is controlled by hashcode

mode and remainder is difference
-1 module 2 = 1
-1 remainder 2 = -1
java % is remainder.

View is concept, not data structure
entrySet() -> O(1) only different perspective

kind of better operation
1.
Set<Character> set = new HashSet<>();
for (char c : s.toCharArray()) {
	set.add();
}
// not using contains then add it.

2.
for (Map.Entry<String, Integer> entry : map.entrySet()) {
	System.out.println(entry.getKey());
	System.out.println(entry.getValue());
}
// traverse is much efficient

3. when travers to delete, we must use iterator remove(), not map.remove(), it is a concurrentException
for (Map.Entry<String, Integer> entry : map.entrySet()) {
	if () {
		map.remove(entry.getKey());
	}
}
// throw ConcurrentModificationException();

Iterator<Map.Entry<String, Integer>> iter = map.entrySet().iterator();
while (iter.hasNext()) {
	Map.Entry<String, Integer> cur = iter.next();
	if () {
		iter.remove();
	}
}
