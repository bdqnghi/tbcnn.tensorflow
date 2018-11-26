/*
  lru.java
  LRU Caching, MCPC 2012 Problem F
  Java solution by Gabriel Foust
*/

import java.io.*;
import java.util.*;

class lru
{
    public static void main( String[] args ) throws FileNotFoundException
    {
        Scanner scanner= new Scanner( new File( "lru.in" ) );
        ArrayList<Character> cache;
        int cache_size;
        String commandString;
        int count= 0;
        while ((cache_size= scanner.nextInt()) > 0)
        {
            System.out.println( "Simulation " + ++count );
            cache= new ArrayList<Character>();
            commandString= scanner.next();
            for (int i= 0; i < commandString.length(); ++i)
            {
                char command= commandString.charAt( i );
                if (command == '!')
                {
                    if (cache.size() == 0)
                        System.out.println( "empty" );
                    else
                    {
                        for (Character c : cache)
                            System.out.print( c );
                        System.out.println();
                    }
                }
                else
                {
                    cache.remove( (Character)command );
                    if (cache.size() == cache_size)
                        cache.remove( 0 );
                    cache.add( command );
                }
            }
        }
    }
}
