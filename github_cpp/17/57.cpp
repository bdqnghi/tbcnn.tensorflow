
#ifndef OCEANBASE_COMMON_BTREE_BTREE_BASE_H_
#define OCEANBASE_COMMON_BTREE_BTREE_BASE_H_

#include "btree_define.h"
#include "btree_default_alloc.h"
#include "btree_root_pointer.h"
#include "btree_read_handle_new.h"
#include "btree_write_handle.h"

namespace oceanbase
{
  namespace common
  {

    

    class BtreeReadParam;
    class BtreeWriteParam;
    class BtreeRootPointer;
    class BtreeNode;
    class BtreeBase : public BtreeCallback
    {
      friend class BtreeWriteHandle;
    public:
      
      static const char *MIN_KEY;
      
      static const char *MAX_KEY;
      
      static const int32_t MAX_RECYCLE_ROOT_COUNT;
      
      static const int64_t RECYCLE_MASK;
      static const int64_t REFCOUNT_MASK;

    public:
      
      BtreeBase(BtreeAlloc *allocator = NULL);

      
      virtual ~BtreeBase();

      
      int32_t get_read_handle(BtreeBaseHandle &handle);

      
      int32_t get_write_handle(BtreeWriteHandle &handle);

      
      int64_t get_object_count();

      
      int32_t get_node_count();

      
      int64_t get_alloc_count();
      
      int32_t get_alloc_memory();
      
      int32_t get_freelist_size();
      
      void clear();
      
      void set_write_lock_enable(int32_t enable);
      
      void destroy();

#ifdef OCEAN_BASE_BTREE_DEBUG
      
      void print(BtreeBaseHandle *handle);
#endif
    protected:
      
      BtreeKeyValuePair *get_one_pair(BtreeBaseHandle &handle, const int32_t tree_id, const char *key);

      
      BtreeKeyValuePair *get_range_pair(BtreeReadHandle &handle);

      
      int32_t put_pair(BtreeWriteHandle &handle, const char *key, const char *value, const bool overwrite);

      
      int32_t remove_pair(BtreeWriteHandle &handle, const int32_t tree_id, const char *key);

    protected:
      
      int32_t tree_count_;
      
      BtreeKeyCompare *key_compare_[CONST_MAX_BTREE_COUNT];
      
      BtreeAlloc *key_allocator_;

    private:
      
      int32_t get_children(BtreeRootPointer *proot, const int32_t tree_id, const char *key, BtreeReadParam &param);
      
      int32_t copy_node_for_write(BtreeWriteHandle &handle, BtreeWriteParam &param);
      
      int32_t add_pair_to_node(BtreeWriteHandle &handle, BtreeWriteParam& param, int32_t level, const char *key, const char *value);
      
      BtreeNode* copy_next_node_for_write(BtreeWriteHandle &handle, BtreeWriteParam& param, int32_t level);
      
      int32_t remove_pair_from_node(BtreeWriteHandle &handle, BtreeWriteParam& param, int32_t level, int32_t next_pos);
      
      void update_parent_first_key(BtreeWriteHandle &handle, BtreeWriteParam& param, int32_t level);
      
      int32_t pos_move_next(BtreeReadParam *param, int32_t direction);
      
      void update_key_ref_count(BtreeWriteHandle &handle, char *old_key, char *new_key);
      
      int callback_done(void *data);
      
      void remove_allnode(BtreeWriteHandle &handle, BtreeNode *root, int32_t depth, int32_t level);

    private:
      
      BtreeRootPointer empty_root_pointer_;
      
      BtreeRootPointer *root_pointer_;
      
      BtreeRootPointer *root_tail_;
      
      BtreeRootPointer *root_recycle_;
      
      pthread_mutex_t mutex_;
      pthread_mutex_t *wl_mutex_;
      
      BtreeAlloc *node_allocator_;
      BtreeDefaultAlloc node_default_allocator_;
      
      int64_t proot_sequence_;
      
      BtreeRootPointerList proot_freelist_;
    };

  } 
} 

#endif


