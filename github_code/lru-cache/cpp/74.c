//设计一个LRU cache的类，并实现get和add方法，都要求O(1)
#include <iostream>

#define HASHSIZE 1<<16
#define MAXLEN 20
#define MAXITEMS 3

using namespace std;

typedef struct item {
    char key[MAXLEN];
    char value[MAXLEN];
    struct item *prev;
    struct item *next;
    struct item *h_next;
}item;

static item **primary_hashtable = NULL;
static int items = 0;
static item *head = NULL;
static item *tail = NULL;

void init(void);
int hash(char *str);
char *get(char *key);
item *add(char *key, char *value);
void hash_delete(char *key);
void init(void) 
{
    primary_hashtable = (item **)malloc(sizeof(item*) * HASHSIZE);
}
int hash(char *str)
{
    char *p;
    int sum = 0;
    for (p = str; *p; p++)
        sum += *p;
    return (sum*sum*2/3) % HASHSIZE;
}
item *add(char *key, char *value)
{
    item *new_item = NULL;
    if (items >= MAXITEMS) {
        new_item = tail;
        hash_delete(new_item->key);
        strncpy(new_item->key, key, MAXLEN);
        strncpy(new_item->value, value, MAXLEN);
        tail = new_item->prev;
        tail->next = NULL;

        new_item->prev = new_item->next = new_item->h_next = NULL;
        
    } else {
        items++;
        new_item = (item *)malloc(sizeof(item));
        strncpy(new_item->key, key, MAXLEN);
        strncpy(new_item->value, value, MAXLEN);
        new_item->prev = new_item->next = new_item->h_next = NULL;
    }
    int hash_index = hash(key);
    new_item->h_next = primary_hashtable[hash_index];
    primary_hashtable[hash_index] = new_item;

    if (!head) {
        head = tail = new_item;
    } else {
        new_item->next = head;
        head->prev = new_item;
        new_item->prev = NULL;
    }
    return new_item;
}
char *get(char *key)
{
    int hash_index = hash(key);
    item *start;
    for (start = primary_hashtable[hash_index]; start != NULL; start = start->h_next) {
        if (strcmp(key, start->key) == 0) {
            return start->value;
        }
    }

    return NULL;
}

void hash_delete(char *key)
{
    int hash_index = hash(key);
    item *cur, *pre=NULL;
    for (cur= primary_hashtable[hash_index]; cur!= NULL; cur= cur->h_next) {
        if (strcmp(key, cur->key) == 0) {
            break;
        }
        pre = cur;
    }

    pre->h_next = cur->h_next;
    cur->h_next = NULL;


    
}
int main() 
{
    init();
    char command[MAXLEN];
    char key[MAXLEN],value[MAXLEN];
    while (scanf("%s", command) && strcmp(command ,"quit") != 0) {
        if (strcmp(command, "add") == 0) {
            printf("add a item,input key and value\n");
            scanf("%s %s", key, value);
            add(key, value);
            printf("add done\n");
        } else if (strcmp(command, "get") == 0){
            printf("get a item: input key\n");
            scanf("%s", key);
            char *v = get(key);
            if (v) {
                printf("%s = %s\n", key, get(key));
            } else {
                printf("%s not found \n",key);
            }
            printf("get done\n");
        } else {
            printf("no command\n");
        }
    }
    return 0;
}

