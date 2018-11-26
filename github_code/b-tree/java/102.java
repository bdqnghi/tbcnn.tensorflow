package com.demo.mina;

import java.util.ArrayDeque;
import java.util.Queue;

 
/**
 * 
 * KeyEntry表示B+Tree页面中的Key元素
 * 
 *@author whw 
 */
class KeyEntry{ 
	
	/**
	 * 这里暂时用认为key为整数
	 */
	int key;
	/**
	 * 如果包含此entry的页面是叶子节点则child指向具体记录，
	 * 否则表示指向小于key的子页面
	 */	
	Object child;	
}

/**
 * 
 *  Page表示B+Tree中的页面，一个页面可以存储若干Key
 * 
 * @author whw
 *
 */
class Page{
	
	//public static int PAGE_SIZE = 1024 * 16;
	/**
	 * 页面类型
	 */
	/** 根节点，且是叶子节点 */
	public static int PAGE_TYPE_ROOT_LEAF = 1;
	/** 根节点，有子节点*/
	public static int PAGE_TYPE_ROOT_NOLEAF = 2;
	/** 内部 节点，即非根节点和叶子节点*/
	public static int PAGE_TYPE_INTERNAL = 3;
	/** 叶子节点，但非根节点 */
	public static int PAGE_TYPE_LEAF = 4; 
	
	/**
	 * 一个页面中可以存储的最大的KeyEntry个数 
	 */
	public static int MAX_ENTRY_NUM = 4; 
	
	/**
	 * 页面类型
	 */
	public int type;	
	
	public int nKeys;	
	
	public KeyEntry[] entrys; 
	
	public Page parent;	
	
	public Page(){		 
		entrys = new KeyEntry[MAX_ENTRY_NUM+1];
	} 
}

/**
 * 
 * 
 * @author whw
 *
 */
public class BTree {

	public Page root;
	
	
	public void createBtree(){ 
		root = new Page();		 
		root.type = Page.PAGE_TYPE_ROOT_LEAF;
		root.nKeys = 0;
		root.parent = null;
	}
    /**
     * 
     * @return true 插入到了page的第一个位置，否则false
     */
	public boolean  putRecord(Page page, KeyEntry entry){
		
		//如果当前page为空，则直接加入		
		if(page.nKeys == 0){
			page.entrys[0] = entry;
			page.nKeys++;
			return false;
		}else{
			//当前记录不为空 
			//不存在，则按从大到小的顺序插入
			//首先找到插入点.暂时不用折半查找法
			
			int j = page.nKeys -1;
			for ( ; j >=0 ; j--) {
				KeyEntry temp = page.entrys[j];
				if(entry.key == temp.key){			
					//断是否entry的key是否已经存在，存在则更新
					page.entrys[j] = entry;					 
					return false;
				}else if( entry.key > temp.key ){					
					j++;
					break;
				}else{
					page.entrys[j+1] = page.entrys[j];
				}
			} 
			page.nKeys++;
			if(j == -1){
				//小于第一个元素， 
				page.entrys[0] = entry;
				return true;
			}else{
				page.entrys[j] = entry;			
				return false;
			}
	 
		} 
	}
	/**
	 * 从包含此key的记录上移除record,
	 * @param key
	 * @param page
	 */
	public void fakeRemoveRecord(int key, Page page){
		
		for (int i = 0; i < page.nKeys; i++) {
			
			if(key == page.entrys[i].key){
				page.entrys[i].child = null;
				break;
			}
		}
	}
	
