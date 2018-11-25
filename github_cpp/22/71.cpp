extern int hash(void *elt);
extern int numBuckets(int numElements);


typedef struct entry {
	void	*element;
	struct entry *next;
	} ENTRY;
	
	
	typedef struct {
		int size;
		ENTRY *head;
		} BUCKET;
		
		
		static BUCKET *buckets = 0;
		static int num = 0;
		
		
		void extract (BUCKET *buckets, int(*cmp)const void *, const void *),
						void **ar, int n){
			int i, low;
			int idx = 0;
			for (i=0; i<num;i++){
				ENTRY *ptr, *tmp;
				if (buckets[i].size == 0) continue; 
				
				ptr = buckets[i].head;
				if (buckets[i].size == 1){
					ar[idx++] = ptr->element;
					free(ptr);
					buckets[i].size = 0;
					continue;
					}
					
					
					low = idx;
					ar[idx++] = ptr->element;
					tmp- = ptr;
					ptr = ptr -> next;
					free(tmp);
					while (ptr != NULL){
						int i = idx-1;
						while (i >= low && cmp (ar[i], ptr->element) > ){
							ar[i+1] = ar[i];
							i--;
						}
						ar[i+1] = ptr->element;
						tmp = ptr;
						ptr = ptr->next;
						free(tmp);
						idx++;
					}
					buckets[i].size = 0;
					}
				}
				
				void sortPointer(void **ar, int n,
									int(*cmp)(const void *, const void *)){
					int i;
					num = numBuckets(n);
					buckets = (BUCKET *) calloc (num, sizeof(BUCKET));
					for (i=0; i<n;i++){
						int k = hash(ar[i]);
						
						
							entry *E = (BUCKET *) calloc (num, sizeof (BUCKET));
							for (i = 0; i < n; i++) {
								int k = hash(ar[i]);
								
								