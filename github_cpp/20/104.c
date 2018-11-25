#include "stdafx.h"
#include "RedBlackTree.h"
#include <stdio.h>

CRedBlackTree::CRedBlackTree()
{
	m_iNodeCount = 0;
	m_pRoot = nullptr;

	m_stNil.enColor = st_TNODE::enBLACK;
	m_stNil.pParent = nullptr;
	m_stNil.pLeft = nullptr;
	m_stNil.pRight = nullptr;
}

CRedBlackTree::~CRedBlackTree()
{
	ReleaseTree();
}

bool CRedBlackTree::InsertNode(int iData)
{
	st_TNODE *pTemp = new st_TNODE;

	pTemp->iData = iData;
	pTemp->pLeft = &m_stNil;
	pTemp->pRight = &m_stNil;
	pTemp->pParent = nullptr;
	pTemp->enColor = st_TNODE::enRED;

	if (nullptr == m_pRoot)
	{
		m_pRoot = pTemp;
		m_pRoot->enColor = st_TNODE::enBLACK;
		return true;
	}

	if (false == linkNode(m_pRoot, pTemp))
	{
		delete pTemp;

		return false;
	}

	
	
	return true;
}

bool CRedBlackTree::DeleteNode(int iData)
{
	st_TNODE *pDeleteNode = deleteNode(m_pRoot, nullptr, iData);

	if (nullptr != pDeleteNode)
	{
		delete pDeleteNode;
		return true;
	}
	else
	{
		return false;
	}
}

st_TNODE * CRedBlackTree::SearchNode(int iData)
{
	if (nullptr == m_pRoot)
	{
		return nullptr;
	}

	return findNode(m_pRoot, iData);
}

bool CRedBlackTree::ReleaseTree(void)
{
	if (nullptr != m_pRoot)
	{
		releaseNode(m_pRoot);
		return true;
	}
	else
	{
		return false;
	}
}

void CRedBlackTree::PreorderPrint(st_TNODE * pNode, int iDepth, int iLR)
{
	if (nullptr == pNode)
	{
		pNode = m_pRoot;
	}

	print(pNode, iDepth, iLR, enPreorder);
}

void CRedBlackTree::InorderPrint(st_TNODE * pNode, int iDepth, int iLR)
{
	if (nullptr == pNode)
	{
		pNode = m_pRoot;
	}

	print(pNode, iDepth, iLR, enInorder);
}

void CRedBlackTree::PostorderPrint(st_TNODE * pNode, int iDepth, int iLR)
{
	if (nullptr == pNode)
	{
		pNode = m_pRoot;
	}

	print(pNode, iDepth, iLR, enPostorder);
}

void CRedBlackTree::DrawTree(HDC memDC, st_TNODE *pParent, int iDepth, POINT pParentPos)
{
	WCHAR	wNodeData;

	POINT	pointNodePos;
	POINT	pointNowPos;

	RECT	rectNode = { -15, -15, 15, 15 };
	RECT	rectTemp;

	int iLineLen = 60 * m_iNodeCount / 2;

	
	if (nullptr== pParent->pParent)
	{
		
	}
	else if (pParent->pParent->iData > pParent->iData)
	{
		
	}
}


bool CRedBlackTree::linkNode(st_TNODE * pParent, st_TNODE * pChild)
{
	
	if (pParent->iData > pChild->iData)
	{
		
		if (&m_stNil == pParent->pLeft)
		{
			pParent->pLeft = pChild;
			pChild->pParent = pParent;

			balanceLink(pChild);
			m_iNodeCount++;
			return true;
		}
		else
		{
			return linkNode(pParent->pLeft, pChild);
		}
	}

	if (pParent->iData < pChild->iData)
	{
		if (&m_stNil == pParent->pRight)
		{
			pParent->pRight = pChild;
			pChild->pParent = pParent;

			balanceLink(pChild);
			m_iNodeCount++;
			return true;
		}
		else
		{
			return linkNode(pParent->pRight, pChild);
		}
	}

	return false;
}

