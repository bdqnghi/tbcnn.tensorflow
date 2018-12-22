package util;

import java.util.concurrent.ArrayBlockingQueue;

import util.Utils.BFSColor;

public class BFSRunner {
  public BFSData bfsData = null;
  public int[][] parents = null;
  public int[] numParents = null;
  int[][] graph;
  public static int maxLevel;
  public BFSRunner(int[][] graph) {
    this.graph = graph;
    bfsData = new BFSData(this.graph.length, -1);
    parents = new int[this.graph.length][];
    numParents = new int[this.graph.length];
    bfsData.initializeBFSData();
    for (int i = 0; i < bfsData.bfsColor.length; ++i) {
      parents[i] = new int[0];
      numParents[i] = 0;
    }
    maxLevel = -1;
  }
  
  public void runBFS(int source) {
    bfsData.source = source;
    ArrayBlockingQueue<Integer> bfsQueue = new ArrayBlockingQueue<Integer>(this.graph.length);
    bfsQueue.add(source);
    bfsData.bfsLevel[source] = 0;
    bfsData.bfsColor[source] = BFSColor.VISITED;
    bfsData.bfsParent[source] = - 1;  
    int nextV, nextVLevel;
    maxLevel = 0;
    while(!bfsQueue.isEmpty()) {
      nextV = bfsQueue.remove();
      nextVLevel = bfsData.bfsLevel[nextV];
      for (int nbr : graph[nextV]) {
        if (BFSColor.UNVISITED == bfsData.bfsColor[nbr]) {
          bfsQueue.add(nbr);
          bfsData.bfsParent[nbr] = nextV;
          bfsData.bfsColor[nbr] = BFSColor.VISITED;
          bfsData.bfsLevel[nbr] = nextVLevel + 1;
          maxLevel = Math.max(maxLevel, nextVLevel + 1);
          numParents[nbr] = 1;
          parents[nbr] = new int[1];
          parents[nbr][0] = nextV;
        } else if (BFSColor.VISITED == bfsData.bfsColor[nbr] &&
          (bfsData.bfsLevel[nbr] == nextVLevel + 1)){
          if (numParents[nbr] + 1 > parents[nbr].length) {
            int newParentsSize = Math.max(numParents[nbr] + 1, (int) (parents[nbr].length * 1.2));
            int[] newParents = new int[newParentsSize];
            System.arraycopy(parents[nbr], 0, newParents, 0, parents[nbr].length);
            parents[nbr] = newParents;
          }
          parents[nbr][numParents[nbr]] = nextV;
          numParents[nbr]++;
        }
      }
    }
  }
  
  public void summarizeLevelData() {
    int[] levelHistogram = new int[maxLevel + 1];
    for (int bfsLevel : bfsData.bfsLevel) {
      if (bfsLevel >= 0) {
        levelHistogram[bfsLevel]++;
      }
    }
    System.out.println("Starting to DUMP LEVEL HISTOGRAM");
    for (int level = 0; level < levelHistogram.length; ++level) {
      System.out.println("level: " + level + " numVInLevel: " + levelHistogram[level]);
    }
    System.out.println("END of DUMPING LEVEL HISTOGRAM");
  }
  
  public void summarizeParentsData() {
    int[][] levelParentsHistogram = new int[maxLevel + 1][5];
    for (int i = 0; i < bfsData.bfsLevel.length; ++i) {
      if (numParents[i] == 0) {
        continue;
      } else if (numParents[i] > 5) {
        levelParentsHistogram[bfsData.bfsLevel[i]][4]++;
      } else {
        levelParentsHistogram[bfsData.bfsLevel[i]][numParents[i] - 1]++;
      }
    }
    
    for (int i = 0; i < levelParentsHistogram.length; ++i) {
      System.out.println("LEVEL " + i);
      for (int j = 0; j < levelParentsHistogram[i].length; ++j) {
        System.out.println("vertices with " + (j+1) + " parents: " + levelParentsHistogram[i][j]);
      }
    }
  }

  public void dumpBFSRunnerData() {
    bfsData.dumpBFSData();
    for (int i = 0; i < parents.length; ++i) {
      System.out.println("v: " + i + " numParents: " + parents[i]);
    }
  }
}
