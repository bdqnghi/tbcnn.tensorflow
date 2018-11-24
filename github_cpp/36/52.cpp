/*######   Copyright (c) 2014-2015 Ufasoft  http://ufasoft.com  mailto:support@ufasoft.com,  Sergey Pavlov  mailto:dev@ufasoft.com ####
#                                                                                                                                     #
# 		See LICENSE for licensing information                                                                                         #
#####################################################################################################################################*/

#include <el/ext.h>

#include "dblite.h"
#include "b-tree.h"

namespace Ext { namespace DB { namespace KV {


int NumKeys(const Page& page) {
	return page.Header().Num;
}


size_t CalculateLocalDataSize(uint64_t dataSize, size_t cbExtendedPrefix, size_t pageSize) {
	if (dataSize+cbExtendedPrefix > pageSize-3) {
		size_t rem = dataSize % (pageSize-4);
		return rem + cbExtendedPrefix + 4 > (pageSize-3) ? 0 : rem;
	}
	return (size_t)dataSize;
}

LiteEntry *BuildLiteEntryIndex(PageHeader& h, void *raw, int n, size_t pageSize, byte keySize) {
	LiteEntry *entries = (LiteEntry*)raw;
	byte *p = h.Data;
	byte keyOffset = h.KeyOffset();
	if (h.Flags & PageHeader::FLAG_BRANCH) {
		p += 4;
		for (int i=0; i<n; ++i) {
			entries[i].P = p;
			p += (keySize ? keySize-keyOffset : 1 + p[0]) + 4;
		}
	} else {
		byte *q = p;
		for (int i=0; i<n; ++i, q=p) {
			entries[i].P = p;
			p += keySize ? keySize-keyOffset : 1 + p[0];
			uint64_t dataSize = Read7BitEncoded((const byte*&)p);
			size_t cbLocal = CalculateLocalDataSize(dataSize, p-q+h.KeyOffset(), pageSize);
			p += cbLocal + (cbLocal!=dataSize ? 4 : 0);
		}
	}
	entries[n].P = p;
	ASSERT(p - (byte*)&h <= pageSize);
	return entries;
}

LiteEntry *Page::Entries(byte keySize) const {
#ifdef X_DEBUG//!!!D
	if (m_pimpl->Entries) {
		PageHeader& hh = Header();
		LiteEntry *le;
		BuildLiteEntryIndex(hh, le = (LiteEntry*)alloca(sizeof(LiteEntry) * (hh.Num+1)), hh.Num);
		if (memcmp(le, m_pimpl->Entries, sizeof(LiteEntry) * (hh.Num+1)))
			cout << "Error";
	}
#endif

	if (!m_pimpl->aEntries.load()) {
		PageHeader& h = Header();
		LiteEntry *p = BuildLiteEntryIndex(h, Malloc(sizeof(LiteEntry) * (h.Num+1)), h.Num, m_pimpl->View->Storage.PageSize, keySize);
		for (LiteEntry *prev=0; !m_pimpl->aEntries.compare_exchange_weak(prev, p);)
			if (prev) {
				free(p);
				break;
			}
	}
	return m_pimpl->aEntries;
}

#ifdef X_DEBUG//!!!D

void CheckPage(Page& page) {
	PageHeader& h = page.Header();
	LiteEntry *entries = BuildLiteEntryIndex(h, (LiteEntry*)alloca(sizeof(LiteEntry) * (h.Num+1)), h.Num);
	for (int i=0; i<h.Num; ++i) {
		ASSERT(entries[i].PgNo() < 100000);
	}
}

#endif

size_t Page::SizeLeft(byte keySize) const {
	PageHeader& h = Header();
	return m_pimpl->View->Storage.PageSize - (Entries(keySize)[h.Num].P - (byte*)&h);
}

LiteEntry GetLiteEntry(const PagePos& pp, byte keySize) {
	ASSERT(pp.Pos <= pp.Page.Header().Num);

	return pp.Page.Entries(keySize)[pp.Pos];
}

size_t GetEntrySize(const pair<size_t, bool>& ppEntry, size_t ksize, uint64_t dsize) {
	byte buf[10], *p = buf;
	Write7BitEncoded(p, dsize);
	return ppEntry.first + ksize + (p-buf) + (ppEntry.second ? 4 : 0);
}

int Page::FillPercent(byte keySize) {
	LiteEntry *entries = Entries(keySize);
	PageHeader& h = Header();
	int pageSize = m_pimpl->View->Storage.PageSize;
	return h.Num ? int(pageSize - (entries[h.Num].P - h.Data))*100/pageSize : 0;
}

bool Page::IsUnderflowed(byte keySize) {
	return FillPercent(keySize) < FILL_THRESHOLD_PERCENTS;
}

void InsertCell(const PagePos& pagePos, const ConstBuf& cell, byte keySize) {
	Page page = pagePos.Page;
	PageObj& po = *page.m_pimpl;
	if (po.Overflows || page.SizeLeft(keySize) < cell.Size) {
		ASSERT(po.Overflows < size(po.OverflowCells));
		po.OverflowCells[po.Overflows++] = IndexedBuf(cell.P, (uint16_t)cell.Size, (uint16_t)pagePos.Pos);
	} else {
		PageHeader& h = page.Header();
		bool bBranch = h.Flags & PageHeader::FLAG_BRANCH;
		int off = bBranch ? 4 : 0;
		LiteEntry *entries = page.Entries(keySize),
			&e = entries[pagePos.Pos];
		memmove(e.P+cell.Size-off, e.P-off, entries[h.Num++].P-e.P+off);
		memcpy(e.P-off, cell.P, cell.Size);
	}
	page.ClearEntries();
}

// Keeps Entry Index valid on the same memory place
// Returns first overflow page or 0
uint32_t DeleteEntry(const PagePos& pp, byte keySize) {
	PageHeader& h = pp.Page.Header();
	ASSERT(pp.Pos < h.Num);
	LiteEntry *entries = pp.Page.Entries(keySize),
		&e = entries[pp.Pos];
	bool bBranch = pp.Page.IsBranch;
	int r = bBranch || e.DataSize(keySize, h.KeyOffset()) == e.LocalData(pp.Page.m_pimpl->View->Storage.PageSize, keySize, h.KeyOffset()).Size ? DB_EOF_PGNO : e.FirstBigdataPage();
	ssize_t off = e.Size();
	byte *p = e.P - (int(bBranch)*4);
	memmove(p, p+off, entries[h.Num--].P - p - off);
	for (int i=pp.Pos+1, numKeys=h.Num; i<=numKeys; ++i)
		entries[i].P = entries[i+1].P-off;
	return r;
}

// Returns pointer to the RightPtr of the Branch Page
static byte *AssemblePage(Page& page, const ConstBuf cells[], uint16_t n) {
	ASSERT(!page.Overflows);

	PageHeader& h = page.Header();
	h.Num = htole(n);
	byte *p = h.Data;
	for (int i=0; i<n; ++i) {
		const ConstBuf& cell = cells[i];
		memcpy(exchange(p, p+cell.Size), cell.P, cell.Size);
	}
	return p;
}

void BTree::SetRoot(const Page& page) {
	Root = page;
	Dirty = true;
	if (Name == DbTable::Main().Name)
		Tx.MainTableRoot = page;
}

// second arg not used, but present to ensure it exists in memory when reopened by OpenPage()
void BTree::BalanceNonRoot(PagePos& ppParent, Page&, byte *tmpPage) {
	DbTransaction& tx = dynamic_cast<DbTransaction&>(Tx);
	KVStorage& stg = tx.Storage;
	const size_t pageSize = stg.PageSize;
	Page pageParent = ppParent.Page;

	int n = NumKeys(pageParent);
	int	nxDiv = std::max(0, std::min(ppParent.Pos-1, n-2+int(tx.Bulk)));
	n = std::min(2-int(tx.Bulk), n);
	vector<Page> oldPages(n+1);
	vector<ConstBuf> dividers(n);
	LiteEntry *entriesParent = pageParent.Entries(KeySize);
	byte *tmp = tmpPage;
	int nEstimatedCells = 0;
	for (int i=oldPages.size()-1; i>=0; --i) {
		LiteEntry& e = entriesParent[nxDiv+i];
		Page& page = oldPages[i] = tx.OpenPage(e.PgNo());
		nEstimatedCells += NumKeys(page)+page.Overflows+1;
		if (i != oldPages.size()-1) {
			size_t cbEntry = e.Size();
			memcpy(tmp, e.P-4, cbEntry);
			dividers[i] = ConstBuf(tmp, cbEntry);
			tmp += cbEntry;
			DeleteEntry(PagePos(pageParent, nxDiv+i), KeySize);
		}
	}
	bool bBranch = oldPages.front().IsBranch;

	struct PageInfo {
		size_t UsedSize;
		int Count;
		Ext::DB::KV::Page Page;

		PageInfo(size_t usedSize = 0, int count = 0)
			:	UsedSize(usedSize)
			,	Count(count)		
		{}
	};
	AlignedMem memTmp((oldPages.size()+1)*pageSize, 64);
	vector<ConstBuf> cells;
	cells.reserve(nEstimatedCells);
	byte *pTemp = (byte*)memTmp.get()+oldPages.size()*pageSize;
	uint32_t pgnoRight = 0;
	byte keyOffset = pageParent.Header().KeyOffset();
	for (int i=0; i<oldPages.size(); ++i) {
		Page& page = oldPages[i];
		PageHeader& h = page.Header();
//!!!R		keyOffset = h.KeyOffset();
		LiteEntry *entries = page.Entries(KeySize);
		PageObj& po = *page.m_pimpl;
		ASSERT(po.Dirty || !po.Overflows);

		if (po.Dirty) {
			PageHeader& hd = *(PageHeader*)((byte*)memTmp.get()+i*stg.PageSize);
			MemcpyAligned32(&hd, &h, entries[h.Num].P - (byte*)&h);
			ssize_t off = (byte*)&hd - (byte*)&h;
			for (int i=0, n=h.Num; i<=n; ++i)
				entries[i].P += off;
		}
		for (int k=0, n=NumKeys(page) + po.Overflows, idx; (idx=k)<n; ++k) {
			ConstBuf cell;
			for (int j=int(po.Overflows)-1; j>=0; --j) {
				IndexedBuf& ib = po.OverflowCells[j];
				if (idx == ib.Index) {
					cell = ConstBuf(ib.P, ib.Size);
					goto LAB_FOUND;
				} else if (idx > ib.Index)
					--idx;
			}
			{
				LiteEntry& e = entries[idx];
				cell = ConstBuf(e.P-int(bBranch)*4, e.Size());
			}
LAB_FOUND:
			cells.push_back(cell);
		}
		po.Overflows = 0;
		if (bBranch) {
			uint32_t pgno = entries[h.Num].PgNo();
			if (i == oldPages.size()-1)
				pgnoRight = pgno;
			else {
				PutLeUInt32(pTemp, pgno);
				ConstBuf& div = dividers[i];
				memcpy(pTemp+4, div.P+4, div.Size-4);
				cells.push_back(ConstBuf(pTemp, div.Size));
				pTemp += div.Size;
			}
		}
		if (po.Dirty)
			page.ClearEntries();
	}
	ASSERT(!cells.empty());
	
	vector<PageInfo> newPages;
	const size_t cbUsable = stg.PageSize-3-int(bBranch)*4;
	size_t cbPage = 0;
	int iCell = 0;
	for (; iCell<cells.size(); ++iCell) {
		size_t cb = cells[iCell].Size;
		if (cbPage+cb > cbUsable) {
			newPages.push_back(PageInfo(exchange(cbPage, 0), iCell));
			iCell -= (int)(!bBranch);
		} else
			cbPage += cb;
	}
	newPages.push_back(PageInfo(exchange(cbPage, 0), iCell));

	for (int i=newPages.size()-1; i>0; --i) {
		size_t &cbRight = newPages[i].UsedSize,
			&cbLeft = newPages[i-1].UsedSize;
		int& cnt = newPages[i-1].Count;
		while (true) {
			int r = cnt - 1,
				d = r + 1 - (bBranch ? 0 : 1);
			if (cbRight!=0 && (tx.Bulk || cbRight+cells[d].Size > cbLeft-cells[r].Size))
				break;
			cbRight += cells[d].Size;
			cbLeft -= cells[r].Size;
			--cnt;
		}
	}

	for (int i=0; i<newPages.size(); ++i) {
		for (vector<Page>::iterator it=oldPages.begin(); it!=oldPages.end(); ++it) {
			if (it->Dirty) {
				ASSERT(!it->m_pimpl->aEntries.load());

				newPages[i].Page = *it;
				oldPages.erase(it);
				break;
			}
		}
		if (!newPages[i].Page) {
			newPages[i].Page = tx.Allocate(bBranch ? PageAlloc::Branch : PageAlloc::Leaf);
			newPages[i].Page.Header().SetKeyOffset(keyOffset);
		}
	}

	//!!!TODO Sort pgnos

	entriesParent[nxDiv].PutPgNo(newPages.back().Page.N);
	
	int j = 0;
	tmp = tmpPage;	
	for (int i=0; i<newPages.size(); ++i) {
		Page& page = newPages[i].Page;
		ASSERT(!page.Overflows);

		int nj = newPages[i].Count;
		byte *pRight = AssemblePage(page, &cells[j], uint16_t(nj-j));
		j = nj;

		ASSERT(i<newPages.size()-1 || j==cells.size());
		if (j < cells.size()) {
			ConstBuf div = cells[j];
			if (bBranch) {
				memcpy(pRight, div.P, 4);
				++j;
			} else {
				div.Size = 4 + (KeySize ? KeySize-keyOffset : 1+div.P[0]);
				div.P -= 4;
			}
			PutLeUInt32(tmp, page.N);
			memcpy(tmp+4, div.P+4, div.Size-4);
			InsertCell(PagePos(pageParent, nxDiv++), ConstBuf(tmp, div.Size), KeySize);
			tmp += div.Size;
		}
		if (bBranch && i==newPages.size()-1)
			PutLeUInt32(pRight, pgnoRight);
	}

	for (int i=0; i<oldPages.size(); ++i)						// non-Dirty oldPages contain used Data, so free them only after copying to newPages
		tx.FreePage(oldPages[i]);

	if (pageParent==Root && 0==NumKeys(pageParent)) {
		ASSERT(newPages.size() == 1);
		tx.FreePage(Root);
		SetRoot(newPages[0].Page);
	}
}

void BTreeCursor::Balance() {
	if (Path.empty())
		return;
	Page& page = Top().Page;
	if (Path.size() == 1) {
		if (!page.Overflows)
			return;
		Tree->SetRoot(dynamic_cast<DbTransaction&>(Tree->Tx).Allocate(PageAlloc::Branch));
		Tree->Root.Header().SetKeyOffset(page.Header().KeyOffset());
		PutLeUInt32(Tree->Root.Header().Data, page.N);
		Path.insert(Path.begin(), PagePos(Tree->Root, 0));
	} else if (!page.Overflows && !page.IsUnderflowed(Tree->KeySize))
		return;
	Initialized = false;
	Blob blobDivs(0, Tree->Tx.Storage.PageSize);										// should be in dynamic scope during one nested call of Balance()
	Tree->BalanceNonRoot(Path[Path.size()-2], Path.back().Page, blobDivs.data());
	Path.back().Page.m_pimpl->Overflows = 0;
	Path.pop_back();
	Balance();
}

void BTreeCursor::Delete() {
	base::Delete();
	Tree->Tx.m_bError = true;
	Balance();
	Tree->Tx.m_bError = false;
}

int PagedMap::Compare(const void *p1, const void *p2, size_t cb2) {
	size_t cb1 = ((const byte*)p1)[-1];
	int r = memcmp(p1, p2, std::min(cb1, cb2));
	return r ? r
		     : (cb1 < cb2 ? -1 : cb1==cb2 ? 0 : 1);
}

pair<size_t, bool> PagedMap::GetDataEntrySize(const ConstBuf& k, uint64_t dsize) const {
	size_t pageSize = Tx.Storage.PageSize;
	byte buf[10], *p = buf;
	Write7BitEncoded(p, dsize);
	size_t cbExtendedPrefix = (KeySize ? KeySize : 1+k.Size) + (p-buf);
	return make_pair(CalculateLocalDataSize(dsize, cbExtendedPrefix, pageSize), cbExtendedPrefix+dsize > pageSize-3);		//!!!?
}

pair<int, bool> PagedMap::EntrySearch(LiteEntry *entries, PageHeader& h, const ConstBuf& k) {
	ConstBuf kk(k.P+h.KeyOffset(), k.Size-h.KeyOffset());
	int rc = 0;
	int b = 0;
	for (int count=h.Num, m, half; count;) {
		ConstBuf nk = entries[m = b+(half=count/2)].Key(KeySize);
		if (!(rc = m_pfnCompare(nk.P, kk.P, kk.Size)))
			return make_pair(m, true);
		else if (rc < 0) {
			b = m + 1;
			count -= half + 1;
		} else
			count = half;
	}	
	return make_pair(b, false);
}

EntryDesc PagedMap::GetEntryDesc(const PagePos& pp) {
	PageHeader& h = pp.Page.Header();
	ASSERT(!(h.Flags & PageHeader::FLAG_BRANCH) && pp.Pos<h.Num);
	LiteEntry *entries = pp.Page.Entries(KeySize),
		&e = entries[pp.Pos];

	EntryDesc r;
	r.P = e.P;
	r.Size = e.Size();
	size_t pageSize = pp.Page.m_pimpl->View->Storage.PageSize;
	r.DataSize = e.DataSize(KeySize, h.KeyOffset());
	r.LocalData = e.LocalData(pageSize, KeySize, h.KeyOffset());
	r.PgNo = (r.Overflowed = r.DataSize >= pageSize || r.LocalData.P+r.DataSize!=e.Upper()) ? e.FirstBigdataPage() : 0;
	return r;
}

void CursorObj::DeepFreePage(const Page& page) {
	DbTransaction& tx = dynamic_cast<DbTransaction&>(Map->Tx);
	if (page.IsBranch) {
		LiteEntry *entries = page.Entries(Map->KeySize);
		for (int i=0, n=NumKeys(page); i<=n; ++i)
			DeepFreePage(tx.OpenPage(entries[i].PgNo()));
	} else {
		for (int i=0, n=NumKeys(page); i<n; ++i)
			FreeBigdataPages(Map->GetEntryDesc(PagePos(page, i)).PgNo);
	}
	tx.FreePage(page);
}

#pragma intrinsic(memcmp)


BTreeCursor::BTreeCursor()
	:	Path(4)
{
}

int BTreeCursor::CompareEntry(LiteEntry *entries, int idx, const ConstBuf& kk) {
	int rc = Tree->m_pfnCompare(entries[idx].Key(Tree->KeySize).P, kk.P, kk.Size);
	if (!rc)
		ReturnFromSeekKey(idx);
	return rc;
}

bool BTreeCursor::SeekToKey(const ConstBuf& k) {
	if (Tree->KeySize && Tree->KeySize!=k.Size)
		Throw(errc::invalid_argument);
	ASSERT(k.Size>0 && k.Size <= KVStorage::MAX_KEY_SIZE);

	if (Initialized) {
		Page& page = Top().Page;
		PageHeader& h = page.Header();
		if (0 == h.Num) {
			Top().Pos = 0;
			return false;
		}
		ConstBuf kk(k.P+h.KeyOffset(), k.Size-h.KeyOffset());
		LiteEntry *entries = page.Entries(Tree->KeySize);
		int rc = CompareEntry(entries, 0, kk);
		if (!rc)
			return true;
		if (rc < 0) {
			if (h.Num > 1) {
				if (!(rc = CompareEntry(entries, h.Num-1, kk)))
					return true;
				if (rc > 0) {
					if (Top().Pos<h.Num && !CompareEntry(entries, Top().Pos, kk))
						return true;
					goto LAB_ENTRY_SEARCH;
				}
			}
			for (int i=0; i<Path.size()-1; ++i)
				if (Path[i].Pos < NumKeys(Path[i].Page)-1)
					goto LAB_SOME_PARENT_HAVE_RIGHT_SIB;
			Top().Pos = h.Num;
			return false;
		}
LAB_SOME_PARENT_HAVE_RIGHT_SIB:
		if (Path.size() < 2) {
			Top().Pos = 0;
			return false;
		}
	}

	if (!PageSearch(k))
		return false;
LAB_ENTRY_SEARCH:
	Page& page = Top().Page;
	ASSERT(!page.IsBranch);

	LiteEntry *entries = page.Entries(Tree->KeySize);
	pair<int, bool> pp = Tree->EntrySearch(entries, page.Header(), k);	// bBranch=false
	Top().Pos = pp.first;
	if (!pp.second)
		return false;
	Eof = false;
		
#ifdef X_DEBUG//!!!D
	ASSERT(Top().Pos < NumKeys(Top().Page));
#endif
	return Initialized = ClearKeyData();
}

bool BTreeCursor::SeekToSibling(bool bToRight) {
	if (Path.size() <= 1)
		return false;
	Path.pop_back();
	PagePos& pp = Top();
	if (bToRight ? pp.Pos+1<=NumKeys(pp.Page) : pp.Pos>0)
		pp.Pos += bToRight ? 1 : -1;
	else if (!SeekToSibling(bToRight))
		return false;	
	ASSERT(Top().Page.IsBranch);	
	Path.push_back(PagePos(Tree->Tx.OpenPage(Top().Page.Entries(Tree->KeySize)[Top().Pos].PgNo()), 0));
	return true;
}

void BTreeCursor::InsertImp(ConstBuf k, const ConstBuf& d) {
	pair<size_t, bool> ppEntry = Tree->GetDataEntrySize(k, d.Size);
	InsertImpHeadTail(ppEntry, k, d, d.Size, DB_EOF_PGNO);
}

void BTreeCursor::Put(ConstBuf k, const ConstBuf& d, bool bInsert) {
	bool bExists = false;
	if (!Tree->Root) {
		Page pageRoot = dynamic_cast<DbTransaction&>(Tree->Tx).Allocate(PageAlloc::Leaf);
		Tree->SetRoot(pageRoot);
		Path.push_back(PagePos(pageRoot, 0));
		Initialized = true;
	} else {
		bExists = SeekToKey(k);
		if (bExists && bInsert)
			throw DbException(ExtErr::DB_DupKey, nullptr);
		ASSERT(!bExists || Top().Pos < NumKeys(Top().Page));
		Touch();
		if (bExists) {
			PagePos& pp = Top();
			EntryDesc e = Tree->GetEntryDesc(pp);
			if (!e.Overflowed && d.Size == e.DataSize) {
				memcpy((byte*)e.LocalData.P, d.P, d.Size);
				return;
			}
			FreeBigdataPages(DeleteEntry(pp, Tree->KeySize));
		}
	}
	InsertImp(k, d);
}

void BTreeCursor::PushFront(ConstBuf k, const ConstBuf& d) {
	if (Tree->Tx.ReadOnly)
		Throw(errc::permission_denied);
	ASSERT(k.Size <= KVStorage::MAX_KEY_SIZE && (!Tree->KeySize || Tree->KeySize==k.Size));
	bool bExists = false;
	if (!Tree->Root) {
		Page pageRoot = dynamic_cast<DbTransaction&>(Tree->Tx).Allocate(PageAlloc::Leaf);
		Tree->SetRoot(pageRoot);
		Path.push_back(PagePos(pageRoot, 0));
		Initialized = true;
	} else {
		bExists = SeekToKey(k);
		ASSERT(!bExists || Top().Pos < NumKeys(Top().Page));
		Touch();
		if (bExists) {
			PagePos& pp = Top();
			EntryDesc e = Tree->GetEntryDesc(pp);
			size_t pageSize = Tree->Tx.Storage.PageSize;
			pair<size_t, bool> ppEntry;
			if (!e.Overflowed ||
				e.LocalData.Size != e.DataSize % (pageSize-4) ||
				(ppEntry = Tree->GetDataEntrySize(k, d.Size+e.DataSize)).first == 0)
			{
				Blob newdata = d + get_Data();
				FreeBigdataPages(DeleteEntry(pp, Tree->KeySize));
				InsertImp(k, newdata);
				return;
			}
			Blob head = d + e.LocalData;
			ASSERT(ppEntry.second && ppEntry.first==head.Size%(pageSize-4) && ppEntry.first==(d.Size+e.DataSize)%(pageSize-4));
			DeleteEntry(pp, Tree->KeySize);
			InsertImpHeadTail(ppEntry, k, head, d.Size+e.DataSize, e.PgNo);
			return;
		}
	}
	InsertImp(k, d);
}

void BTreeCursor::Drop() {
	if (Tree->Root) {
		DeepFreePage(Tree->Root);
		Tree->SetRoot(nullptr);
	}
}

void static CopyPage(Page& pageFrom, Page& pageTo, byte keySize) {
	PageHeader& h = pageFrom.Header();
	LiteEntry *entries = pageFrom.Entries(keySize);
	
	size_t size = entries[h.Num].P - (byte*)&h;
	MemcpyAligned32(pageTo.Address, pageFrom.Address, size);
#ifdef X_DEBUG//!!!D
	memset((byte*)pageTo.Address+size, 0xFE, pageFrom.m_pimpl->Storage.PageSize-size);
#endif

	LiteEntry *dEntries = pageTo.m_pimpl->aEntries = (LiteEntry*)Ext::Malloc(sizeof(LiteEntry)*(h.Num+1));
	ssize_t off = (byte*)pageTo.get_Address() - (byte*)pageFrom.get_Address();
	for (int i=0, n=h.Num; i<=n; ++i)
		dEntries[i].P = entries[i].P+off;
}

void BTreeCursor::PageTouch(int height) {
	Page& page = Path[height].Page;
	DbTransaction& tx = dynamic_cast<DbTransaction&>(Tree->Tx);
	if (!page.Dirty) {
		Page np = tx.Allocate(page.IsBranch ? PageAlloc::Branch : PageAlloc::Leaf);
		CopyPage(page, np, Tree->KeySize);
		tx.FreePage(page);

		int t = Path.size()-1;
		EXT_FOR (CursorObj& co, Tree->Cursors) {
			BTreeCursor& c = dynamic_cast<BTreeCursor&>(co);
			if (&c != this && c.Path.size() > t && c.Path[t].Page == page)
				c.Path[t].Page = np;
		}
		page = np;
		if (height)
			GetLiteEntry(Path[height-1], Tree->KeySize).PutPgNo(page.N);
		else
			Tree->SetRoot(page);
	}
}

void BTreeCursor::Touch() {
	if (Tree->Name != DbTable::Main().Name) {
		DbCursor cM(Tree->Tx, DbTable::Main());
		BTreeCursor *btreeCursor = dynamic_cast<BTreeCursor*>(cM.m_pimpl.get());
		if (!btreeCursor->PageSearch(ConstBuf(Tree->Name.c_str(), strlen(Tree->Name.c_str())), true))
			Throw(E_FAIL);
		Tree->Dirty = true;
	}
	for (int i=0; i<Path.size(); ++i)
		PageTouch(i);
}

bool BTreeCursor::PageSearchRoot(const ConstBuf& k, bool bModify) {
	while (true) {
		Page& page = Path.back().Page;
		PageHeader& h = page.Header();
		if (!(h.Flags & PageHeader::FLAG_BRANCH))
			return true;
		LiteEntry *entries = page.Entries(Tree->KeySize);

		int i = 0;
		if (k.Size > MAX_KEY_SIZE)
			i = h.Num;
		else if (k.P) {
			pair<int, bool> pp = Tree->EntrySearch(entries, h, k);		// bBranch=true
			i = pp.second ? pp.first+1 : pp.first;
		}
		Path.back().Pos = i;
		Path.push_back(PagePos(Tree->Tx.OpenPage(entries[i].PgNo()), 0));
		ASSERT(Path.size() < 10);
		if (bModify)
			PageTouch(Path.size()-1);
	}
}

bool BTreeCursor::PageSearch(const ConstBuf& k, bool bModify) {
	if (Tree->Tx.m_bError)
		Throw(E_FAIL);

	if (!Tree->Root)
		return false;

	if (Tree->Name != DbTable::Main().Name && bModify && !IsDbDirty) {
		DbCursor cMain(Tree->Tx, DbTable::Main());
		BTreeCursor *btreeCursor = dynamic_cast<BTreeCursor*>(cMain.m_pimpl.get());
		const char *name = Tree->Name;
		if (!btreeCursor->PageSearch(ConstBuf(name, strlen(name)), bModify))
			Throw(E_FAIL);
		IsDbDirty = bModify;
	}

	Path.resize(1);
	Path[0] = PagePos(Tree->Root, 0);
	if (bModify)
		PageTouch(0);
	return PageSearchRoot(k, bModify);
}

bool BTreeCursor::SeekToFirst() {
	if (!Initialized || Path.size() > 1) {
		if (!PageSearch(ConstBuf()))
			return false;
	}
	ASSERT(!Top().Page.IsBranch);
	Top().Pos = 0;
	return Initialized = ClearKeyData();
}

bool BTreeCursor::SeekToLast() {
	if (!Eof) {
		if (!Initialized || Path.size() > 1) {
			if (!PageSearch(ConstBuf(0, INT_MAX)))
				return false;
		}
		ASSERT(!Top().Page.IsBranch);
		Top().Pos = NumKeys(Top().Page)-1;
		Initialized = Eof = true;
	}
	return ClearKeyData();
}

}}} // Ext::DB::KV::