st_TNODE * CRedBlackTree::findNode(st_TNODE * pNode, int iData)
{
	if (pNode->iData > iData)
	{
		if (nullptr == pNode->pLeft)
		{
			return nullptr;
		}

		findNode(pNode->pLeft, iData);
	}

	if (pNode->iData < iData)
	{
		if (nullptr == pNode->pRight)
		{
			return nullptr;
		}

		findNode(pNode->pRight, iData);
	}

	return pNode;
}

st_TNODE * CRedBlackTree::deleteNode(st_TNODE * pNode, st_TNODE * pParent, int iData)
{
	if (pNode->iData > iData)
	{
		if (nullptr == pNode->pLeft)
		{
			return nullptr;
		}
		else
		{
			return deleteNode(pNode->pLeft, pNode, iData);
		}
	}

	else if (pNode->iData < iData)
	{
		if (nullptr == pNode->pRight)
		{
			return nullptr;
		}
		else
		{
			return deleteNode(pNode->pRight, pNode, iData);
		}
	}
	else
	{
		
		

		
		if (nullptr == pNode->pLeft && nullptr == pNode->pRight)
		{
			
			if (pParent->pLeft == pNode)
			{
				pParent->pLeft = nullptr;
			}
			else
			{
				pParent->pRight = nullptr;
			}
			return pNode;
		}
		
		else if (nullptr != pNode->pLeft && nullptr != pNode->pRight)
		{
			
			
			
			st_TNODE *pSubstitute = pNode->pRight;

			while (nullptr != pSubstitute->pLeft)
			{
				pSubstitute = pSubstitute->pLeft;
			}

			
			pSubstitute = deleteNode(pNode, nullptr, pSubstitute->iData);

			pSubstitute->pRight = pNode->pRight;
			pSubstitute->pLeft = pNode->pLeft;

			if (pNode == m_pRoot)
			{
				m_pRoot = pSubstitute;
			}

			return pNode;
		}

		
		else
		{
			
			st_TNODE *pSubstitute = pNode;

			if (pNode->pLeft != nullptr)
			{
				pSubstitute = pNode->pLeft;
			}
			else
			{
				pSubstitute = pNode->pRight;
			}

			
			if (pParent->pLeft == pNode)
			{
				pParent->pLeft = pSubstitute;
			}
			else
			{
				pParent->pRight = pSubstitute;
			}

			if (pNode == m_pRoot)
			{
				m_pRoot = pSubstitute;
			}

			return pNode;
		}

	}
}

void CRedBlackTree::releaseNode(st_TNODE * pNode)
{
	if (&m_stNil != pNode->pLeft)
	{
		releaseNode(pNode->pLeft);
	}

	if (&m_stNil != pNode->pRight)
	{
		releaseNode(pNode->pRight);
	}

	delete pNode;
}

void CRedBlackTree::print(st_TNODE * pParent, int iDepth, int iLR, PRINT_ODER enOrder)
{
	st_TNODE *pFirstDir		= nullptr;
	st_TNODE *pSecondDir	= nullptr;

	if (iLR != 0)
	{
		if (nullptr != pParent->pLeft)
			pFirstDir = pParent->pLeft;
		if (nullptr != pParent->pRight)
			pSecondDir = pParent->pRight;
	}
	else
	{
		if (nullptr != pParent->pRight)
			pFirstDir = pParent->pRight;
		if (nullptr != pParent->pLeft)
			pSecondDir = pParent->pLeft;
	}

	if (enPreorder == enOrder)
	{
		for (int iCount = 0; iCount < iDepth; iCount++)
		{
			printf("  ");
		}

		printf("%d\n", pParent->iData);
	}


	if (nullptr != pFirstDir)
	{
		print(pFirstDir, iDepth + 1, iLR, enOrder);
	}

	if (enInorder == enOrder)
	{
		for (int iCount = 0; iCount < iDepth; iCount++)
		{
			printf("  ");
		}

		printf("%d\n", pParent->iData);
	}

	if (nullptr != pSecondDir)
	{
		print(pSecondDir, iDepth + 1, iLR, enOrder);
	}

	if (enPostorder == enOrder)
	{
		for (int iCount = 0; iCount < iDepth; iCount++)
		{
			printf("  ");
		}

		printf("%d\n", pParent->iData);
	}
}

