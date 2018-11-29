// File: IntBalancedSet.java from the package edu.colorado.linked

// The implementation of most methods in this file is left as a student
// exercise from Section 10.2 of "Data Structures and Other Objects Using Java"

package edu.colorado.collections;

/******************************************************************************
* This class is a homework assignment;
* An <CODE>IntBalancedSet</CODE> is a set of int numbers, stored in a B-tree. 
*
* <b>Outline of Java Source Code for this class:</b>
*   <A HREF="../../../../edu/colorado/collections/IntTreeBag.java">
*   http://www.cs.colorado.edu/~main/edu/colorado/collections/IntTreeBag.java
*   </A>
*
* <b>Note:</b>
*   This file contains mostly blank implementations ("stubs")
*   because this is a Programming Project for my students.
*
* @version Feb 10, 2016
*
* @see IntArrayBag
* @see IntLinkedBag
* @see IntTreeBag
******************************************************************************/
public class IntBalancedSet implements Cloneable
{
   // Invariant of the IntBalancedSet class:
   //   1. The elements of the Set are stored in a B-tree, satisfying the six
   //      B-tree rules.
   //   2. The number of elements in the tree's root is in the instance
   //      variable dataCount, and the number of subtrees of the root is stored
   //      stored in the instance variable childCount.
   //   3. The root's elements are stored in data[0] through data[dataCount-1].
   //   4. If the root has subtrees, then subtree[0] through 
   //      subtree[childCount-1] are references to these subtrees.
   private final int MINIMUM = 1;
   private final int MAXIMUM = 2*MINIMUM;
   int dataCount;
   int[ ] data = new int[MAXIMUM + 1];
   int childCount;
   IntBalancedSet[ ] subset = new IntBalancedSet[MAXIMUM + 2]; 


   /**
   * Initialize an empty set.
   * <b>Postcondition:</b>
   *   This set is empty.
   * @exception OutOfMemoryError
   *   Indicates insufficient memory for adding a new element.
   **/
   public IntBalancedSet( )
   {
      dataCount = 0;
      childCount = 0;
   }


   /**
   * Add a new element to this set.
   * @param  element
   *   the new element that is being added
   * <b>Postcondition:</b>
   *   If the element was already in this set, then there is no change.
   *   Otherwise, the element has been added to this set.
   * @exception OutOfMemoryError
   *   Indicates insufficient memory for adding a new element.
   **/
   public void add(int element)
   {
      // Implemented by student.
   }
   

   /**
   * Generate a copy of this set.
   * @return
   *   The return value is a copy of this set. Subsequent changes to the
   *   copy will not affect the original, nor vice versa. Note that the return
   *   value must be type cast to an <CODE>IntBalancedSet</CODE> before it 
   *   can be used.
   * @exception OutOfMemoryError
   *   Indicates insufficient memory for creating the clone.
   **/ 
   public Object clone( )
   {  // Clone a IntBalancedSet object.
      // Student will replace this return statement with their own code:
      return null;        
   }


   /**
   * Accessor method to determine whether a particular element is in this set.
   * @param target
   *   an element that may or may not be in this set
   * @return
   *   <CODE>true</CODE> if this set contains <CODE>target</CODE>;
   *   otherwise <CODE>false</CODE>
   **/
   public boolean contains(int target)
   {
      // Student will replace this return statement with their own code:
      return false;        
   }


   /**
   * Remove a specified element from this set.
   * @param target
   *   the element to remove from this set
   * @return
   *   if <CODE>target</CODE> was found in this set, then it has been removed
   *   and the method returns <CODE>true</CODE>. Otherwise this set remains
   *   unchanged and the method returns <CODE>false</CODE>.
   **/
   public boolean remove(int target)
   {
      // Student will replace this return statement with their own code:
      return false;        
   }


   public void print(int indent)
   // Print a representation of this set's B-tree, useful during debugging.
   {
      final int EXTRA_INDENTATION = 4;
      int i;
      int space;
  
      // Print the indentation and the data from this node
      for (space = 0; space < indent; space++)
         System.out.print(" ");
      for (i = 0; i < dataCount; i++)
         System.out.print(data[i] + " ");
      System.out.println( );
         
      // Print the subtrees
      for (i = 0; i < childCount; i++)
         subset[i].print(indent + EXTRA_INDENTATION);
   }
       
       
   // PRIVATE HELPER METHODS 
   // The helper methods are below with precondition/postcondition contracts.
   // Students should implement these methods to help with the other methods.

   private int deleteData(int removeIndex)
   // Precondition: 0 <= removeIndex < dataCount.
   // Postcondition: The element at data[removeIndex] has been removed and
   // subsequent elements shifted over to close the gap. Also, dataCount has
   // been decremented by one, and the return value is a copy of the
   // removed element.
   {
      // Student will replace this return statement with their own code:
      return 0;        
   }
   
   
   private IntBalancedSet deleteSubset(int removeIndex)
   // Precondition: 0 <= removeIndex < childCount.
   // Postcondition: The element at subset[removeIndex] has been removed and
   // subsequent elements shifted over to close the gap. Also, childCount has
   // been decremented by one, and the return value is a copy of the
   // removed element.
   {
      // Student will replace this return statement with their own code:
      return null;        
   }
   
