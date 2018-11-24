#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <fstream>
#include <string>
using namespace std;

struct node {
    int v;
    node *next;
    int c, f, cf;
    node (int j, node *t, int temp_c) {
        v = j; 
        next = t;
        c = temp_c;
        f = 0;
        cf = c - f;
    }
};
typedef node *linkSt;

void Print_list (linkSt);
void Print_residual_network (vector<linkSt>, int);
bool Find_adj_vertex (int, int, vector<linkSt>);
bool Augmenting_path (vector<linkSt>, int, int, int, int*);

void Print_list (linkSt head) {
    while (head != NULL) {
        cout << "link with: " << head->v << " c = " << head->c << " f = " << head->f << " cf = " << head->cf << "; ";
        head = head->next;
    }
    cout << "\n";
}

void Print_residual_network(vector<linkSt> adj, int v) {
    for (int i = 0; i < v; i++) {
        cout << i << ": "; 
        Print_list(adj[i]);
        cout << "\n";
    }
}

bool Find_adj_vertex(int i, int j, vector<linkSt> *adj) {
    linkSt vertex_view = (*adj)[j];
    
    while (vertex_view != NULL) {           // прохожусь по списку для вершины j и ищу связь с вершиной i
        if (vertex_view->v == i)
            return true;
        vertex_view = vertex_view->next;
    }
    
    return false;
}

bool Augmenting_path (vector<linkSt> adj, int v, int source, int sink, vector<int> *way) {
    // Готовим граф к поиску в глубинну
    queue<int> myqueue;
    vector<string> color;   // цвет вершин
    vector<int> distance;   // длина пути до вершины из начальной
    vector<int> min_way;    // сам путь
    int u;
    
    for (int i = 0; i < v; i++) {
        color.push_back("White");
        distance.push_back(-1);
        min_way.push_back(-1);
    }
    color[source] = "Gray";
    distance[source] = 0;
    myqueue.push(source);
    
    // Граф готов!
    
    while (!myqueue.empty()) {
        u = myqueue.front();
        myqueue.pop();
        for (linkSt t = adj[u]; t != NULL; t = t->next) {
            if ((color[t->v] == "White") && (t->cf > 0)) {
                color[t->v] = "Gray";
                distance[t->v] = distance[u] + 1;
                min_way[t->v] = u;
                myqueue.push(t->v);
            }
        }
        color[u] = "BLACK";
    }
    
    u = min_way[sink];
    way->push_back(sink);
    while (u != -1) {
        way->push_back(u);
        u = min_way[u];
    }
    int temp_swap;
    for (size_t i = 0; i < way->size() / 2; i++) {
        temp_swap = (*way)[i];
        (*way)[i] = (*way)[way->size() - i - 1];
        (*way)[way->size() - i - 1] = temp_swap;
    }
    
    if (distance[sink] != -1)
        return true;
    else
        return false;
}
    

int main() {
    const int MAXFLOW = 10000;
    ifstream File("GrafExKormen.txt");
    int j, i, c;
    int v;                      // кол-во вершин
    vector<linkSt> adj;         // список смежности графа
    File >> v; 
    for (i = 0; i < v; i++)
        adj.push_back(NULL);    
    
    // Создание исходного графа
    while (true) {
        File >> i >> j >> c;    // вершина i соединена с j ребром с пропускной способностью c
        if (i == -1)            // условие окончания считывания информации из файла
            break;
        adj[i] = new node (j, adj[i], c);
    }
    
    // Модификация графа - создание остаточной сети
    
    for (i = 0; i < v; i++) {               // проход по всем вершинам
        linkSt vertex_view = adj[i];        // взял вершину, например, 1, смотрю с кем она связана, и прохожусь по связанным вершинам         
        while (vertex_view != NULL) {       
            if (Find_adj_vertex(i, vertex_view->v, &adj) == false)              // проверяю есть ли обратная связь
                adj[vertex_view->v] = new node (i, adj[vertex_view->v], 0);     // если нет, то создаю обратную дугу с пропускной способностью 0
            vertex_view = vertex_view->next;
        }
    }
    
    // Остаточная сеть создана. Граф готов к работе!
    
    int source, sink;
    File >> source >> sink;
    
    
    vector<int> way;                        // хранит увеличивающий путь из истока в сток
    int cf_min = MAXFLOW;
    linkSt list_f = NULL, list_back = NULL; // list_forvard - список смежности для вершины way[i] на увеличивающем пути
                                            // list_back - список смежности для вершины way[i+1] на увеличивающем пути, нужен чтобы при 
                                            // увеличении потока на ребре (i, j) на cf_min, пустить по ребру (j, i) поток -cf_min
    int max_flow = 0;
    
    while (Augmenting_path(adj, v, source, sink, &way) == true) {
        cout << "way : ";
        for (size_t i = 0; i < way.size(); i++)
            cout << way[i] << "  ";
        printf("\n");
        
        // ищу на увеличивающем пути min(cf, принадлежащих увел пути) 
        for (size_t i = 0; i + 1 < way.size(); i++) {
            list_f= adj[way[i]];
            while (list_f != NULL) {
                if (list_f->v == way[i+1]) {
                    if (list_f->cf < cf_min)
                        cf_min = list_f->cf;
                    break;
                }
                list_f = list_f->next;
            }
        }
        // нашел, теперь пускаю по этому пути поток
        printf("cf_min = %d\n\n", cf_min);
        max_flow += cf_min;
        list_f = NULL;
        list_back = NULL;
        for (size_t i = 0; i + 1 < way.size(); i++) {           //прохожусь по всем ребрам увел пути и обновляю поток
            list_f = adj[way[i]];
            while (list_f != NULL) {                            //ищу в списке смежности для вершины way[i] ребро,связывающее ее с way[i+1]
                if (list_f->v == way[i+1]) {
                    list_f->f += cf_min;
                    list_f->cf = list_f->c - list_f->f;
                    
                    list_back = adj[way[i+1]];                  //список смежности для вершины way[i+1]
                    
                    while (list_back != NULL) {                     //ищу в списке смежности для вершины way[i+1] ребро,связывающее ее с way[i]
                        if (list_back->v == way[i]) {
                            list_back->f += (-1) * cf_min;
                            list_back->cf = list_back->c - list_back->f;
                            break;
                        }
                        list_back = list_back->next;
                    }
                    break;
                }
                list_f = list_f->next;
            }
        }
        
        Print_residual_network(adj, v);         // вывод остаточной сети
        printf("--------------------------------------------------------------------------------\n\n");
        way.clear();
        cf_min = MAXFLOW;
    }
    
    printf("RESULT: max fow = %d\n", max_flow);
    
    return 0;
}
