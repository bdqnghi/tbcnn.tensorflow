#include "rts/segment/BTree.hpp"










namespace BTreeLogActions {


static const unsigned innerHeaderSize = 24;

LOGACTION2DEF(BTree,UpdateInnerPage,LogData,oldEntry,LogData,newEntry);

void UpdateInnerPage::redo(void* page) const { memcpy(static_cast<unsigned char*>(page)+8,newEntry.ptr,newEntry.len); }
void UpdateInnerPage::undo(void* page) const { memcpy(static_cast<unsigned char*>(page)+8,oldEntry.ptr,oldEntry.len); }

LOGACTION3DEF(BTree,UpdateInner,uint32_t,slot,LogData,oldEntry,LogData,newEntry);

void UpdateInner::redo(void* page) const {
   unsigned entrySizeInner=newEntry.len;
   memcpy(static_cast<unsigned char*>(page)+innerHeaderSize+(entrySizeInner*slot),newEntry.ptr,newEntry.len);
}
void UpdateInner::undo(void* page) const {
   unsigned entrySizeInner=newEntry.len;
   memcpy(static_cast<unsigned char*>(page)+innerHeaderSize+(entrySizeInner*slot),oldEntry.ptr,oldEntry.len);
}

LOGACTION2DEF(BTree,InsertInner,uint32_t,slot,LogData,newEntry);

void InsertInner::redo(void* page) const {
   unsigned entrySizeInner=newEntry.len;
   unsigned oldCount=Segment::readUint32Aligned(static_cast<unsigned char*>(page)+16);
   memmove(static_cast<unsigned char*>(page)+innerHeaderSize+(entrySizeInner*(slot+1)),static_cast<unsigned char*>(page)+innerHeaderSize+(entrySizeInner*slot),entrySizeInner*(oldCount-slot));
   memcpy(static_cast<unsigned char*>(page)+innerHeaderSize+(entrySizeInner*slot),newEntry.ptr,newEntry.len);
   Segment::writeUint32Aligned(static_cast<unsigned char*>(page)+16,oldCount+1);
}
void InsertInner::undo(void* page) const {
   unsigned entrySizeInner=newEntry.len;
   unsigned oldCount=Segment::readUint32Aligned(static_cast<unsigned char*>(page)+16);
   memmove(static_cast<unsigned char*>(page)+innerHeaderSize+(entrySizeInner*slot),static_cast<unsigned char*>(page)+innerHeaderSize+(entrySizeInner*(slot+1)),entrySizeInner*(oldCount-slot-1));
   Segment::writeUint32Aligned(static_cast<unsigned char*>(page)+16,oldCount-1);
}

LOGACTION2DEF(BTree,UpdateLeaf,LogData,oldContent,LogData,newContent);

void UpdateLeaf::redo(void* page) const { memcpy(static_cast<unsigned char*>(page)+8,newContent.ptr,newContent.len); }
void UpdateLeaf::undo(void* page) const { memcpy(static_cast<unsigned char*>(page)+8,oldContent.ptr,oldContent.len); }

};