   private int firstGE(int target)
   // Postcondition: The return value, x, is the first location in the root
   // such that data[x] >= target. If there is no such location, then the
   // return value is dataCount.
   {
      // Student will replace this return statement with their own code:
      return 0;        
   }
   
   
   private void fixExcess(int i)
   // Precondition: 
   //   (i < childCount) and the entire B-tree is valid EXCEPT that
   //   subset[i] has MAXIMUM + 1 entries. Also, the root is allowed to have
   //   zero entries and one child.
   // Postcondition: 
   //   The tree has been rearranged so that the entire B-tree is valid EXCEPT
   //   that the number of entries in the root of this set might be one more than
   //   the allowed maximum.
   {
      // Implemented by student.
   }


   private void fixShortage(int i)
   // Precondition: 
   //   (i < childCount) and the entire B-tree is valid EXCEPT that
   //   subset[i] has only MINIMUM - 1 entries.
   // Postcondition: 
   //   The tree has been rearranged so that the entire B-tree is valid EXCEPT
   //   that the number of entries in the root of this set might be one less than
   //   the allowed minimum.
   {
      // Implemented by student.
   }      


   private void insertData(int insertIndex, int entry)
   // Precondition: 0 <= insertIndex <= dataCount <= MAXIMUM.
   // Postcondition: The entry has been inserted at data[insertIndex] with
   // subsequent elements shifted right to make room. Also, dataCount has
   // been incremented by one.
   {
      // Implemented by student.
   }
   
   
   private void insertSubset(int insertIndex, IntBalancedSet set)
   // Precondition: 0 <= insertIndex <= childCount <= MAXIMUM+1.
   // Postcondition: The set has been inserted at subset[insertIndex] with
   // subsequent elements shifted right to make room. Also, childCount has
   // been incremented by one.
   {
      // Implemented by student.
   }
   
   
   private boolean isLeaf( )
   // Return value is true if and only if the B-tree has only a root.
   {
      return (childCount == 0);
   }
   
   
   private void looseAdd(int entry)
   // Precondition:
   //   The entire B-tree is valid.
   // Postcondition:
   //   If entry was already in the set, then the set is unchanged. Otherwise,
   //   entry has been added to the set, and the entire B-tree is still valid
   //   EXCEPT that the number of entries in the root of this set might be one
   //   more than the allowed maximum.
   {
      // Implemented by student.
   }


   private boolean looseRemove(int target)
   // Precondition:
   //   The entire B-tree is valid.
   // Postcondition:
   //   If target was in the set, then it has been removed from the set and the
   //   method returns true; otherwise the set is unchanged and the method 
   //   returns false. The entire B-tree is still valid EXCEPT that the
   //   number of entries in the root of this set might be one less than the
   //   allowed minimum.
   {
      // Student will replace this return statement with their own code:
      return false;        
   }


   private void mergeWithNextSubset(int i)
   // Precondition: 
   //   (i+1 < childCount) and the entire B-tree is valid EXCEPT that the total
   //   number of entries in subset[i] and subset[i+1] is 2*MINIMUM - 1.
   // Postcondition: 
   //   subset[i] and subset[i+1] have been merged into one subset (now at
   //   subset[i]), and data[i] has been passed down to be the median entry of the
   //   new subset[i]. As a result, the entire B-tree is valid EXCEPT that the
   //   number of entries in the root of this set might be one less than the
   //   allowed minimum.
   {
      // Implemented by student.
   }

   private int removeBiggest( )
   // Precondition: 
   //   (dataCount > 0) and the entire B-tree is valid.
   // Postcondition:
   //   The largest item in the set has been removed, and the value of this
   //   item is the return value. The B-tree is still valid EXCEPT
   //   that the number of entries in the root of this set might be one less than
   //   the allowed minimum.
   {
      // Student will replace this return statement with their own code:
      return 0;        
   }

    
   public void transferLeft(int i)
   // Precondition: 
   //   (0 < i < childCount) and (subset[i]->dataCount > MINIMUM)
   //   and the entire B-tree is valid EXCEPT that
   //   subset[i-1] has only MINIMUM - 1 entries.
   // Postcondition:
   //   One entry has been shifted from the front of subset[i] up to
   //   data[i-1], and the original data[i-1] has been shifted down to the last
   //   entry of subset[i-1]. Also, if subset[i] is not a leaf, then its first
   //   subset has been transfered over to be the last subset of subset[i-1].
   //   As a result, the entire B-tree is now valid.
   {
      // Implemented by student.
   }
   

   public void transferRight(int i)
   // Precondition: 
   //   (i+1 < childCount) and (subset[i]->dataCount > MINIMUM)
   //   and the entire B-tree is valid EXCEPT that
   //   subset[i] has only MINIMUM - 1 entries.
   // Postcondition: One entry has been shifted from the end of subset[i] up to
   //   data[i], and the original data[i] has been shifted down to the first entry
   //   of subset[i+1]. Also, if subset[i] is not a leaf, then its last subset has
   //   been transfered over to be the first subset of subset[i+1].
   //   As a result, the entire B-tree is now valid.
   {
      // Implemented by student.
   }
   
}
