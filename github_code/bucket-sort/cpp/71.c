extern int hash(void *elt);
extern int numBuckets(int numElements);

/* linked list of elements in bucket. */
typedef struct entry {
	void	*element;
	struct entry *next;
	} ENTRY;
	
	/*maintain count of entries in each bucket and pointer to its first entry*/
	typedef struct {
		int size;
		ENTRY *head;
		} BUCKET;
		
		/* Allocation of buckets and the number of buckets allocated */
		static BUCKET *buckets = 0;
		static int num = 0;
		
		/** One by one remove and overwrite ar */
		void extract (BUCKET *buckets, int(*cmp)const void *, const void *),
						void **ar, int n){
			int i, low;
			int idx = 0;
			for (i=0; i<num;i++){
				ENTRY *ptr, *tmp;
				if (buckets[i].size == 0) continue; /* empty buckiet */
				
				ptr = buckets[i].head;
				if (buckets[i].size == 1){
					ar[idx++] = ptr->element;
					free(ptr);
					buckets[i].size = 0;
					continue;
					}
					
					/* insertion sort where elements are drawn from linked list
					* and inserted into array. linked list are realsed. */
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
						
						/** Insert each element and increment counts */
							entry *E = (BUCKET *) calloc (num, sizeof (BUCKET));
							for (i = 0; i < n; i++) {
								int k = hash(ar[i]);
								
								