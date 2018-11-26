import static org.junit.Assert.*;

import org.junit.Test;

/** @author Alexandros Evangelidis
 * Updated, Uday Reddy, 2014-01-15
 * 
 * This class contains one simple
 * test for each exercise,and is 
 * for verification purposes only.
 * 
 *
 *
 *Do not change or modify this file.
 *You should use the  Worksheet1Test class 
 *for your tests.
 *
 */
public class Worksheet1Verify {

	@Test
	/**
	 * Ex1
	 * Testing a list with positive numbers - should return true
	 */
	public void ex1Test1() {
	List l1 = List.cons(1,List.cons(3, (List.empty())));

		assertTrue(Worksheet1.allPositive(l1));
		
	}

	
	@Test
	/**
	 * Ex2
	 * Testing a sorted list - should return true
	 */
	public void ex2Test1() {
		List l1 = List.cons(1,List.cons(2,List.cons(3, List.cons(4,  (List.empty())))));
		
	assertTrue(Worksheet1.sorted(l1));
	
	}

	
	@Test
	/**
	 * Ex3
	 * Given two sorted lists, testing for merging lists.
	 * 
	 */
	public void ex3Test1() {
	List l1 = List.cons(2,List.cons(5,List.cons(5, List.cons(8,  (List.empty())))));
	List l2 = List.cons(5,List.cons(7,List.cons(8, List.cons(9,  (List.empty())))));	
	
	List merged = Worksheet1.merge(l1,l2);
	
	List expected = List.cons(2, List.cons(5, List.cons(5, List.cons(5, 
	List.cons(7, List.cons(8, List.cons(8, List.cons(9, List.empty()))))))));

	
	
	assertEquals(merged,expected);
	
	}
	
	
	@Test
	/**
	 * Ex4
	 * Removing duplicates from a list
	 * 
	 */
	public void ex4Test1()  {
	List l1 = List.cons(2, List.cons(5, List.cons(5, List.cons(5, 
			List.cons(7, List.cons(8, List.cons(8, List.cons(9, List.empty()))))))));	
	

	List expected = List.cons(2, List.cons(5, List.cons(7, List.cons(8, List.cons(9, List.empty())))));
	assertEquals(Worksheet1.removeDuplicates(l1), expected);
		
	}
	
	@Test
	/**
	 * Ex5 
	 * Testing for the mirrored tree.
	 */
	public void ex5Test1() {
		Tree t1 = new Tree(5,new Tree(3,new Tree(1,new Tree(), new Tree()),
				new Tree(4,new Tree(), new Tree())),
				new Tree(8,new Tree(6,new Tree(),new Tree()),new Tree()));
	
		Tree expected = new Tree(5,new Tree(8,new Tree(),new Tree(6,
				new Tree(),new Tree())),new Tree(3,new Tree(4,new Tree(),
						new Tree()),new Tree(1,new Tree(),new Tree())));
		
		assertEquals(Worksheet1.mirror(t1),expected);
		
	}
	
	@Test
	/**
	 * Ex6
	 * Testing showDescending method that returns
	 * the values as a String in descending order
	 * 
	 */
		public void ex6Test1() {
	Tree t1 = new Tree(5,new Tree(3,new Tree(1,new Tree(), new Tree()),
			new Tree(4,new Tree(), new Tree())),
			new Tree(8,new Tree(6,new Tree(),new Tree()),new Tree()));
		
	String expected = "8 6 5 4 3 1";
	System.out.println(Worksheet1.showDescending(t1));
	assertEquals(Worksheet1.showDescending(t1), expected );
		
	}

	@Test
	/**
	 * Ex7
	 * Testing for the maximum value in a binary search tree 
	 */
	public void ex7Test1() {
	Tree t1 = new Tree(5,new Tree(3,new Tree(1,new Tree(), new Tree()),
			new Tree(4,new Tree(), new Tree())),
			new Tree(8,new Tree(6,new Tree(),new Tree()),new Tree()));
	
	int expected = 8;
	
	assertEquals(Worksheet1.max(t1),expected);
	}
	
	@Test
	/**Ex8
	 * Deleting 6 from t1 (simple case).
	 */
	public void ex8Test1() {
		Tree t1 = new Tree(5,new Tree(3,new Tree(1,new Tree(), new Tree()),
				new Tree(4,new Tree(), new Tree())),
				new Tree(8,new Tree(6,new Tree(),new Tree()),new Tree()));
	
		Tree expected = new Tree(5,new Tree(3,new Tree(1,new Tree(), new Tree()),
				new Tree(4,new Tree(), new Tree())),
				new Tree(8,new Tree(),new Tree()));
		
		assertEquals(Worksheet1.delete(t1, 6),expected);
	}

	}