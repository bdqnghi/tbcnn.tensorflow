/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package lab6;

import java.util.*;

/******************************************************************************
* This class is a homework assignment;
* An IntBalancedSet is a set of int numbers, stored in a B-tree. 
*
* @version
*   Jan 24, 1999 by Michael Main
* revised November 2008 and April 2012 by Cate Sheller
*
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
   int[ ] data; 
   int childCount;
   IntBalancedSet[ ] subset;
   static int sct = 0; // this is a temporary variable used to examine number of recursive calls
                       // in a search operation; not intended for production code

   /**
   * Initialize an empty set.
   * @param - none
   * Postcondition: This set is empty.
   * @exception OutOfMemoryError
   *   Indicates insufficient memory for adding a new element.
   **/
   public IntBalancedSet( )
   {
      dataCount = 0;
      childCount = 0;
      data = new int[MAXIMUM + 1];
      subset = new IntBalancedSet[MAXIMUM + 2]; 
   }

   /**
   * Add a new element to this set.
   * @param  element
   *   the new element that is being added
   * Postcondition: If the element was already in this set, 
   *    then there is no change. Otherwise, the element has
   *    been added to this set.
   * @exception OutOfMemoryError
   *   Indicates insufficient memory for adding a new element.
   **/
   public void add(int element)
   {
      looseAdd(element);
        // add data, then check to see if node still OK; if not:
        if (dataCount > MAXIMUM) {
            // get ready to split root node
            IntBalancedSet child = new IntBalancedSet();    
            for (int x=0; x<dataCount; x++)
                child.data[x] = data[x];
            for (int y=0; y<childCount; y++)
                child.subset[y] = subset[y];
            child.childCount = childCount;
            child.dataCount = dataCount;
            dataCount = 0;
            childCount = 1;
            subset[0] = child;
            fixExcess(0);
        }
    }
   
   /**
   * Generate a copy of this set.
   * @param - none
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
   *   true if this set contains target; otherwise false
   **/
   public boolean contains(int target)
   {
        int i;
        sct++;  // increment test variable to keep track of calls to this method
        for (i=0; i<dataCount && data[i] < target; i++, sct++); 
        if (i < dataCount && data[i] == target) //we found it
            return true;    
        if (childCount == 0) // root has no subsets
            return false;
   
        return subset[i].contains(target);    
   }


   /**
   * Remove a specified element from this set.
   * @param target
   *   the element to remove from this set
   * Postcondition:
   *   if target was found in this set, then it has been removed
   *   and the method returns true. Otherwise this set remains
   *   unchanged and the method returns false.
   **/
   public boolean remove(int target)
   {
      // call looseRemove:
       boolean answer = looseRemove(target); // looseRemove returns a boolean!
       
       if ((dataCount == 0)  && (childCount == 1))
       {
           // fix root of the entire tree so that it no longer has zero elements
       
       }
       
      return answer;        
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
       
   // Precondition: 
   //   (i < childCount) and the entire B-tree is valid EXCEPT that
   //   subset[i] has MAXIMUM + 1 entries. Also, the root is allowed to have
   //   zero entries and one child.
   // Postcondition: 
   //   The tree has been rearranged so that the entire B-tree is valid EXCEPT
   //   that the number of entries in the root of this set might be one more than
   //   the allowed maximum.
   private void fixExcess(int i)
   {
      int ct;
        // copy middle entry of subset to root:
        for(ct = dataCount; ct > i; ct--)
            data[ct] = data[ct-1];
        data[i] = subset[i].data[MINIMUM];
        dataCount++;
        // split child into 2 subsets:
        IntBalancedSet leftChild = new IntBalancedSet(),
                       rightChild = new IntBalancedSet();
        leftChild.dataCount = MINIMUM;
        rightChild.dataCount = MINIMUM;
        // copy data from original subset into 2 splits:
        for (ct = 0; ct < MINIMUM; ct++) {
            leftChild.data[ct] = subset[i].data[ct];
            rightChild.data[ct] = subset[i].data[ct+MINIMUM+1];
        }
        // copy subsets of child if they exist:
        int subChCt = (subset[i].childCount)/2;
        for (ct = 0; ct < subChCt; ct++) {
            leftChild.subset[ct] = subset[i].subset[ct];
            rightChild.subset[ct] = subset[i].subset[ct+subChCt];
        }
        if(subChCt > 0) {
            leftChild.childCount = MINIMUM + 1;
            rightChild.childCount = MINIMUM + 1;
        }
        // make room in root's subset array for new children:
        subset[childCount] = new IntBalancedSet();
        for (ct = childCount; ct > i; ct--)
            subset[ct] = subset[ct-1];
        childCount++;
        // add new subsets to root's subset array:
        subset[i] = leftChild;
        subset[i+1] = rightChild;
   }

   private boolean isLeaf( )
   // Return value is true if and only if the B-tree has only a root.
   {
      return (childCount == 0);
   }
   
   // Precondition:
   //   The entire B-tree is valid.
   // Postcondition:
   //   If entry was already in the set, then the set is unchanged. Otherwise,
   //   entry has been added to the set, and the entire B-tree is still valid
   //   EXCEPT that the number of entries in the root of this set might be one
   //   more than the allowed maximum.
   private void looseAdd(int entry)
   {
        int i;
        for (i = 0; i<dataCount && data[i] < entry; i++);
        if (i < data.length && data[i] == entry)
            return;
        if (childCount == 0) // add entry at this node
        {
            for(int x = data.length-1; x > i; x--)
                data[x] = data[x-1]; // shift elements to make room
            data[i] = entry;
            dataCount++;
        }
        else  // add entry to a subset, housekeep
        {
            subset[i].looseAdd(entry);
            if(subset[i].dataCount > MAXIMUM)
                fixExcess(i);
        }     
        
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
      int i;
      for (i = 0; i<dataCount && data[i] < target; i++);
       
      if (childCount == 0 && i == dataCount)
      {
          return false;
      } else if ((childCount == 0) && (data[i] == target)  ) 
      {
          // remove the target from the data array and return true
          return true;
      } 
      if ((childCount > 0 ) && (data[i] == target))
      {
          boolean answer = subset[i].looseRemove(target);
            if ((answer) && (subset[i].dataCount < MINIMUM))  // might not need (answer) test here???
            {
                fixShortage(i);
            }
            return answer;
      } 
      if ( (childCount > 0) && ( data[i] == target))
      {
          data[i] = subset[i].removeBiggest();
          if (subset[i].dataCount < MINIMUM)
          {
               fixShortage(i);
          }
           return true;
      }
       
      
      
      return false;        
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
       if (i >= childCount) {
          throw new IllegalArgumentException("Problem in fixShortage");
      }
       if ((i != 0) && (subset[i-1].dataCount > MINIMUM )) 
       {
           transferLeft(i);
       } else if ((i != dataCount-1) && (subset[i+1].dataCount > MINIMUM))
       {
           transferRight(i);
       } else if ((i > 0) && (subset[i-1].dataCount == MINIMUM))
       {
           mergeWithLastSubset(i);
       } else if  ((i != dataCount-1) && (subset[i+1].dataCount==MINIMUM))
       {
           mergeWithNextSubset(i);
       
       }
               
               
       
   }      
   
   
    private void mergeWithLastSubset(int i)
   // Precondition: 
   //   
   // Postcondition: 
   //   subset[i] and subset[i-1] have been merged into one subset
   {
      // Implemented by student.
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
      if (dataCount <= 0) {
         // throw new IllegalArgumentException("Problem in removeBiggest");
          throw new RuntimeException("Problem in removeBiggest");
      }
      if (childCount == 0) {
        return data[--dataCount];
      }
      if (childCount > 0 ) 
      {
          int answer = subset[childCount-1].removeBiggest();
          if (subset[childCount-1].dataCount < MINIMUM) {
            fixShortage(childCount-1); 
          }
        return answer;
      }
      
      
      
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
    
    public static void main (String [] args) {
        IntBalancedSet set = new IntBalancedSet();
        Random rg = new Random();
        for (int x=0; x<50; x++)
        {
            int num = rg.nextInt(1500);
            set.add(num);
        }
        System.out.println("final version of tree");
        set.print(4); 
        int num = rg.nextInt(1500);
        System.out.println("Searching for: " + num);
        if (set.contains(num))
            System.out.println ("found it!");
        else
            System.out.println ("all that time, and nothing to show for it!");
        System.out.println("search took " + sct + " operations");  
    }
}