void CRedBlackTree::balanceLink(st_TNODE * pNode)
{
	if (m_pRoot == pNode || m_pRoot == pNode->pParent)
	{
		m_pRoot->enColor = st_TNODE::enBLACK;
		return;
	}


	st_TNODE *pGrandParent = pNode->pParent->pParent;
	st_TNODE *pParent = pNode->pParent;

	
	
	if (st_TNODE::enRED != pParent->enColor)
	{
		return;
	}


	

	
	if (pParent == pGrandParent->pLeft)
	{
		

		st_TNODE *pUncle = pGrandParent->pRight;

		
		if (st_TNODE::enRED == pUncle->enColor)
		{
			
			
			pParent->enColor = st_TNODE::enBLACK;
			pUncle->enColor = st_TNODE::enBLACK;
			pGrandParent->enColor = st_TNODE::enRED;

			
			
			if (pGrandParent == m_pRoot)
			{
				pGrandParent->enColor = st_TNODE::enBLACK;
				return;
			}
			return balanceLink(pGrandParent);
		}

		
		if (st_TNODE::enBLACK == pUncle->enColor)
		{
			
			if (pNode == pParent->pRight)
			{
				rotationLeft(pParent);

				
				pNode = pParent;
				pParent = pNode->pParent;
			}

			
			pParent->enColor = st_TNODE::enBLACK;
			pGrandParent->enColor = st_TNODE::enRED;

			
			rotationRight(pGrandParent);
		}
	}


	
	if (pParent == pGrandParent->pRight)
	{

		
		st_TNODE *pUncle = pGrandParent->pLeft;

		
		if (st_TNODE::enRED == pUncle->enColor)
		{
			
			
			pParent->enColor = st_TNODE::enBLACK;
			pUncle->enColor = st_TNODE::enBLACK;
			pGrandParent->enColor = st_TNODE::enRED;

			
			return balanceLink(pGrandParent);
		}

		
		if (st_TNODE::enBLACK == pUncle->enColor)
		{
			
			if (pNode == pParent->pLeft)
			{
				rotationRight(pParent);

				
				pNode = pParent;
				pParent = pNode->pParent;
			}

			
			pParent->enColor = st_TNODE::enBLACK;
			pGrandParent->enColor = st_TNODE::enRED;

			
			rotationLeft(pGrandParent);
		}
	}
}

