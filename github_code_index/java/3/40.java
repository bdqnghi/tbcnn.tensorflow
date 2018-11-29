public class TowerOfHanoi
{
  public static int cnt = 0;
  public static void solveTowers( int disk, int source, 
                      int destination, int temp )
  {
      cnt++;
      if( disk == 1 )
      {
        System.out.printf( "\n%d --> %d", source, destination );
        return;
      }
      solveTowers(disk - 1, source, temp, destination );
      
      System.out.printf( "\n%d --> %d", source, destination );
      
      solveTowers(disk - 1, temp, destination, source  );  
  }
  
  public static void main( String[] args ) 
  {
      int start = 2;
      int end   = 3;
      int temp  = 1;
      int disks = 20;
      TowerOfHanoi.solveTowers( disks, start, end, temp );
      System.out.printf("\nNo. of moves: %d\n", TowerOfHanoi.cnt );
      System.exit(0);
  }
}
