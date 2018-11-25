




#include <stdio.h>
#include "Fulkerson.h"

FordFulkerson::FordFulkerson()
{
    init();
}

FordFulkerson::~FordFulkerson()
{
    Node* pre;
    Node* suc;
    for( int i=0;i<headCount;i++)
    {
        pre = nodes[i].next;
        while(pre)
        {
            suc = pre->next;
            delete pre;
            pre = suc ;
        }
    }
    delete nodeStack;
}

void FordFulkerson::init()
{
    nodeStack = new stack<Node*>();
    constructAdjList();
    for( int i=0; i<headCount; i++)
    {
        currentState[i] = flowPair(i,-1);
    }
    Qs = 0;
    augmentingPath = 0;
    current = -1;
    source = 0;
    target = 6;
    nodeStack->push(nodes[0].next);
    currentState[0] = flowPair(0,999999);
}

void FordFulkerson::constructAdjList()
{
    Node* tmp ;
    nodes[0].next = new Node(0,0);
    tmp = nodes[0].next ;
    tmp->next = new Node(1,13);
    tmp = tmp->next ;
    tmp->next = new Node(2,9);
   
    nodes[1].next = new Node(3,6);
    tmp = nodes[1].next;
    tmp->next = new Node(4,5);

    nodes[2].next = new Node(1,4);
    tmp = nodes[2].next;
    tmp->next = new Node(3,5);
    tmp = tmp->next ;
    tmp->next = new Node(5,5);

    nodes[3].next = new Node(4,6);
    tmp = nodes[3].next;
    tmp->next = new Node(5,4);
    tmp = tmp->next;
    tmp->next = new Node(6,4);

    nodes[4].next = new Node(6,9);

    nodes[5].next = new Node(6,10);
}

void FordFulkerson::displayInfo()
{
    printf("�ҵ�����·����%d ��\n",augmentingPath);
    printf("������������%d\n",Qs);

    printf("���������");

    int sum = 0;
    for(Node* node = nodes[0].next; node != NULL;node = node->next)
        sum += node->F ;

    printf("%d\n",sum);
    printf("\n\n Flow after Adjusted \n\n");

    for (int i=0;i<headCount;i++)
    {
        while(nodes[i].next)
        {
            printf("v%d->v%d : ",i,nodes[i].next->number);
            printf("C= %d F= %d\n",nodes[i].next->C,nodes[i].next->F);
            nodes[i].next = nodes[i].next->next;
        }
        printf("\n");
    }

}

void FordFulkerson::getMaxFlow()
{
    mark();
}

void FordFulkerson::pop(int number)
{
    nodeStack->pop();
    currentState[number].second = -1;
}

Node* FordFulkerson::findNode(Node* _current)
{
    Node* node = nodes[_current->number].next; 
    Node* result;

    if (current != -1)
    {
        while ((current != target) && (node->number != current))
        {
            node = node->next;
        }
        node = node->next;
    }
   

    while(node)
    {
        if (node->C != node->F)
        {
            result = node;
            break;
        }
        node = node->next;
    }
   
   
    while(node)
    {
        if ((node->number == target) && (node->C != node->F))
        {
            result = node;
            break;
        }
        node = node->next;
    }
    return result;
}

Node* FordFulkerson::getAdjustedNode(int number,int _target)
{
    Node* node = nodes[number].next;
    while(node)
    {
        if (node->number == _target)
            break;
        node = node->next;
    }
    return node;
}


void FordFulkerson::adjustFlow()
{
    int Q ;
    int index;
    int fullFlow = -1;
    Node* tmp;

    Q = currentState[target].second ;
    Qs += Q;
    augmentingPath += 1;
   
    index = target;
    while ( index > 0)
    {
        tmp = getAdjustedNode(currentState[index].first,index);
        tmp->F += Q ;       
        if (index != target)
        {           
            currentState[index].second = currentState[index].second - currentState[target].second ;
        }
       
        if (tmp->F == tmp->C)
        {
            fullFlow = index ;
        }
        index = currentState[index].first;
    }

    
    if (fullFlow != -1)
    {
        while (nodeStack->top()->number != fullFlow)
        {
            pop(nodeStack->top()->number);
        }
    }
    return ;
}

void FordFulkerson::mark()
{
    Node* adjNode;
    int minQ = 999999;
   

    while (!nodeStack->empty())
    {   
        if (nodeStack->top()->number == target)
        {
            adjustFlow(); 
            current = nodeStack->top()->number;
            pop(current);
            continue;
        }

        
        if ((nodeStack->top()->C == nodeStack->top()->F ) && (nodeStack->top()->number != 0))
        {
            current = nodeStack->top()->number;
            pop(current);           
            continue;
        }

        adjNode = findNode(nodeStack->top());

        if ( adjNode == NULL)
        {
            current = nodeStack->top()->number;
            pop(current);
            continue;
        }
        else
        {
            if (nodeStack->top()->number != 0)
            {
                minQ = currentState[nodeStack->top()->number].second;
            }
            else
                minQ = 999999;
           
            currentState[adjNode->number].first = nodeStack->top()->number;
            currentState[adjNode->number].second = adjNode->C - adjNode->F < minQ ? adjNode->C - adjNode->F :minQ;
            nodeStack->push(adjNode);
            current = -1;

        }
    }
}

int main()
{
    FordFulkerson* ffk = new FordFulkerson();
    ffk->getMaxFlow();
    ffk->displayInfo();

    delete ffk;
    return 0;
}
