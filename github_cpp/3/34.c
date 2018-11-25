

#ifndef AVL_CPP
#define AVL_CPP




template <typename T, typename K>
int AVL<T,K>::bfactor() const
{
   const AVL<T,K>* right_sub = dynamic_cast<const AVL<T,K>*>(this->right_subtree());
   int rheight = -1;
   if(right_sub != NULL && right_sub->root  != NULL){
	   rheight = right_sub->height();
   }

   const AVL<T,K>* left_sub = dynamic_cast<const AVL<T,K>*>(this->left_subtree());
   int lheight =-1;
   if(left_sub != NULL && left_sub->root  != NULL){
  	   lheight = left_sub->height();
   }

   return rheight-lheight;
}



template <typename T, typename K>
void AVL<T,K>::fix_height() const
{
	
	if(this->root == NULL){
		return;
	}

	int rheight = -1;
	int lheight = -1;

	
	const AVL<T,K>* right_sub = dynamic_cast<const AVL<T,K>*>(this->right_subtree());

	if(right_sub == NULL){
		

	}else{
		right_sub->fix_height();
		rheight = right_sub->height();
		
	}

	
	const AVL<T,K>* left_sub = dynamic_cast<const AVL<T,K>*>(this->left_subtree());

	if(left_sub == NULL){
		

	}else {
		left_sub->fix_height();
		lheight = left_sub->height();
		
	}

	this->root->bt_height = (lheight>rheight)? lheight+1:rheight+1;
}



template <typename T, typename K>
void AVL<T,K>::rotate_left() 
{
	
	

    bt_node* origin = this->root;

    
    AVL<T,K>* right_sub = dynamic_cast<AVL<T,K>*>(this->right_subtree());

    this->root = right_sub->root;

    

    BT<T,K>*& left_sub = this->left_subtree();


    if(left_sub== NULL){
        	 left_sub= new AVL<T,K>;
    }
    
    dynamic_cast<AVL<T,K>*>(origin->right)->root = dynamic_cast<AVL<T,K>*>(left_sub)->root;

  
    dynamic_cast<AVL<T,K>*>(left_sub)->root = origin;


}



template <typename T, typename K>
void AVL<T,K>::rotate_right()
{
	

     bt_node* origin = this->root;

     AVL<T,K>* left_sub = dynamic_cast<AVL<T,K>*>(this->left_subtree());

     this->root = left_sub->root;

     BT<T,K>*& right_sub= this->right_subtree();

     if(right_sub== NULL){
    	 right_sub= new AVL<T,K>;
     }
     

     dynamic_cast<AVL<T,K>*>(origin->left)->root = dynamic_cast<AVL<T,K>*>(right_sub)->root;

     dynamic_cast<AVL<T,K>*>(right_sub)->root = origin;
}


template <typename T, typename K>
void AVL<T,K>::balance()
{

	if(this->root == NULL){
		return;
	}

	AVL<T,K>* left_sub = dynamic_cast<AVL<T,K>*>(this->left_subtree());

	if(left_sub !=NULL && left_sub->root != NULL){
		left_sub->balance();
	}

	AVL<T,K>* right_sub = dynamic_cast<AVL<T,K>*>(this->right_subtree());

	if(right_sub !=NULL && right_sub->root != NULL){
		right_sub->balance();
	}
    
	
	if(bfactor() == -2 ){
		
		if(left_sub->bfactor() < 0){
			
			rotate_right();
		}else{
			
			left_sub->rotate_left();
			rotate_right();
		}
	}else if(bfactor() == 2){
		
		if(right_sub->bfactor()>0){
			
			rotate_left();
		}else{
			right_sub->rotate_right();
			rotate_left();
		}
	}
}



template <typename T, typename K>
void AVL<T,K>::insert(const T& x, const K& k)
{

	if(  this->root == NULL){

		

		this->root = new bt_node(x,k);

	}else if(this->root->key == k){
		
		return;
	}else if(this->root->key < k){
		


		if(this->root->right== NULL){
			
			this->root->right = new AVL<T,K>;
		}

		AVL<T,K>* right_sub = dynamic_cast<AVL<T,K>*>(this->root->right);


		
		right_sub->insert(x,k);

	}else{


		

		if(this->root->left == NULL){
					
					this->root->left = new AVL<T,K>;
		}

		AVL<T,K>* left_sub = dynamic_cast<AVL<T,K>*>(this->root->left);


		
		left_sub->insert(x,k);
	}

    fix_height();
    balance();

}




template <typename T, typename K>
void AVL<T,K>::remove(const K& k)
{
    BST<T,K>::remove(k);

    
    fix_height();
    
    balance();
    

}



#endif 