	public void realRemoveRecord(int removeKey, Page page){
		
		int i = 0;
		//首先查找key为removekey的entry的索引
		for ( ; i < page.nKeys; i++) {			
			if(removeKey == page.entrys[i].key){				 
				break;
			}			
		} 
		
		//根据页面类型进行删除和调整		
		if(page.type == Page.PAGE_TYPE_ROOT_LEAF){
			//允许的范围1-Page.MAX_ENTRY_NUM 			
			for( int j = i+1; j < page.nKeys; j++){
				page.entrys[j-1] = page.entrys[j];
			} 
			return;
		}else if (page.type == Page.PAGE_TYPE_ROOT_NOLEAF) {
				
				//判断entry个数是否为2，
				if(page.nKeys <= 2){
					//如果根节点的元素个数为2，则删除后剩一个元素，则直接删除根节点，用起子节点代替
					if(i == 0){
						root = (Page) page.entrys[1].child;
					}else {
						root = (Page) page.entrys[0].child;
					}
				}else{
					
					page.entrys[i].child = null;
					
					for( int j = i; j < page.nKeys - 1; j++){
						page.entrys[j] = page.entrys[j+1];
					} 
					
					page.entrys[page.nKeys - 1] = null;
					page.nKeys--;
				}
			
		}else if (page.type == Page.PAGE_TYPE_LEAF || page.type == Page.PAGE_TYPE_INTERNAL) {
			//允许的范围Page.MAX_ENTRY_NUM/2-Page.MAX_ENTRY_NUM
			//判断删除后当前页面是否大于等于Page.MAX_ENTRY_NUM/2
			if(page.nKeys > Page.MAX_ENTRY_NUM/2){
				
				for( int j = i+1; j < page.nKeys; j++){
					page.entrys[j-1] = page.entrys[j];
				} 
				page.nKeys--;
				page.entrys[page.nKeys] = null;
				
				//如果是第一个元素，需要进行调整，不是则不需要调整	
				if(i == 0 && page.parent != null){
					adjust_min_key(page);
				}
			}else {
				//此时,删除后entry数将少于Page.MAX_ENTRY_NUM/2，因此需要进行调整
				
				//首先需要判断父页面上指向此page的key是否是父页面的第一个元素
				boolean first_entry = isFirstSubPage(page);				 
				if(first_entry == true){
					
					Page rightPage = getRightSibling(page);
					if( rightPage.nKeys > Page.MAX_ENTRY_NUM/2){
						//向右兄弟借一个元素来平衡自己；
						for( int j = i; j < page.nKeys - 1; j++){
							page.entrys[j] = page.entrys[j+1];
						} 
						
						page.entrys[page.nKeys - 1] = rightPage.entrys[0];
						
						for (int k = 0; k < rightPage.nKeys -1; k++) {
							rightPage.entrys[k] = rightPage.entrys[k+1];
						}
						
						rightPage.entrys[rightPage.nKeys -1] = null;
						rightPage.nKeys--;
						//由于第一个entry的key被修改，因此调整
						adjust_min_key(rightPage);
						
						if(i == 0 && page.parent != null){						
							adjust_min_key(page);
						}
					}else {
						//右兄弟页面上的entry数等于Page.MAX_ENTRY_NUM/2,
						//将右兄弟页面并入本页，让后删除右兄弟页面上的在父页面上的key
						for( int j = i; j < page.nKeys - 1; j++){
							page.entrys[j] = page.entrys[j+1];
						} 
						page.nKeys--;
						
						for (int k = 0; k < page.nKeys; k++) {	
							 
							page.entrys[page.nKeys++] = rightPage.entrys[k];
						}
						
						if(i == 0 && page.parent != null){						
							adjust_min_key(page);
						}
						
						
						//删除右兄弟页面上的在父页面上的key
						realRemoveRecord( rightPage.entrys[0].key, page.parent); 
					} 
					
				}else{
					//首先判断左兄弟节点是否大于Page.MAX_ENTRY_NUM/2,如果大于，则可以借一个来满足最小个数 
					//KeyEntry leftSibling = getLeftSibling(page.entrys[0].key, page.parent);
					Page leftPage = getLeftSibling(page);
					if( leftPage.nKeys > Page.MAX_ENTRY_NUM/2){
						//向左兄弟借一个元素来平衡自己；
						for( int j = i; j >0; j--){
							page.entrys[j] = page.entrys[j-1];
						} 
						
						page.entrys[0] = leftPage.entrys[leftPage.nKeys -1];
						leftPage.entrys[leftPage.nKeys -1] = null;
						leftPage.nKeys--;
						
						//if(i == 0 && page.parent != null){						
							adjust_min_key(page);
						//}
					}else {
						//左兄弟页面上的entry数等于Page.MAX_ENTRY_NUM/2,
						//则此页面和左兄弟页面合并;合并后删除父页面中key为removekey的entry； 					 
						for (int j = 0; j < page.nKeys; j++) {	
							if(j != i){
								leftPage.entrys[leftPage.nKeys++] = page.entrys[j];		
								page.entrys[j] = null;
							}
						}
						//删除父页面指向page的entry
						realRemoveRecord(page.entrys[0].key, page.parent); 
					} 
				}
				
				
			} 
		} 
		
		 
	}
	
	private boolean isFirstSubPage(Page page){
		
		if (page.entrys[0].key == page.parent.entrys[0].key) {			
			return true;
		}else {
			return false;
		}
	}
	
	private boolean isLastSubPage(Page page){ 
		
		int last_idx = page.parent.nKeys -1;
		if (page.entrys[0].key == page.parent.entrys[last_idx].key) {			
			return true;
		}else {
			return false;
		}
	} 
	
