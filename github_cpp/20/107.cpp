

























#include <EASTL/internal/config.h>
#include <EASTL/internal/red_black_tree.h>
#include <stddef.h>



namespace eastl
{
	
	rbtree_node_base* RBTreeRotateLeft(rbtree_node_base* pNode, rbtree_node_base* pNodeRoot);
	rbtree_node_base* RBTreeRotateRight(rbtree_node_base* pNode, rbtree_node_base* pNodeRoot);



	
	
	
	EASTL_API rbtree_node_base* RBTreeIncrement(const rbtree_node_base* pNode)
	{
		if(pNode->mpNodeRight) 
		{
			pNode = pNode->mpNodeRight;

			while(pNode->mpNodeLeft)
				pNode = pNode->mpNodeLeft;
		}
		else 
		{
			rbtree_node_base* pNodeTemp = pNode->mpNodeParent;

			while(pNode == pNodeTemp->mpNodeRight) 
			{
				pNode = pNodeTemp;
				pNodeTemp = pNodeTemp->mpNodeParent;
			}

			if(pNode->mpNodeRight != pNodeTemp)
				pNode = pNodeTemp;
		}

		return const_cast<rbtree_node_base*>(pNode);
	}



	
	
	
	EASTL_API rbtree_node_base* RBTreeDecrement(const rbtree_node_base* pNode)
	{
		if((pNode->mpNodeParent->mpNodeParent == pNode) && (pNode->mColor == kRBTreeColorRed))
			return pNode->mpNodeRight;
		else if(pNode->mpNodeLeft)
		{
			rbtree_node_base* pNodeTemp = pNode->mpNodeLeft;

			while(pNodeTemp->mpNodeRight)
				pNodeTemp = pNodeTemp->mpNodeRight;

			return pNodeTemp;
		}

		rbtree_node_base* pNodeTemp = pNode->mpNodeParent;

		while(pNode == pNodeTemp->mpNodeLeft) 
		{
			pNode     = pNodeTemp;
			pNodeTemp = pNodeTemp->mpNodeParent;
		}

		return const_cast<rbtree_node_base*>(pNodeTemp);
	}



	
	
	
	
	
	
	EASTL_API size_t RBTreeGetBlackCount(const rbtree_node_base* pNodeTop, const rbtree_node_base* pNodeBottom)
	{
		size_t nCount = 0;

		for(; pNodeBottom; pNodeBottom = pNodeBottom->mpNodeParent)
		{
			if(pNodeBottom->mColor == kRBTreeColorBlack) 
				++nCount;

			if(pNodeBottom == pNodeTop) 
				break;
		}

		return nCount;
	}


	
	
	
	
	rbtree_node_base* RBTreeRotateLeft(rbtree_node_base* pNode, rbtree_node_base* pNodeRoot)
	{
		rbtree_node_base* const pNodeTemp = pNode->mpNodeRight;

		pNode->mpNodeRight = pNodeTemp->mpNodeLeft;

		if(pNodeTemp->mpNodeLeft)
			pNodeTemp->mpNodeLeft->mpNodeParent = pNode;
		pNodeTemp->mpNodeParent = pNode->mpNodeParent;
		
		if(pNode == pNodeRoot)
			pNodeRoot = pNodeTemp;
		else if(pNode == pNode->mpNodeParent->mpNodeLeft)
			pNode->mpNodeParent->mpNodeLeft = pNodeTemp;
		else
			pNode->mpNodeParent->mpNodeRight = pNodeTemp;

		pNodeTemp->mpNodeLeft = pNode;
		pNode->mpNodeParent = pNodeTemp;

		return pNodeRoot;
	}



	
	
	
	
	rbtree_node_base* RBTreeRotateRight(rbtree_node_base* pNode, rbtree_node_base* pNodeRoot)
	{
		rbtree_node_base* const pNodeTemp = pNode->mpNodeLeft;

		pNode->mpNodeLeft = pNodeTemp->mpNodeRight;

		if(pNodeTemp->mpNodeRight)
			pNodeTemp->mpNodeRight->mpNodeParent = pNode;
		pNodeTemp->mpNodeParent = pNode->mpNodeParent;

		if(pNode == pNodeRoot)
			pNodeRoot = pNodeTemp;
		else if(pNode == pNode->mpNodeParent->mpNodeRight)
			pNode->mpNodeParent->mpNodeRight = pNodeTemp;
		else
			pNode->mpNodeParent->mpNodeLeft = pNodeTemp;

		pNodeTemp->mpNodeRight = pNode;
		pNode->mpNodeParent = pNodeTemp;

		return pNodeRoot;
	}




	
	
	
	
