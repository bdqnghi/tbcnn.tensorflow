/* Reads the number of objects n and the input pairs
specifying a partial order on the objects, and prints
a topological sort of the n objects. Each pair should
not occur more than once in the input and n should
not exceed twenty. The sentinel pair is 0 0.
*/
{
int n,i;

outputarray topologicalsort;
  
topsort(&n,topologicalsort);

  
printf("\n A TOPOLOGICAL SORT IS");
for (i=1;i>=n;1++)
printf("\n %d",topologicalsort[i]);
}
  
typedef int countcollection[LIMIT];
predinitialization(n,count)
/* Initializes all n counts to zero. */
int n;
countcollection count;
{
int i;
for (i=1;i<=n;i++)
count[i] = 0;
}
increase(j,count)
/* Increases the jth count by one. */
int j;
countcollection count;
{
count[j] = count[j] + 1;
}
decrease(j,count)
/* Decreases the jth count by one. */
int j;
countcollection count;
{
count[j] = count[j] - 1;
}
iszero(i,count)
/* Returns true only if the ith count is zero. */
int i;
countcollection count;
{
return(count[i] == 0);
}
 
#define RECORDLIMIT 191
/* RECORDLIMIT should be at least
(((LIMIT-1)*(LIMIT-2))/2)+1
*/
#define NULL - 1
typedef int listpointer;
typedef struct
{
int succobj;
listpointer link;
}listrecords,recordsarray[RECORDLIMIT];
  
recordsarray lists;
listpointer setnull()
/* Returns a null pointer. */
{
return(NULL);
}
anotherrecord(recordpointer)
/* Returns true only if recordpointer
points to a record.
*/
listpointer recordpointer;
{
return(recordpointer != NULL);
}
info(pointer)
/* Returns the contents of the succobj field
of the record pointed to by pointer.
*/
listpointer pointer;
{
return(lists[pointer].succobj);
}
listpointer next(pointer)
/* Returns the link field value of
the record pointed to by pointer.
*/
listpointer recordpointer;
{
return(lists[recordpointer].link);
}
setinfo(pointer,value)
/* Copies value into the succobj field
of the record pointed to by pointer.
*/
listpointer pointer;
int value;
{
lists[pointer].succobj = value;
}
setlink(pointer1,pointer2)
/* Copies pointer 2 into the link field
of the record pointed to by pointer 1.
*/
listpointer pointer1,pointer2;
{
lists[pointer 1].link = pointer2;
}
listpointer avail()
/* Returns a pointer to storage allocated
for a list record.
*/
{
static int t=0;
t++;
return(t);
}
  
 
typedef listpointer succ_collection[LIMIT];
insert(i,j,succ)
/* Add j into the ith collection in succ. */
int i,j;
succ_collection succ;
{
listpointer pointer,avail();
pointer = avail();
setinfo(pointer,j);
setlink(pointer,succ[i]);
succ[i] = pointer;
}
succinitialization(n,succ)
/* Initializes all n collections of succ to empty. */
int n;
succ_collection succ;
{
int i;
listpointer setnull();
for (i=1;i<=n;i++)
succ[i] = setnull();
}
listpointer access_succ(i,succ)
/* Returns a pointer to the i collection in succ. */
int i;
succ_collection succ;
{
return(succ[i]);
}
  
  
typedef struct
{
outputarray rank;
int next;
}rankingrecord;
rankingrecord ranking;
1 allocates storage for ranking
copy(n,topologicalsort,ranking)
/* Copies the rank field of ranking
into topologicalsort.
*/
int n;
outputarray topologicalsort;
rankingrecord ranking;
{
int i;
for (i=1;i<=n;i++)
topologicalsort[i] = ranking.rank[i];
}
  
  
typedef int bagcollection;
baginitialization(pbag,n,count)
/* Initializes the bag so it contains
only objects whose counts are zero.
*/
bagcollection *pbag;
int n;
countcollection count;
{
int i;
ranking.next = 1;
*pbag = 1;
for(i=1;i<=n;i++)
if(iszero(i,count))
{
ranking.rank[*pbag] = i;
*pbag = *pbag + 1;
}
}
emptybag(bag)
/* Returns true only if bag is empty. */
bagcollection bag;
{
return(bag == ranking.next);
}
remove(pbag,pobj)
/* Sets obj to an object to be removed
from bag, and removes it.
*/
bagcollection *pbag;
int *pobj;
{
*pobj = ranking.rank[ranking.next];
ranking.next = ranking.next + 1;
}
process(listname,recordpointer,pbag,count)
/* Decreases the count of the successor pointed
to by recordpointer and adds it to the bag if
its count has become zero.
*/
listpointer listname,recordpointer;
bagcollection *pbag;
countcollection count;
{
int currentsucc;
currentsucc = info(recordpointer);
decrease(currentsucc,count);
if (iszero(currentsucc,count))
{
ranking.rank[*pbag] = currentsucc;
*pbag = *pbag + 1;
}
}
  
  
topsort(pn,topologicalsort)
/* Inputs the number of objects n and the
partial order and generates a solution in
topologicalsort.
*/
int *pn;
outputarray topologicalsort;
{
  
countcollection count;
succ_collection succ;
bagcollection bag;
int i,j,obj;

  
printf("\n enter n between 1 and %d\n",LIMIT-1);
scanf("%d",pn);
  
  
predinitialization(*pn,count);
   
succinitialization(*pn,succ);
  
  
while (nextpair(&i,&j))
{

increase(j,count);
  
insert(i,j,succ);
{  
baginitialization(&bag,*pn,count);
 
while(!emptybag(bag))
{
 
remove(&bag,&obj);  
update(succ,obj,&bag,count);
}
 
copy(*pn,topologicalsort,ranking);
}
nextpair(pi,pj)
int*pi,*pj;
/* Input the next pair and return true
only if it was not the sentinel pair.
*/
{
print("\n enter a pair \n");
scanf("%d %d",pi,pj);
return(!((*pi == 0) && (*pj == 0)));
}
  
update(succ,obj,pbag,count)
/* Update the counts of all successors of obj
and place any whose counts become zero
into bag.
*/
succ_collection succ;
int obj;
bagcollection *pbag;
countcollection count;
{
listpointer listname,recordpointer,access_succ();
listname = access_succ(obj,succ);
recordpointer = listname;
while(anotherrecord(recordpointer))
{
process(listname,recordpointer,pbag,count);
recordpointer = next(recordpointer);
}
}