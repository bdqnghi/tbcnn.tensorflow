package com.jagerdown.towerofhanoi.impl;

//import org.slf4j.Logger;
//import org.slf4j.LoggerFactory;

import com.jagerdown.towerofhanoi.TowerOfHanoi;

/**
 * 
 * Tower of Hanoi Rules: 
 * 1: Only one disk can be moved at a time. 
 * 2: Each move consists of taking the upper disk from one of the stacks and placing it on top of
 * another stack i.e. a disk can only be moved if it is the uppermost disk on a stack. 
 * 3: No disk may be placed on top of a smaller disk.
 * 
 * @author jagerdown
 *
 */
public class TowerOfHanoiSolution implements TowerOfHanoi {

  //private static final Logger LOG = LoggerFactory.getLogger(TowerOfHanoi.class);

  private Tower towerOfHanoi;
  private int numberOfDisks;
  private int numberOfRods;

  public TowerOfHanoiSolution(int numberOfDisks, int numberOfRods) {
    this.towerOfHanoi = null;
    this.numberOfDisks = numberOfDisks;
    this.numberOfRods = numberOfRods;

    // Probably shouln't be in the constructor
    this.initiateTowerOfHanoi();
  }

  public Tower getTower() {
    return this.towerOfHanoi;
  }

  public void initiateTowerOfHanoi() {
    this.towerOfHanoi = new Tower(numberOfDisks, numberOfRods);
  }

  /**
   * Recursively go through all (but the last disk )the disks in rod0, and move them the rod1, so that we can can move the last disk on rod0 to rod2, and the
   * recurse again to move the remaining disks from rod1 to rod2.
   * 
   * @param depth
   * @param rod0
   * @param rod1
   * @param rod2
   */
  public void recursiveSolveTowerOfHanoi(int depth, int rod0, int rod1, int rod2) {
    if (depth == 1) {
      towerOfHanoi.getTower().get(rod2).push(towerOfHanoi.getTower().get(rod0).pop());
      return;
    }
    recursiveSolveTowerOfHanoi(depth - 1, rod0, rod2, rod1);
    towerOfHanoi.getTower().get(rod2).push(towerOfHanoi.getTower().get(rod0).pop());
    recursiveSolveTowerOfHanoi(depth - 1, rod1, rod0, rod2);
  }
}
