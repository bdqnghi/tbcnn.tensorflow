#include <cstdio>

int bucket[1000010];
int bucket2[1000010];

int bucket3[1000010];

int ans[5];
int ansx[5], ansy[5];

int main() {
    int o[5];
    o[0] = 4;
    o[1] = 2;
    o[2] = 3;
    o[3] = 5;
    o[4] = 1;
    for(int i = 0; i < 5; i++) bucket[o[i]]++;
    for(int i = 1; i <= 1000000; i++) bucket[i] += bucket[i - 1]; // if you want descending order then 1000000 to 1
    for(int i = 4; i >= 0; i--) ans[--bucket[o[i]]] = o[i];
    for(int i = 0; i < 5; i++) printf("%d ",ans[i]);
    printf("\n");
    
    int ox[5], oy[5];
    
    ox[0] = 4;
    ox[1] = 2;
    ox[2] = 2;
    ox[3] = 3;
    ox[4] = 1;
    
    oy[0] = 1;
    oy[1] = 3;
    oy[2] = 2;
    oy[3] = 4;
    oy[4] = 5;
    
    for(int i = 0; i < 5; i++) bucket2[ox[i]]++;
    for(int i = 1; i <= 1000000; i++) bucket2[i] += bucket2[i - 1]; // stable sort
    for(int i = 4; i >= 0; i--) {
        ansx[--bucket2[ox[i]]] = ox[i];
        ansy[bucket2[ox[i]]] = oy[i];
    }
    for(int i = 0; i < 5; i++) printf("(%d %d) ",ansx[i], ansy[i]);
    printf("\n");
    
    
    for(int i = 0; i < 5; i++) bucket3[o[i]]++;
    for(int i = 1000000; i >= 1; i--) bucket3[i] += bucket3[i + 1]; // descending order
    for(int i = 5; i >= 0; i--) ans[--bucket3[o[i]]] = o[i];
    for(int i = 0; i < 5; i++) printf("%d ",ans[i]);
    printf("\n");
    
    return 0;
}
