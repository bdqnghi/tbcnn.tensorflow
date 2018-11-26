// Compile with Vert_list.cpp
#include <iostream>
#include "Vert_list.h"

void print(Vertex * v0)
{
    std::cout << "v[" << v0->index << "], ";
}

void dfs(Vert_list * vert_list, Vertex * v0, int num_of_vertices, bool * visited)
{
    print(v0);
    visited[v0->index] = true;
    // przegladanie listy sasiadow v0
    Vertex * iterator = vert_list->list[v0->index].head;
    while(iterator != NULL)
    {
        if(visited[iterator->index] == false)
            dfs(vert_list, iterator, num_of_vertices, visited);
        iterator = iterator->next;
    }
}
int main()
{
    int num_of_vertices = 7;
    int num_of_edges = 5;
    bool visited[num_of_vertices];
    for(int i = 0; i < num_of_vertices; i++)
        visited[i] = false;

    Vert_list * vert_list = new Vert_list(num_of_vertices, num_of_edges);
    vert_list->init();
    vert_list->print();
    std::cout << std::endl;
    dfs(vert_list, vert_list->list[0].head, num_of_vertices, visited);
    delete vert_list;
    return 0;
}
