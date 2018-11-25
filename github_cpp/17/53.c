















inline TBtreeToken::TBtreeToken(TEmpty)

	{Clear();}
inline void TBtreeToken::Touch()

	{iHeight=0;}
inline TBool TBtreeToken::IsBroken() const

	{return iFirst!=KNullPageRef&&iHeight==0;}
inline TBool TBtreeToken::IsIntact() const

	{return iFirst==KNullPageRef||iHeight!=0;}
inline TBool TBtreeToken::IsEmpty() const

	{return iFirst==KNullPageRef;}


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


inline TBool TBtree::IsDirty() const

	{return iStatus<0;}
inline void TBtree::MarkCurrent()

	{iStatus&=~EDirty;}
inline void TBtree::MarkDirty()

	{iStatus|=EDirty;}
inline TBool TBtree::IsBroken() const

	{return (iStatus&EBroken)!=0;}
inline TBool TBtree::IsIntact() const

	{return (iStatus&EBroken)==0;}
inline void TBtree::MarkBroken()

	{if (iFirst!=KNullPageRef) iStatus|=EBroken;}
inline TBool TBtree::IsEmpty() const

	{return iFirst==KNullPageRef;}


template <class Entry,class Key>
inline TBtreeFix<Entry,Key>::TBtreeFix(TBtreeMode aMode)
	: TBtreeFixBase(aMode,sizeof(Entry),sizeof(Key))

	{}
template <class Entry,class Key>
inline TBtreeFix<Entry,Key>::TBtreeFix(const TBtreeToken& aToken,TBtreeMode aMode)
	: TBtreeFixBase(aToken,aMode,sizeof(Entry),sizeof(Key))

	{}
template <class Entry,class Key>
inline TBool TBtreeFix<Entry,Key>::FindL(TBtreePos& aPos,const Key& aKey,TBtree::TFind aMode) const
	{return TBtreeFixBase::FindL(aPos,&aKey,aMode);}
template <class Entry,class Key>
inline TBool TBtreeFix<Entry,Key>::InsertL(TBtreePos& aPos,const Entry& anEntry,TAllowDuplicates aDup)

	{return TBtreeFixBase::InsertL(aPos,&anEntry,aDup);}
template <class Entry,class Key>
inline TBool TBtreeFix<Entry,Key>::DeleteL(const Key& aKey)

	{return TBtreeFixBase::DeleteL(&aKey);}
template <class Entry,class Key>
inline Entry TBtreeFix<Entry,Key>::AtL(const TBtreePos& aPos) const

	{Entry e;TBtreeFixBase::ExtractAtL(aPos,&e);return e;}
template <class Entry,class Key>
inline Entry TBtreeFix<Entry,Key>::AtL(const TBtreeMark& aMark) const

	{Entry e;TBtreeFixBase::ExtractAtL(aMark,&e);return e;}
template <class Entry,class Key>
inline void TBtreeFix<Entry,Key>::ExtractAtL(const TBtreePos& aPos,Entry& anEntry) const

	{TBtreeFixBase::ExtractAtL(aPos,&anEntry);}
template <class Entry,class Key>
inline void TBtreeFix<Entry,Key>::ExtractAtL(const TBtreeMark& aMark,Entry& anEntry) const

	{TBtreeFixBase::ExtractAtL(aMark,&anEntry);}
inline TBtreeFix<TAny,TAny>::TBtreeFix(TBtreeMode aMode,TInt anEntrySize,TInt aKeySize)
	: TBtreeFixBase(aMode,anEntrySize,aKeySize)

	{}
inline TBtreeFix<TAny,TAny>::TBtreeFix(const TBtreeToken& aToken,TBtreeMode aMode,TInt anEntrySize,TInt aKeySize)
	: TBtreeFixBase(aToken,aMode,anEntrySize,aKeySize)

	{}

