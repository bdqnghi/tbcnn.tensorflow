// Copyright (c) 1998-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

// Class TBtreeToken
inline TBtreeToken::TBtreeToken(TEmpty)
/** Constructor that intialises the TBtreeToken for an empty B-tree.

@param Intialises for an empty B-tree */
	{Clear();}
inline void TBtreeToken::Touch()
/** Marks the B-tree as broken. */
	{iHeight=0;}
inline TBool TBtreeToken::IsBroken() const
/** Tests if the broken flag has been set on the B-tree.

@return True if the B-tree is broken, otherwise false. */
	{return iFirst!=KNullPageRef&&iHeight==0;}
inline TBool TBtreeToken::IsIntact() const
/** Tests if the broken flag has not been set on the B-tree .

@return True if the B-tree is not broken, otherwise false. */
	{return iFirst==KNullPageRef||iHeight!=0;}
inline TBool TBtreeToken::IsEmpty() const
/** Tests if the B-tree is empty.

@return True if the B-tree is empty, otherwise false. */
	{return iFirst==KNullPageRef;}

// Class TBtreePath
inline TBtreePath::TBtreePath()
	: iEnd(-1)
	{}
inline TPageRef TBtreePath::Node() const
	{return iNodes[iEnd];}
inline TInt TBtreePath::Entry() const
	{return iEntries[iEnd];}
inline TBool TBtreePath::IsLeaf() const
	{return iEnd==0;}
inline TBtreeHeight TBtreePath::End() const
	{return iEnd;}
inline void TBtreePath::SetEntry(TInt aEntry)
	{iEntries[iEnd]=TUint8(aEntry);}
inline void TBtreePath::Pop()
	{++iEnd;}

// Class TBtree
inline TBool TBtree::IsDirty() const
/** Tests if the dirty flag has been set on the B-tree.

Any updates to the B-tree will set this flag on the TBtree object. Applications 
can use this to determine if they need to flush the page pool and re-save 
the B-tree token, after which they can call MarkCurrent() to indicate that 
the persistent storage is now up-to-date with the TBtree object.

@return True if the dirty flag has been set, otherwise false */
	{return iStatus<0;}
inline void TBtree::MarkCurrent()
/** Clears the dirty flag. */
	{iStatus&=~EDirty;}
inline void TBtree::MarkDirty()
/** Sets the dirty flag. */
	{iStatus|=EDirty;}
inline TBool TBtree::IsBroken() const
/** Tests if the broken flag has been set on the B-tree.

Any updates to the B-tree that fail will leave this flag set on the TBtree 
object. This indicates that the persistent tree data is broken (corrupt) and 
the tree needs to be repaired. In this state, none of the functions which 
use a TBtreePos will work, only those taking a TBtreeMark.

@return True if the B-tree is broken, otherwise false. */
	{return (iStatus&EBroken)!=0;}
inline TBool TBtree::IsIntact() const
/** Tests if the broken flag has not been set on the B-tree .

@return True if the B-tree is not broken, otherwise false. */
	{return (iStatus&EBroken)==0;}
inline void TBtree::MarkBroken()
/** Sets the broken flag. */
	{if (iFirst!=KNullPageRef) iStatus|=EBroken;}
inline TBool TBtree::IsEmpty() const
/** Tests if the B-tree is empty.

@return True if the B-tree is empty, otherwise false */
	{return iFirst==KNullPageRef;}

// Template class TBtreeFix
template <class Entry,class Key>
inline TBtreeFix<Entry,Key>::TBtreeFix(TBtreeMode aMode)
	: TBtreeFixBase(aMode,sizeof(Entry),sizeof(Key))
/** Constructor that sets the B-tree mode.

@param aMode B-tree operating mode */
	{}
template <class Entry,class Key>
inline TBtreeFix<Entry,Key>::TBtreeFix(const TBtreeToken& aToken,TBtreeMode aMode)
	: TBtreeFixBase(aToken,aMode,sizeof(Entry),sizeof(Key))
/** Constructor that sets the B-tree mode and initialisation parameters.

@param aToken Parameters with which to initialise the B-tree
@param aMode B-tree operating mode */
	{}
template <class Entry,class Key>
inline TBool TBtreeFix<Entry,Key>::FindL(TBtreePos& aPos,const Key& aKey,TBtree::TFind aMode) const
	{return TBtreeFixBase::FindL(aPos,&aKey,aMode);}
template <class Entry,class Key>
inline TBool TBtreeFix<Entry,Key>::InsertL(TBtreePos& aPos,const Entry& anEntry,TAllowDuplicates aDup)
/** Inserts an entry into the tree.

@param aPos On return, the position of the entry inserted
@param anEntry Entry to insert
@param aDup Flag to indicate whether duplicate entries are allowed in the tree
@return True if successful, false if the entry was a duplicate and aDup was 
set to ENoDuplicates */
	{return TBtreeFixBase::InsertL(aPos,&anEntry,aDup);}
template <class Entry,class Key>
inline TBool TBtreeFix<Entry,Key>::DeleteL(const Key& aKey)
/** Delete an entry.

@param aKey Key of the entry to delete
@return True if successful, false if the entry was not found */
	{return TBtreeFixBase::DeleteL(&aKey);}
template <class Entry,class Key>
inline Entry TBtreeFix<Entry,Key>::AtL(const TBtreePos& aPos) const
/** Gets the entry at the specified position.

@param aPos Position of the entry to get
@return Entry at position aPos */
	{Entry e;TBtreeFixBase::ExtractAtL(aPos,&e);return e;}
template <class Entry,class Key>
inline Entry TBtreeFix<Entry,Key>::AtL(const TBtreeMark& aMark) const
/** Gets the entry at the specified iterator position.

@param aMark Iterator to use to get the entry
@return Entry at current iterator position */
	{Entry e;TBtreeFixBase::ExtractAtL(aMark,&e);return e;}
template <class Entry,class Key>
inline void TBtreeFix<Entry,Key>::ExtractAtL(const TBtreePos& aPos,Entry& anEntry) const
/** Gets the entry at the specified position.

@param aPos Position of the entry to get
@param anEntry On return, the specified entry */
	{TBtreeFixBase::ExtractAtL(aPos,&anEntry);}
template <class Entry,class Key>
inline void TBtreeFix<Entry,Key>::ExtractAtL(const TBtreeMark& aMark,Entry& anEntry) const
/** Gets the entry at the specified iterator position.

@param aMark Iterator to use to get the entry
@param anEntry On return, the specified entry */
	{TBtreeFixBase::ExtractAtL(aMark,&anEntry);}
inline TBtreeFix<TAny,TAny>::TBtreeFix(TBtreeMode aMode,TInt anEntrySize,TInt aKeySize)
	: TBtreeFixBase(aMode,anEntrySize,aKeySize)
/** Constructor that sets the B-tree mode.
	
@param aMode B-tree operating mode
@param anEntrySize Entry size
@param aKeySize Key size for entries */
	{}
inline TBtreeFix<TAny,TAny>::TBtreeFix(const TBtreeToken& aToken,TBtreeMode aMode,TInt anEntrySize,TInt aKeySize)
	: TBtreeFixBase(aToken,aMode,anEntrySize,aKeySize)
/** Constructor that sets the B-tree mode and initialisation parameters.
	
@param aToken Parameters with which to initialise the B-tree
@param aMode B-tree operating mode
@param anEntrySize Entry size
@param aKeySize Key size for entries */
	{}