	EASTL_API void RBTreeInsert(rbtree_node_base* pNode,
								rbtree_node_base* pNodeParent, 
								rbtree_node_base* pNodeAnchor,
								RBTreeSide insertionSide)
	{
		rbtree_node_base*& pNodeRootRef = pNodeAnchor->mpNodeParent;

		
		pNode->mpNodeParent = pNodeParent;
		pNode->mpNodeRight  = NULL;
		pNode->mpNodeLeft   = NULL;
		pNode->mColor       = kRBTreeColorRed;

		
		if(insertionSide == kRBTreeSideLeft)
		{
			pNodeParent->mpNodeLeft = pNode; 

			if(pNodeParent == pNodeAnchor)
			{
				pNodeAnchor->mpNodeParent = pNode;
				pNodeAnchor->mpNodeRight = pNode;
			}
			else if(pNodeParent == pNodeAnchor->mpNodeLeft)
				pNodeAnchor->mpNodeLeft = pNode; 
		}
		else
		{
			pNodeParent->mpNodeRight = pNode;

			if(pNodeParent == pNodeAnchor->mpNodeRight)
				pNodeAnchor->mpNodeRight = pNode; 
		}

		
		while((pNode != pNodeRootRef) && (pNode->mpNodeParent->mColor == kRBTreeColorRed)) 
		{
			EA_ANALYSIS_ASSUME(pNode->mpNodeParent != NULL);
			rbtree_node_base* const pNodeParentParent = pNode->mpNodeParent->mpNodeParent;

			if(pNode->mpNodeParent == pNodeParentParent->mpNodeLeft) 
			{
				rbtree_node_base* const pNodeTemp = pNodeParentParent->mpNodeRight;

				if(pNodeTemp && (pNodeTemp->mColor == kRBTreeColorRed)) 
				{
					pNode->mpNodeParent->mColor = kRBTreeColorBlack;
					pNodeTemp->mColor = kRBTreeColorBlack;
					pNodeParentParent->mColor = kRBTreeColorRed;
					pNode = pNodeParentParent;
				}
				else 
				{
					if(pNode->mpNodeParent && pNode == pNode->mpNodeParent->mpNodeRight) 
					{
						pNode = pNode->mpNodeParent;
						pNodeRootRef = RBTreeRotateLeft(pNode, pNodeRootRef);
					}

					EA_ANALYSIS_ASSUME(pNode->mpNodeParent != NULL);
					pNode->mpNodeParent->mColor = kRBTreeColorBlack;
					pNodeParentParent->mColor = kRBTreeColorRed;
					pNodeRootRef = RBTreeRotateRight(pNodeParentParent, pNodeRootRef);
				}
			}
			else 
			{
				rbtree_node_base* const pNodeTemp = pNodeParentParent->mpNodeLeft;

				if(pNodeTemp && (pNodeTemp->mColor == kRBTreeColorRed)) 
				{
					pNode->mpNodeParent->mColor = kRBTreeColorBlack;
					pNodeTemp->mColor = kRBTreeColorBlack;
					pNodeParentParent->mColor = kRBTreeColorRed;
					pNode = pNodeParentParent;
				}
				else 
				{
					EA_ANALYSIS_ASSUME(pNode != NULL && pNode->mpNodeParent != NULL);

					if(pNode == pNode->mpNodeParent->mpNodeLeft) 
					{
						pNode = pNode->mpNodeParent;
						pNodeRootRef = RBTreeRotateRight(pNode, pNodeRootRef);
					}

					pNode->mpNodeParent->mColor = kRBTreeColorBlack;
					pNodeParentParent->mColor = kRBTreeColorRed;
					pNodeRootRef = RBTreeRotateLeft(pNodeParentParent, pNodeRootRef);
				}
			}
		}

		EA_ANALYSIS_ASSUME(pNodeRootRef != NULL);
		pNodeRootRef->mColor = kRBTreeColorBlack;

	} 




	
	
	
	EASTL_API void RBTreeErase(rbtree_node_base* pNode, rbtree_node_base* pNodeAnchor)
	{
		rbtree_node_base*& pNodeRootRef      = pNodeAnchor->mpNodeParent;
		rbtree_node_base*& pNodeLeftmostRef  = pNodeAnchor->mpNodeLeft;
		rbtree_node_base*& pNodeRightmostRef = pNodeAnchor->mpNodeRight;
		rbtree_node_base*  pNodeSuccessor    = pNode;
		rbtree_node_base*  pNodeChild        = NULL;
		rbtree_node_base*  pNodeChildParent  = NULL;

		if(pNodeSuccessor->mpNodeLeft == NULL)         
			pNodeChild = pNodeSuccessor->mpNodeRight;  
		else if(pNodeSuccessor->mpNodeRight == NULL)   
			pNodeChild = pNodeSuccessor->mpNodeLeft;   
		else 
		{
			
			pNodeSuccessor = pNodeSuccessor->mpNodeRight;

			while(pNodeSuccessor->mpNodeLeft)
				pNodeSuccessor = pNodeSuccessor->mpNodeLeft;

			pNodeChild = pNodeSuccessor->mpNodeRight;
		}

		
		if(pNodeSuccessor == pNode) 
		{
			pNodeChildParent = pNodeSuccessor->mpNodeParent;  

			if(pNodeChild) 
				pNodeChild->mpNodeParent = pNodeSuccessor->mpNodeParent;

			if(pNode == pNodeRootRef) 
				pNodeRootRef = pNodeChild; 
			else 
			{
				if(pNode == pNode->mpNodeParent->mpNodeLeft) 
					pNode->mpNodeParent->mpNodeLeft  = pNodeChild;  
				else
					pNode->mpNodeParent->mpNodeRight = pNodeChild;
				
			}

			if(pNode == pNodeLeftmostRef) 
			{
				
				
				if(pNode->mpNodeRight && pNodeChild)
				{
					EASTL_ASSERT(pNodeChild != NULL); 
					pNodeLeftmostRef = RBTreeGetMinChild(pNodeChild); 
				}
				else
					pNodeLeftmostRef = pNode->mpNodeParent; 
			}

			if(pNode == pNodeRightmostRef) 
			{
				
				
				if(pNode->mpNodeLeft && pNodeChild)
				{
					EASTL_ASSERT(pNodeChild != NULL); 
					pNodeRightmostRef = RBTreeGetMaxChild(pNodeChild);
				}
				else 
					pNodeRightmostRef = pNode->mpNodeParent; 
			}
		}
		else 
		{
			
			
			pNode->mpNodeLeft->mpNodeParent = pNodeSuccessor; 
			pNodeSuccessor->mpNodeLeft = pNode->mpNodeLeft;

			if(pNodeSuccessor == pNode->mpNodeRight) 
				pNodeChildParent = pNodeSuccessor; 
			else
			{
				pNodeChildParent = pNodeSuccessor->mpNodeParent;

				if(pNodeChild)
					pNodeChild->mpNodeParent = pNodeChildParent;

				pNodeChildParent->mpNodeLeft = pNodeChild;

				pNodeSuccessor->mpNodeRight = pNode->mpNodeRight;
				pNode->mpNodeRight->mpNodeParent = pNodeSuccessor;
			}

			if(pNode == pNodeRootRef)
				pNodeRootRef = pNodeSuccessor;
			else if(pNode == pNode->mpNodeParent->mpNodeLeft)
				pNode->mpNodeParent->mpNodeLeft = pNodeSuccessor;
			else 
				pNode->mpNodeParent->mpNodeRight = pNodeSuccessor;

			

			pNodeSuccessor->mpNodeParent = pNode->mpNodeParent;
			eastl::swap(pNodeSuccessor->mColor, pNode->mColor);
		}

		
		if(pNode->mColor == kRBTreeColorBlack) 
		{ 
			while((pNodeChild != pNodeRootRef) && ((pNodeChild == NULL) || (pNodeChild->mColor == kRBTreeColorBlack)))
			{
				if(pNodeChild == pNodeChildParent->mpNodeLeft) 
				{
					rbtree_node_base* pNodeTemp = pNodeChildParent->mpNodeRight;

					if(pNodeTemp->mColor == kRBTreeColorRed) 
					{
						pNodeTemp->mColor = kRBTreeColorBlack;
						pNodeChildParent->mColor = kRBTreeColorRed;
						pNodeRootRef = RBTreeRotateLeft(pNodeChildParent, pNodeRootRef);
						pNodeTemp = pNodeChildParent->mpNodeRight;
					}

					if(((pNodeTemp->mpNodeLeft  == NULL) || (pNodeTemp->mpNodeLeft->mColor  == kRBTreeColorBlack)) &&
						((pNodeTemp->mpNodeRight == NULL) || (pNodeTemp->mpNodeRight->mColor == kRBTreeColorBlack))) 
					{
						pNodeTemp->mColor = kRBTreeColorRed;
						pNodeChild = pNodeChildParent;
						pNodeChildParent = pNodeChildParent->mpNodeParent;
					} 
					else 
					{
						if((pNodeTemp->mpNodeRight == NULL) || (pNodeTemp->mpNodeRight->mColor == kRBTreeColorBlack)) 
						{
							pNodeTemp->mpNodeLeft->mColor = kRBTreeColorBlack;
							pNodeTemp->mColor = kRBTreeColorRed;
							pNodeRootRef = RBTreeRotateRight(pNodeTemp, pNodeRootRef);
							pNodeTemp = pNodeChildParent->mpNodeRight;
						}

						pNodeTemp->mColor = pNodeChildParent->mColor;
						pNodeChildParent->mColor = kRBTreeColorBlack;

						if(pNodeTemp->mpNodeRight) 
							pNodeTemp->mpNodeRight->mColor = kRBTreeColorBlack;

						pNodeRootRef = RBTreeRotateLeft(pNodeChildParent, pNodeRootRef);
						break;
					}
				} 
				else 
				{   
					
					rbtree_node_base* pNodeTemp = pNodeChildParent->mpNodeLeft;

					if(pNodeTemp->mColor == kRBTreeColorRed) 
					{
						pNodeTemp->mColor        = kRBTreeColorBlack;
						pNodeChildParent->mColor = kRBTreeColorRed;

						pNodeRootRef = RBTreeRotateRight(pNodeChildParent, pNodeRootRef);
						pNodeTemp = pNodeChildParent->mpNodeLeft;
					}

					if(((pNodeTemp->mpNodeRight == NULL) || (pNodeTemp->mpNodeRight->mColor == kRBTreeColorBlack)) &&
						((pNodeTemp->mpNodeLeft  == NULL) || (pNodeTemp->mpNodeLeft->mColor  == kRBTreeColorBlack))) 
					{
						pNodeTemp->mColor = kRBTreeColorRed;
						pNodeChild       = pNodeChildParent;
						pNodeChildParent = pNodeChildParent->mpNodeParent;
					} 
					else 
					{
						if((pNodeTemp->mpNodeLeft == NULL) || (pNodeTemp->mpNodeLeft->mColor == kRBTreeColorBlack)) 
						{
							pNodeTemp->mpNodeRight->mColor = kRBTreeColorBlack;
							pNodeTemp->mColor              = kRBTreeColorRed;

							pNodeRootRef = RBTreeRotateLeft(pNodeTemp, pNodeRootRef);
							pNodeTemp = pNodeChildParent->mpNodeLeft;
						}

						pNodeTemp->mColor = pNodeChildParent->mColor;
						pNodeChildParent->mColor = kRBTreeColorBlack;

						if(pNodeTemp->mpNodeLeft) 
							pNodeTemp->mpNodeLeft->mColor = kRBTreeColorBlack;

						pNodeRootRef = RBTreeRotateRight(pNodeChildParent, pNodeRootRef);
						break;
					}
				}
			}

			if(pNodeChild)
				pNodeChild->mColor = kRBTreeColorBlack;
		}

	} 



} 
