void CRedBlackTree::balanceDelete(st_TNODE * pNode)
{
	
	st_TNODE *pDelete = pNode;

	
	st_TNODE *pParent = pDelete->pParent;
	st_TNODE *pReplace = nullptr;
	st_TNODE *pSibling = nullptr;



	
	if (pDelete->enColor == st_TNODE::enRED)
	{
		return;
	}

	while (1)
	{
		
		

		if (pReplace == m_pRoot)
		{
			break;
		}

		
		
		if (pReplace == &m_stNil)
		{
			pReplace->pParent = pParent;
		}

		
		

		
		if (pParent->pLeft != &m_stNil)
		{
			pReplace = pParent->pLeft;
		}
		else
		{
			pReplace = pParent->pRight;
		}

		
		if (pReplace == pParent->pLeft)
		{
			
			pSibling = pParent->pRight;

			
			if (pSibling->enColor == st_TNODE::enRED)
			{
				

				
				pParent->enColor = st_TNODE::enRED;

				
				pSibling->enColor = st_TNODE::enBLACK;

				
				rotationLeft(pParent);

				break;
			}
			
			else
			{
				
				if (pSibling->pLeft->enColor == st_TNODE::enBLACK
					&& pSibling->pRight->enColor == st_TNODE::enBLACK)
				{
					pSibling->enColor = st_TNODE::enRED;
					pParent->enColor = st_TNODE::enBLACK;
					pReplace = pParent;
					pParent = pReplace->pParent;
				}
				
				else if (pSibling->pLeft->enColor == st_TNODE::enRED
					&& pSibling->pRight->enColor == st_TNODE::enBLACK)
				{
					
					pSibling->enColor = st_TNODE::enRED;

					
					pSibling->pLeft->enColor = st_TNODE::enBLACK;

					
					rotationRight(pSibling);

					continue;
				}

				else
				{
					
					
					
					pSibling->enColor = pParent->enColor;

					
					pSibling->pRight->enColor = st_TNODE::enBLACK;

					
					rotationLeft(pParent);

					
					pReplace = pSibling->pParent;

					continue;
				}
			}
		}

		
		{
			
			pSibling = pParent->pLeft;

			
			if (pSibling->enColor == st_TNODE::enRED)
			{
				

				
				pParent->enColor = st_TNODE::enRED;

				
				pSibling->enColor = st_TNODE::enBLACK;

				
				rotationRight(pParent);

				break;
			}
			
			else
			{
				
				if (pSibling->pLeft->enColor == st_TNODE::enBLACK
					&& pSibling->pRight->enColor == st_TNODE::enBLACK)
				{
					pSibling->enColor = st_TNODE::enRED;
					pReplace = pParent;
					pParent = pReplace->pParent;
				}
				
				else if (pSibling->pLeft->enColor == st_TNODE::enBLACK
					&& pSibling->pRight->enColor == st_TNODE::enRED)
				{
					
					pSibling->enColor = st_TNODE::enRED;

					
					pSibling->pRight->enColor = st_TNODE::enBLACK;

					
					rotationLeft(pSibling);

					continue;
				}

				else
				{
					
					
					
					pSibling->enColor = pParent->enColor;

					
					pSibling->pLeft->enColor = st_TNODE::enBLACK;

					
					rotationRight(pParent);

					
					pReplace = pSibling->pParent;

					continue;
				}
			}
		}
	}


	m_pRoot->enColor = st_TNODE::enBLACK;

}

void CRedBlackTree::rotationLeft(st_TNODE * pNode)
{
	
	
	

	
	st_TNODE *pGrandParent = pNode->pParent;
	st_TNODE *pParent = pNode->pRight;
	st_TNODE *pLeft = pNode;
	st_TNODE *pLeftRight = pNode->pRight->pLeft; 

												 
												 
												 
	if (nullptr != pGrandParent)
	{
		if (pGrandParent->pLeft == pNode)
		{
			pGrandParent->pLeft = pParent;
		}
		if (pGrandParent->pRight == pNode)
		{
			pGrandParent->pRight = pParent;
		}
	}
	else
	{
		
		m_pRoot = pParent;
	}

	pParent->pLeft = pLeft;
	pLeft->pParent = pParent;

	pLeft->pRight = pLeftRight;
	pLeftRight->pParent = pLeft;
}

void CRedBlackTree::rotationRight(st_TNODE * pNode)
{
	
	
	

	
	st_TNODE *pGrandParent = pNode->pParent;
	st_TNODE *pParent = pNode->pLeft;
	st_TNODE *pRight = pNode;
	st_TNODE *pRightLeft = pNode->pLeft->pRight;

	
	
	if (nullptr != pGrandParent)
	{
		if (pGrandParent->pLeft == pNode)
		{
			pGrandParent->pLeft = pParent;
		}
		if (pGrandParent->pRight == pNode)
		{
			pGrandParent->pRight = pParent;
		}
	}
	else
	{
		
		m_pRoot = pParent;
	}

	pParent->pRight = pRight;
	pRight->pParent = pParent;

	pRight->pLeft = pRightLeft;
	pRightLeft->pParent = pRight;
}
