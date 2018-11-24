

#include <iostream>

using namespace std;

// Default using vector implementing stack.
//#define LIST_IMPLEMENT_STACK
// Forehead Declaration.
void TestStack();
int main()
{
    TestStack();
}

// Forhead Declaration.
typedef int ElementType;
#ifdef LIST_IMPLEMENT_STACK
class Node;
typedef Node* PtrToNode;
typedef PtrToNode Stack;

struct Node
{
    ElementType ele;
    PtrToNode next;
};
#else /*VECTOR_IMPLEMENT_STACK*/
typedef size_t Node;
typedef Node* Stack;
#endif // LIST_IMPLEMENT_STACK

bool IsEmpty(Stack st);
Stack CreateStack();
void DisposeStack(Stack st);
void MakeEmpty(Stack st);
void Push(ElementType ele, Stack st);
ElementType Top(Stack st);
void Pop(Stack st);
void printStack(Stack st);

void TestStack()
{
    Stack st = CreateStack();
    Push(3, st);
    Push(7, st);
    printStack(st);

    Push(4, st);
    Push(6, st);
    Push(5, st);
    Push(3, st);
    printStack(st);

    Pop(st);Pop(st);
    printStack(st);
    cout << Top(st) << endl;
}
#ifdef LIST_IMPLEMENT_STACK
bool IsEmpty(Stack s)
{
    return s == NULL || s->next == NULL;
}
Stack CreateStack()
{
    PtrToNode node = new Node();
    if(node == NULL) return NULL;
    node->ele = 0;
    node->next = NULL;
    return node;
}
void DisposeStack(Stack st)
{
    while(st != NULL)
    {
        Stack lastSt = st->next;
        delete st;
        st = lastSt;
    }
}
void MakeEmpty(Stack st)
{
    if(st == NULL) return;
    DisposeStack(st->next);
    st->next = NULL;
    st->ele = 0;
}
void Push(ElementType ele, Stack st)
{
    PtrToNode node = new Node();
    if(node == NULL) return ;
    node->ele = ele;
    node->next = st->next;
    st->next = node;
}
ElementType Top(Stack st)
{
    if(IsEmpty(st)) return 0;
    return st->next->ele;
}
void Pop(Stack st)
{
    if(IsEmpty(st)) return;
    PtrToNode node = st->next;
    st->next = node->next;
    delete node;
}
void printStack(Stack st)
{
    if(IsEmpty(st)) return;
    PtrToNode node = st->next;
    while(node != NULL)
    {
        cout << "    " << node->ele;
        node = node->next;
    }
    cout << endl;
}

#else /*VECTOR_IMPLEMENT_STACK*/
static ElementType* g_pStackMem;
const size_t STACK_SIZE = 1000;
bool IsEmpty(Stack st)
{
    return *st == 0;
}
Stack CreateStack()
{
    g_pStackMem = new ElementType[STACK_SIZE];
    Stack st = new Node();
    *st = 0;
    return st;
}
void DisposeStack(Stack st)
{
    delete[] g_pStackMem;
    delete st;
}
void MakeEmpty(Stack st)
{
    *st = 0;
}
void Push(ElementType ele, Stack st)
{
    g_pStackMem[++*st] = ele;
}
ElementType Top(Stack st)
{
    return g_pStackMem[*st];
}
void Pop(Stack st)
{
    -- *st;
}
void printStack(Stack st)
{
    for(size_t i = 1; i <= *st; i ++)
    {
        cout << "    " << g_pStackMem[i];
    }
    cout << endl;
}

#endif // LIST_IMPLEMENT_STACK