package Code;

public class RedBlack_Tree {

	private RedBlack_Node m_ROOT ;
	private int m_SIZE ; 
	
	public void RedBlack_Tree(){
		m_ROOT = null ;
		m_SIZE = 0 ;
	}

	public void insert( int key, int num ){
		
		RedBlack_Node newNode = new RedBlack_Node( key, num ) ;
		
		/* First Element */
		if ( m_ROOT == null ){
			m_ROOT = newNode ;
			newNode.setColor( Color.BLACK );
			m_SIZE++;
		}
		
		insert( m_ROOT, newNode );
		m_SIZE++ ;
		
	}
	
	private void insert( RedBlack_Node parent, RedBlack_Node newNode ) {
		
		/* Right */
		if ( newNode.get_Key() >= parent.get_Key() ) { 
			if ( parent.getRight() == null ){
				parent.setRight( newNode ) ;
				newNode.set_isLeftChild( false ) ;
				newNode.set_Parent( parent ) ;
				return ;
			}
			
			insert( parent.getRight(), newNode ) ;
			return ;
		}
		
		/* Left */
		if( parent.getLeft() == null ){
			parent.setLeft( newNode ) ;
			newNode.set_Parent( parent ) ;
			newNode.set_isLeftChild( true ) ;
			return ;
		}
		
		insert( parent.getLeft(), newNode ) ;
		return ;
		
	}
	
	private void checkColor( RedBlack_Node node ){
		
		if ( m_ROOT == node )
			return ;
		
		/* Two consecutive reds violation */
		if ( node.getColor() == Color.RED && node.get_Parent().getColor() == Color.RED ){
			correct( node ) ;
		}
		
		/* Recurse on parent to correct possible new violations */
		checkColor( node.get_Parent() ) ; 
		
	}
	
	private void correct( RedBlack_Node node ){
		
		if ( node.get_Parent().get_isLeftChild() == true ){
			if ( node.get_Parent().get_Parent().getRight() == null || 
					node.get_Parent().get_Parent().getRight().getColor() == Color.BLACK ){
				//rotate( node ) ;
				return ;
			}
			
			if ( node.get_Parent().get_Parent().getRight() != null ){
				node.get_Parent().get_Parent().getRight().setColor(Color.BLACK);
			}
			
			node.get_Parent().get_Parent().setColor( Color.RED );
			node.get_Parent().setColor( Color.BLACK );
			return ;
		}
		
		/* Aunt is Grandparent.left */
		if ( node.get_Parent().get_Parent().getLeft() == null || 
				node.get_Parent().get_Parent().getLeft().getColor() == Color.BLACK ){
			//rotate( node ) ;
			return ;
		}
		
		if ( node.get_Parent().get_Parent().getLeft() != null ){
			node.get_Parent().get_Parent().getLeft().setColor(Color.BLACK);
		}
		
		node.get_Parent().get_Parent().setColor( Color.RED );
		node.get_Parent().setColor( Color.BLACK );
		return ;
	}
	
	public void left_rotate( RedBlack_Node node){
		
		RedBlack_Node y = node.getRight() ;
		node.getRight().setLeft(y.getLeft());
		
		if ( node.getLeft() != null )
			y.getLeft().set_Parent(node);
		
		y.set_Parent(node.get_Parent());
		
		if( node.get_Parent() == null ){
			m_ROOT = y ;
		}else if( node == node.get_Parent().getLeft() ){
			node.get_Parent().setLeft(y);
		}else if( node.get_Parent().getRight() == y){
			y.setLeft(node);
			node.set_Parent(y);
		}
		
	}
}
