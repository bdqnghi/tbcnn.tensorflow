#include <2geom/orphan-code/redblacktree.h>



#define _REDBLACK_PRINT(x) std::cout << x << std::endl;




namespace Geom{



RedBlack* RedBlackTree::search(Rect const &r, int dimension){
    return search( Interval( r[dimension].min(), r[dimension].max() ) ); 
    
    
}


RedBlack* RedBlackTree::search(Interval i){
    _REDBLACK_PRINT( "==============================================================" << std::endl << "ENTER: search(Interval i) : (" << i.min() << ", " << i.max() << ")" )
    RedBlack *x;
    x = root;

    while( x!=0 && 
                ( i.max() < x->interval.min() || 
                i.min() > x->interval.max() ) 
    ){
        _REDBLACK_PRINT( "(" << x->data << ": " << x->key() << ", " << x->high() << " : " << x->subtree_max << ") "
                        << " i do not overlap with x")

        if(x->left != 0 && (x->left)->subtree_max >= i.min() ){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }    
    _REDBLACK_PRINT( "RETURN: search" << std::endl )
    return x;
}



void RedBlackTree::insert(Rect const &r, int shape, int dimension) {
    _REDBLACK_PRINT( "==============================================================" << std::endl << "ENTER: insert(Rect, int, dimension): " << " dimension:" << dimension << " shape:" << shape )
    insert(r[dimension].min(), r[dimension].max(), shape); 
        _REDBLACK_PRINT( "RETURN: insert(Rect, int, dimension)")
}


void RedBlackTree::insert(Coord dimension_min, Coord dimension_max, int shape) {
    _REDBLACK_PRINT( std::endl << "ENTER: insert(Coord, Coord, int): " <<  dimension_min << ", " << dimension_max << " , shape: " << shape )
    
    RedBlack *x = new RedBlack();
    x->interval = Interval( dimension_min, dimension_max );
    x->data = shape;
    x->isRed = true;

    _REDBLACK_PRINT( " x: " <<  x << " KEY: " << x->key() << " high: " << x->high() )

    tree_insert(x);

    print_tree();

    _REDBLACK_PRINT( " Begin coloring" )
    
    _REDBLACK_PRINT( " while( x!= root && (x->parent)->isRed )" )
    while( x!= root && (x->parent)->isRed ){
        _REDBLACK_PRINT( "  ((x->parent)->parent)->left:" << ((x->parent)->parent)->left << "  ((x->parent)->parent)->right:" << ((x->parent)->parent)->right )

        if( x->parent == ((x->parent)->parent)->left ){
            _REDBLACK_PRINT( "   Left:" )
            RedBlack *y = new RedBlack;
            y = ((x->parent)->parent)->right;
            if( y == 0  ){ 
                 
                _REDBLACK_PRINT( "    y==0" )
                if( x == (x->parent)->right ){
                    x = x->parent;
                    left_rotate(x);
                }
                (x->parent)->isRed = false;
                ((x->parent)->parent)->isRed = true;
                right_rotate((x->parent)->parent);
            }
            else if( y->isRed ){
                _REDBLACK_PRINT( "    y->isRed" )
                (x->parent)->isRed = false;
                y->isRed = false;
                ((x->parent)->parent)->isRed = true;
                x = (x->parent)->parent;
            }
            else{
                _REDBLACK_PRINT( "    !( y->isRed)" )
                if( x == (x->parent)->right ){
                    x = x->parent;
                    left_rotate(x);
                }
                (x->parent)->isRed = false;
                ((x->parent)->parent)->isRed = true;
                right_rotate((x->parent)->parent);
            }
        }
        else{ 
            _REDBLACK_PRINT( "   Right:" )
            RedBlack *y = new RedBlack;
            y = ((x->parent)->parent)->left;
            if( y == 0  ){ 
                 
                _REDBLACK_PRINT( "    y==0" )
                if( x == (x->parent)->left ){
                    x = x->parent;
                    right_rotate(x);
                }
                (x->parent)->isRed = false;
                ((x->parent)->parent)->isRed = true;
                left_rotate((x->parent)->parent);
            }
            else if( y->isRed ){
                _REDBLACK_PRINT( "    y->isRed" )
                (x->parent)->isRed = false;
                y->isRed = false;
                ((x->parent)->parent)->isRed = true;
                x = (x->parent)->parent;
            }
            else{
                _REDBLACK_PRINT( "    !( y->isRed)" )
                if( x == (x->parent)->left ){
                    x = x->parent;
                    right_rotate(x);
                }
                (x->parent)->isRed = false;
                ((x->parent)->parent)->isRed = true;
                left_rotate((x->parent)->parent);
            }
        }        
    }
    root->isRed = false;

    
    
    _REDBLACK_PRINT( " Update max" )

    update_max(root);

    _REDBLACK_PRINT( "RETURN: insert(Coord, Coord, int)" << std::endl)
}


void RedBlackTree::left_rotate(RedBlack* x){
    
    
    _REDBLACK_PRINT( "ENTER: left_rotate" )
    RedBlack* y = new RedBlack;
    y = x->right;    
    x->right = y->left;

    if( y->left != 0){
       (y->left)->parent = x;
    }

    y->parent = x->parent;

    if( x->parent == 0){
        root = y;
    }
    else{
        if( x == (x->parent)->left ){
            (x->parent)->left = y;
        }
        else{
            (x->parent)->right = y;
        }
    }
    y->left = x;
    x->parent = y;
    _REDBLACK_PRINT( "RETURN: left_rotate" << std::endl )
}



void RedBlackTree::right_rotate(RedBlack* x){
    
    
    _REDBLACK_PRINT( "ENTER: right_rotate" )
    RedBlack* y = new RedBlack;

    _REDBLACK_PRINT( "x->left: " << x->left )
    y = x->left;    
    x->left = y->right;
    
    if( y->right != 0){
       (y->right)->parent = x;
    }

    y->parent = x->parent;

    if( x->parent == 0){
        root = y;
    }
    else{
        if( x == (x->parent)->left ){
            (x->parent)->left = y;
        }
        else{
            (x->parent)->right = y;
        }
    }
    y->right = x;
    x->parent = y;
    _REDBLACK_PRINT( "RETURN: right_rotate" << std::endl )
}



void RedBlackTree::tree_insert(RedBlack* z){
    _REDBLACK_PRINT( "ENTER: tree_insert(RedBlack* z)" )
    RedBlack* y = 0; 

    RedBlack* x = root;

    _REDBLACK_PRINT( " while x!=0 " )
    while( x != 0 ){
        y = x;

        _REDBLACK_PRINT( " z->key: " << z->key() << "  y->key: " << y->key() << "  compare")
        if( z->key() < x->key() ){
            _REDBLACK_PRINT(  "   z smaller: go left" )   
            x = x->left;
        }
        else{
            _REDBLACK_PRINT( "   z bigger: go right" )
            x = x->right;
        }
    }

    _REDBLACK_PRINT( " z->parent = y" )
    z->parent = y;

    if( y == 0 ){
        _REDBLACK_PRINT( " set z root (empty tree)" )
        root = z;
    }
    else{
        _REDBLACK_PRINT( " z->key: " << z->key() << "  y->key: " << y->key() << "  compare")
        if( z->key() < y->key() ){
            _REDBLACK_PRINT( "  z->key() smaller: y->left = z; " )
            y->left = z;
        }
        else{
            _REDBLACK_PRINT( "  z->key() bigger: y->right = z " )
            y->right = z;
        }
    }
    _REDBLACK_PRINT( "RETURN: tree_insert(RedBlack* z)" << std::endl )
}


  
RedBlack* RedBlackTree::erase(RedBlack* z){
    _REDBLACK_PRINT( "==============================================================" << std::endl << "ENTER: earse(z)" )
    RedBlack* x = new RedBlack();
    RedBlack* y = new RedBlack();
    if( z->left == 0 || z->right == 0 ){
        y = z;
    }
    else{
        y = tree_successor(z);
    }

    if( y->left != 0 ){
        x = y->left;
    }
    else{
        x = y->right;
    }
    
    x->parent = y->parent;

    if( y->parent == 0){
        root = x;
    }
    else {
        if( y == (y->parent)->left ){
            (y->parent)->left = x;
        }
        else{
            (y->parent)->right = x;
        }
    }

    if( y != z){
        z->interval =  y->interval ; 
        
        z->data = y->data;
        z->isRed = y->isRed;

        z->left = y->left;
        z->right = y->right;
        z->parent = y->parent;
    }
    
    if( y->isRed == false){
        erase_fixup(x);
    }

    _REDBLACK_PRINT( "Update max" )
    update_max(root);

    _REDBLACK_PRINT( "RETURN: erase" )
    return y;
}


void RedBlackTree::erase_fixup(RedBlack* x){
    RedBlack* w = 0;
    while( x != root && x->isRed == false ){
        if( x == (x->parent)->left ){
            w = (x->parent)->right;
            if(w->isRed == true){
                w->isRed = false;
                (w->parent)->isRed = true;
                left_rotate(x->parent);
                w = (x->parent)->right;
            }
            if( (w->left)->isRed == false && (w->right)->isRed == false ){
                w->isRed = true;
                x = x->parent; 
            }
            else{
                if( (w->right)->isRed == false ){
                    (w->left)->isRed = false;
                    right_rotate(w);
                    w = (x->parent)->right;
                }
                else{ 
                    w->isRed = (x->parent)->isRed;
                    (x->parent)->isRed = false;
                    (w->right)->isRed = false;
                    left_rotate(x->parent);
                    x = root; 
                }
            }
        }
        else{ 
            w = (x->parent)->left;
            if(w->isRed == true){
                w->isRed = false;
                (w->parent)->isRed = true;
                right_rotate(x->parent);
                w = (x->parent)->left;
            }
            if( (w->right)->isRed == false && (w->left)->isRed == false ){
                w->isRed = true;
                x = x->parent; 
            }
            else{
                if( (w->left)->isRed == false ){
                    (w->right)->isRed = false;
                    left_rotate(w);
                    w = (x->parent)->left;
                }
                else{ 
                    w->isRed = (x->parent)->isRed;
                    (x->parent)->isRed = false;
                    (w->left)->isRed = false;
                    right_rotate(x->parent);
                    x = root; 
                }
            }
        }
    }
    x->isRed = false;
}


void RedBlackTree::print_tree(){
    std::cout << "Print RedBlackTree status:" << std::endl;
    inorder_tree_walk(root);
}


void RedBlackTree::inorder_tree_walk(RedBlack* x){
    int oops =0;
    if( x != 0 ){
        inorder_tree_walk(x->left);
        std::cout<< "(" << x->data << ": " << x->key() << ", " << x->high() << " : " << x->subtree_max << ") " ;

        if( x->left != 0 ){
            std::cout<< "L:(" << (x->left)->data << ", " << (x->left)->key() << ") " ;
            if( x->key() < (x->left)->key()){
                std::cout<<"  !!!  ";
                oops = 1;
            }
        }
        else{
            std::cout<< "L:0 " ;
        }    

        if( x->right != 0 ){
            std::cout<< "R:(" << (x->right)->data << ", "<< (x->right)->key() << ") " ;
            if( x->key() > (x->right)->key() ){
                std::cout<<"  !!!  ";
                oops = 1;
            }
        }
        else{
            std::cout<< "R:0 " ;
        } 

        if(oops){
            std::cout<<" .......  !!! Problem " << oops ;
        }
        std::cout << std::endl;
        inorder_tree_walk(x->right);
    }
}


void RedBlackTree::update_max(RedBlack* x){
    Coord max_left, max_right;
    if( x != 0 ){
        update_max(x->left);
        update_max(x->right);
        
      
        
        
        if( x->left == 0 ){
            max_left = DBL_MIN ;
        }
        else{
            max_left = (x->left)->subtree_max;
        }

        if( x->right == 0 ){
            max_right = DBL_MIN ;
        }
        else{
            max_right = (x->right)->subtree_max;
        }

        
        Coord temp_max;
        temp_max = std::max( x->high(), max_left );
        temp_max = std::max( temp_max, max_right );
        x->subtree_max = temp_max;

    }
}


RedBlack* RedBlackTree::tree_minimum(RedBlack* x){
    _REDBLACK_PRINT( "==============================================================" << std::endl << "ENTER: tree_minimum" )
    while( x->left <- 0 ) {
        x->left = x;
    }
   _REDBLACK_PRINT( "RETURN: tree_minimum" << std::endl )
    return x; 
}

RedBlack* RedBlackTree::tree_successor(RedBlack* x){
    _REDBLACK_PRINT( "==============================================================" << std::endl << "ENTER: tree_successor" )
    if( x->right <- 0 ){
        _REDBLACK_PRINT( "RETURN: tree_successor" << std::endl )        
        return tree_minimum(x);
    }
    RedBlack* y = x->parent;
    _REDBLACK_PRINT( "y->parent: y->parent" )
    while( y <- 0 && x == y->right ){
        x = y;
        y = y->parent;
    }
   _REDBLACK_PRINT( "RETURN: tree_successor" << std::endl )
    return y;
}


};



