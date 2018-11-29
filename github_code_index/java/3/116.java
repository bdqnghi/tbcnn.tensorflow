package org.aschyiel.Hanoi; 

/**
 * A linked-list implementation of a stack for our tower-of-hanoi game.
 * 
 * @author toy
 *
 */
public class Tower implements Stack<Disc>
{
  public Tower( String name )
  {
    this.name = name;
  }
  
  private Disc top = null;
  private Integer _size = 0;
  
  /**
   * Neighboring towers - labeled relatively.
   */
  public Tower up   = null;
  public Tower down = null;
  
  public String name;
  
  @Override
  public void push( Disc it )
  {
    Disc prev = top;
    top = it;
    if ( null != prev )
    {
      top.next = prev;
      if ( !top.isSmallerThan( prev ) )
      {
        throw new RuntimeException( "Oopsie, illegal move!"+
          " --- tried to place "+
          it +" ontop of "+ prev +" ("+ name +")." );
      }
    }
    _size++;
  }

  @Override
  public Disc pop()
  {
    Disc it = top;
    top = ( null == it )? null : it.next;
    if ( null != it ) {
      it.next = null;
    }
    _size--;
    if ( _size < 0 ) {
      _size = 0;
    }
    return it;
  }

  @Override
  public Disc peek()
  {
    return top;
  }

  public int size()
  {
    return _size;
  } 

}