	private Page getLeftSibling(Page page){
		
		
		int key = page.entrys[0].key;
		Page parent = page.parent;
		
		int i = 0; 
		for ( ; i < parent.nKeys; i++) {			
			if(key == parent.entrys[i].key){				
				break;
			}			
		} 
		if(i == 0){
			return null;
		}else {
			return (Page) parent.entrys[i-1].child;
		}
		
	}
	
	private Page getRightSibling(Page page){
		
		int key = page.entrys[0].key;
		Page parent = page.parent;
		
		int i = 0;
		for ( ; i < parent.nKeys; i++) {
			if(key == parent.entrys[i].key){				
				break;
			}			
		} 
		if(i >= parent.nKeys-1){
			return null;
		}else
			return (Page) parent.entrys[i+1].child;
		 
	}
	 
	
	/**
	 * page页面的第一个entry的key被修改，调整父页面中指向page的的entry中的key,
	 * 以此向上传播， 直到根节点；
	 * 
	 * 
	 * 
	 * @param page
	 */
	private void adjust_min_key(Page page){
		
		if(page.type == page.PAGE_TYPE_ROOT_LEAF 
				|| page.type == page.PAGE_TYPE_ROOT_NOLEAF )
			return; 
		
		Page parent = page.parent;
		int i = 0; //父页面中指向page的entry在父页面中的索引；
		for (; i < parent.nKeys; i++) {			
			if(parent.entrys[i].child == page){
				parent.entrys[i].key = page.entrys[0].key;
				break;
			}
		}		
		//parent.entrys[0].key = page.entrys[0].key;
		if(i == 0){
			//此时，父页面的第一个元素也被修改，继续进行调整
			adjust_min_key(parent); 
		}
	}
	

	public void insertEntry(int key, Object record){
		
		/**
		 * 搜索适合key插入的叶子页面
		 */
		Page will_page = search(key, root); 		
		//btree_print(page);
		
		KeyEntry entry = new KeyEntry();
		entry.key = key;
		entry.child = record;
		
		/**
		 * good luck! no full，则直接插入,ok，		
		 */
		boolean is_first = putRecord(will_page, entry); 
		if (is_first) {
			/**
			 * 可以确定，新插入的key是Tree中最小的元素，
			 * 否则不会是如果插入到了页面的首entry位置，需要进行调整,
			 * 此时叶子页中的最小记录与其父keyentry不一致，
			 * 需要更新父页中的相应的key，确切得说，这种情况
			 * 只会是每一层的第一页的首元素
			 */				
			adjust_min_key(will_page);
		}
		
		
		/**
		 * 判断will_page是否已超过MAX_ENTRY_NUM，如果页面中的
		 * KeyEntry个数小于MAX_ENTRY_NUM，则插入完成，
		 * 否则需要进行页面分裂调整.
		 */
		if(will_page.nKeys > Page.MAX_ENTRY_NUM){	
			
		//}else{
			/**
			 * 已经full，需要分裂.   
			 * 新建一个Page，用来存储后半部分keyentry
			 * 是否是根节点，如果是根节点，则新建节点，
			 */			
			adjust_spilt(/*key, record, */will_page);
		} 
	}
	
