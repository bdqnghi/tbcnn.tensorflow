package org.teachingkidsprogramming.section05recursion.Kata_and_Variation;

public class TowerOfHanoi
{
  //fields
  public static int index;
  public static void main(String[] args)
  {
    //create some constant variables (final means they can't change after initialization)
    final int MUN_DISCS = 5; // number of disc to move
    final int FROM_PEG = 1; // initial 'from' peg
    final int TO_PEG = 3; // initial 'to' peg
    final int TEMP_PEG = 2; // initial 'temp'peg
    //play game
    moveDiscs(MUN_DISCS, FROM_PEG, TO_PEG, TEMP_PEG);
    System.out.println("\nAll the discs are moved!");
  }
  private static void moveDiscs(int num, int fromPeg, int toPeg, int tempPeg)
  {
    if (num > 0)
    {
      moveDiscs(num - 1, fromPeg, tempPeg, toPeg);
      index++;
      System.out.println(index + ".Move a disc from peg " + fromPeg + "to peg" + toPeg);
      moveDiscs(num - 1, tempPeg, toPeg, fromPeg);
    }
  }
}
