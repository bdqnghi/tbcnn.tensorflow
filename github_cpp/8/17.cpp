
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

int n;
countcollection count;
{
int i;
for (i=1;i<=n;i++)
count[i] = 0;
}
increase(j,count)

int j;
countcollection count;
{
count[j] = count[j] + 1;
}
decrease(j,count)

int j;
countcollection count;
{
count[j] = count[j] - 1;
}
iszero(i,count)

int i;
countcollection count;
{
return(count[i] == 0);
}
 
#define RECORDLIMIT 191

#define NULL - 1
typedef int listpointer;
typedef struct
{
int succobj;
listpointer link;
}listrecords,recordsarray[RECORDLIMIT];
  
recordsarray lists;
listpointer setnull()

{
return(NULL);
}
anotherrecord(recordpointer)

listpointer recordpointer;
{
return(recordpointer != NULL);
}
info(pointer)

listpointer pointer;
{
return(lists[pointer].succobj);
}
listpointer next(pointer)

listpointer recordpointer;
{
return(lists[recordpointer].link);
}
setinfo(pointer,value)

listpointer pointer;
int value;
{
lists[pointer].succobj = value;
}
setlink(pointer1,pointer2)

listpointer pointer1,pointer2;
{
lists[pointer 1].link = pointer2;
}
listpointer avail()

{
static int t=0;
t++;
return(t);
}
  
 
typedef listpointer succ_collection[LIMIT];
insert(i,j,succ)

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

int n;
succ_collection succ;
{
int i;
listpointer setnull();
for (i=1;i<=n;i++)
succ[i] = setnull();
}
listpointer access_succ(i,succ)

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

bagcollection bag;
{
return(bag == ranking.next);
}
remove(pbag,pobj)

bagcollection *pbag;
int *pobj;
{
*pobj = ranking.rank[ranking.next];
ranking.next = ranking.next + 1;
}
process(listname,recordpointer,pbag,count)

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

{
print("\n enter a pair \n");
scanf("%d %d",pi,pj);
return(!((*pi == 0) && (*pj == 0)));
}
  
update(succ,obj,pbag,count)

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