	private void adjust_spilt(/*int key , Object val, */Page page){
		
		//默认page应该已经满了 
		//btree_print(page);
		//System.out.println(page.nKeys);
		
		if(page.nKeys <= Page.MAX_ENTRY_NUM){
			//error
		}
		
		/**
		 * 新建一个Page，用来存储后半部分keyentry
		 * 是否是根节点，如果是根节点，则新建节点，
		 */		
		Page right = new Page();
		
		if(page.type == Page.PAGE_TYPE_LEAF || page.type == page.PAGE_TYPE_ROOT_LEAF){
			right.type = Page.PAGE_TYPE_LEAF;
		}else{
			right.type = Page.PAGE_TYPE_INTERNAL;
		}
		right.nKeys = Page.MAX_ENTRY_NUM / 2;
		right.parent = page.parent;
		System.arraycopy(page.entrys, Page.MAX_ENTRY_NUM - right.nKeys +1 , right.entrys, 0, right.nKeys); 
		page.nKeys = Page.MAX_ENTRY_NUM - right.nKeys +1;
		
		/**
		 * 接下来,如果本页面是根节点， 则新建一个页面作为根节点，将旧根结点分裂为两个结点，切作为新建根节点的两个子节点，
		 * 否则，将新产生的Page “right” 加入到父页面中，相当于在父页面中新插入一个KeyEntry
		 */ 
		if(page.parent != null){
			
			KeyEntry entry = new KeyEntry();
			entry.key = right.entrys[0].key;
			entry.child = right;
			
			boolean is_first = putRecord(page.parent, entry); 
			//此时is_first永远等于false
			/*if (is_first) {
				//需要进行调整,此时叶子页中的最小记录与其父keyentry不一致，需要更新父key中的key
				adjust_min_key(page);
			} */
			if(page.parent.nKeys > Page.MAX_ENTRY_NUM){	
				adjust_spilt(/*right.entrys[0].key, right,*/ page.parent);
			}
			
		}else{
			
			Page root_temp = new Page();
			root_temp.type = Page.PAGE_TYPE_ROOT_NOLEAF;
			root_temp.parent = null;
			
			page.parent = root_temp;
			
			KeyEntry entry1 = new KeyEntry();
			entry1.key = page.entrys[0].key;
			entry1.child = page;
			if(page.type == Page.PAGE_TYPE_ROOT_LEAF)
				page.type = Page.PAGE_TYPE_LEAF;
			else {
				page.type = Page.PAGE_TYPE_INTERNAL;
			}
			page.parent = root_temp;
			
			KeyEntry entry2 = new KeyEntry();
			entry2.key = right.entrys[0].key;
			entry2.child = right;
			right.parent = root_temp;
			putRecord(root_temp, entry1);
			putRecord(root_temp, entry2);
			
			root = root_temp; 
		}
	}
	
	
	public void deleteEntry(int key){
		
		//首先找包含此key的叶子页面
		Page contain_page = search(key, root);
		
		realRemoveRecord(key, contain_page);
		//
	}

	
	private Page search(int key, Page page){
		
		//找到key在其范围内容的叶子页面
		Page rtPage = null;
		
		if(page != null && (page.type == Page.PAGE_TYPE_LEAF || page.type == Page.PAGE_TYPE_ROOT_LEAF)){
			
			rtPage = page;
			
		}else{
		
			if(null != page){
				int i = page.nKeys -1;
				for(; i >=0; i--){
					if(key >= page.entrys[i].key ){
						//break;
						//rtPage = search(key, (Page)page.entrys[i].child);
						break;
					}
				}
				if(i == -1){
				    //说明小于或等于最小值,沿着第一个key的指针向下搜索
					rtPage = search(key, (Page)page.entrys[0].child);
				}else{
					rtPage = search(key, (Page)page.entrys[i].child);
				}
			}		
		}
		
		return rtPage;			
	}
	
	public void btree_print(Page page){
		for(int i = 0; i < page.nKeys; i++){
			
			System.out.print(page.entrys[i].key+",");
			
		}
		System.out.println();
		
		
	}
	
	public void btree_print(){
		
		Queue<Page> queue = new ArrayDeque<Page>();
		
		for(int i = 0; i < root.nKeys; i++){
			
			System.out.print(root.entrys[i].key+",");
			
			if((Page)root.entrys[i].child != null){
				queue.add((Page)root.entrys[i].child);
			}
		}
		System.out.println();
		btree_print(queue);
		
	}
	public void btree_print(Queue<Page> queue){
		
		Page page = null;
		Queue<Page> queue_temp = new ArrayDeque<Page>();		
		while((page = queue.poll()) != null){ 
			for(int i = 0; i < page.nKeys; i++){
				
				System.out.print(page.entrys[i].key+",");
				if((Page)page.entrys[i].child != null){
					queue_temp.add((Page)page.entrys[i].child);
				}
			}
		}
		System.out.println();
		if(queue_temp.size() > 0){
			btree_print(queue_temp);
		}
		
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		BTree bTree = new BTree();
		bTree.createBtree();
		bTree.insertEntry(5, null);
		bTree.insertEntry(30, null);
		bTree.insertEntry(70, null);
		bTree.insertEntry(112, null);
		bTree.insertEntry(90, null);
		
		
		bTree.insertEntry(53, null);
		bTree.insertEntry(20, null);
		bTree.insertEntry(60, null);
		bTree.insertEntry(47, null);
		bTree.insertEntry(111, null);
		bTree.insertEntry(222, null);
		bTree.insertEntry(225, null);
		bTree.insertEntry(329, null);
		
		bTree.insertEntry(422, null);
		bTree.insertEntry(425, null);
		bTree.insertEntry(429, null);
		bTree.insertEntry(3, null);
		
		
		bTree.insertEntry(60, null);
		
		
		System.out.println("-----------------------");
		bTree.btree_print();
		bTree.deleteEntry(30);
		System.out.println("-----------------------");
		bTree.btree_print();
		bTree.deleteEntry(20);
		System.out.println("-----------------------");
		bTree.btree_print();
	}

/*	3,222,
	3,30,53,90,222,422,
	3,5,20,30,47,53,60,70,90,111,112,222,225,329,422,425,429,*/
}
