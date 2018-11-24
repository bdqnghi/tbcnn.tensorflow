
#include<string.h>
#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
typedef struct node
{
        char ch;
        int freq;
        struct node *left;
        struct node *right;
}node;
/*Declaring heap globally so that we do not need to pass it as an argument every time*/
/* Heap implemented  here is Min Heap */
node * heap[1000000];
int heapSize;
/*Initialize Heap*/
void Init()
{
        heapSize = 0;
        heap[0] = (node *)malloc(sizeof(node));
        heap[0]->freq = -INT_MAX;
}
/*Insert an element into the heap */
void Insert(node * element)
{
        heapSize++;
        heap[heapSize] = element; /*Insert in the last place*/
        /*Adjust its position*/
        int now = heapSize;
        while(heap[now/2] -> freq > element -> freq) 
        {
                heap[now] = heap[now/2];
                now /= 2;
        }
        heap[now] = element;
}
node * DeleteMin()
{
        /* heap[1] is the minimum element. So we remove heap[1]. Size of the heap is decreased. 
           Now heap[1] has to be filled. We put the last element in its place and see if it fits.
           If it does not fit, take minimum element among both its children and replaces parent with it.
           Again See if the last element fits in that place.*/
        node * minElement,*lastElement;
        int child,now;
        minElement = heap[1];
        lastElement = heap[heapSize--];
        /* now refers to the index at which we are now */
        for(now = 1; now*2 <= heapSize ;now = child)
        {
                /* child is the index of the element which is minimum among both the children */ 
                /* Indexes of children are i*2 and i*2 + 1*/
                child = now*2;
                /*child!=heapSize beacuse heap[heapSize+1] does not exist, which means it has only one 
                  child */
                if(child != heapSize && heap[child+1]->freq < heap[child] -> freq ) 
                {
                        child++;
                }
                /* To check if the last element fits ot not it suffices to check if the last element
                   is less than the minimum element among both the children*/
                if(lastElement -> freq > heap[child] -> freq)
                {
                        heap[now] = heap[child];
                }
                else /* It fits there */
                {
                        break;
                }
        }
        heap[now] = lastElement;
        return minElement;
}
void print(node *temp,char *code)
{
        if(temp->left==NULL && temp->right==NULL)
        {
                printf("char %c code %s\n",temp->ch,code);
                return;
        }
        int length = strlen(code);
        char leftcode[512],rightcode[512];
        strcpy(leftcode,code);
        strcpy(rightcode,code);
        leftcode[length] = '0';
        leftcode[length+1] = '\0';
        rightcode[length] = '1';
        rightcode[length+1] = '\0';
        print(temp->left,leftcode);
        print(temp->right,rightcode);
}
/* Given the list of characters along with their frequencies, our goal is to predict the encoding of the
   characters such that total length of message when encoded becomes minimum */ 
int main()
{
        Init();
        int distinct_char ;
        scanf("%d",&distinct_char);
        char ch;
        int freq;       
        int iter;
        for(iter=0;iter<distinct_char;iter++)
        {
                char t[4];
                scanf("%s",t); //Scanning the character as string to avoid formatting issues of input.
                ch = t[0];
                scanf("%d",&freq);
                node * temp = (node *) malloc(sizeof(node));
                temp -> ch = ch;
                temp -> freq = freq;
                temp -> left = temp -> right = NULL;
                Insert(temp);
        }
        /* Special Case */
        if(distinct_char==1)
        {
                printf("char %c code 0\n",ch);
                return 0;
        }
        for(iter=0;iter<distinct_char-1 ;iter++)
        {
                node * left = DeleteMin();
                node * right = DeleteMin();
                node * temp = (node *) malloc(sizeof(node));
                temp -> ch = 0;
                temp -> left = left;
                temp -> right = right;
                temp -> freq = left->freq + right -> freq;
                Insert(temp);
        }
        node *tree = DeleteMin();
        char code[512];
        code[0] = '\0';
        print(tree,code);



}
