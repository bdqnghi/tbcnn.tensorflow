#include <iostream>
using namespace std;

struct node {
      char mark;
      bool visit;
};

class Graph {
public:
      int size, rear, front, queueCount, vertexCount;
      int *queue, **adjMatrix;
      struct node *vertices[100];   

      Graph(int size) {
            this->size = size;
            this->rear = -1;
            this->front = 0;
            this->queueCount = 0;
            this->vertexCount = 0;

            adjMatrix = new int*[size];
            for(int i = 0; i < size; i++) {
                  adjMatrix[i] = new int[size];
                  for(int j = 0; j < size; j++) {
                        adjMatrix[i][j] = 0;
                  }
            }
      }

      void queueInsert(int data) {
            queue[++rear] = data;
            queueCount++;
      }

      int queueRemove() {
            queueCount--;
            return queue[front++];
      }

      bool isQueueEmpty() {
            return queueCount == 0;
      }

      void addVertex(char ch) {
            cout << "--------" << endl;
            struct node *temp = new struct node;
            temp->mark = ch;
            temp->visit = false;
            vertices[vertexCount++] == temp;
            cout << "--------" << endl;
      }

      void addEdge(int init, int term) {
            adjMatrix[init][term] = 1;
            adjMatrix[term][init] = 1;
      }

      void displayVertex(int num) {
            cout << vertices[num]->mark << endl;
      }

      int adjacentUnvisitedVertex(int num) {
            for(int i = 0; i < num; i++) {
                  if(adjMatrix[num][i] == 1 && vertices[i]->visit == false)
                        return i;
            }

            return -1;
      }

      void breadthFirstSearch() {
            cout << "----------------------" << endl;
            vertices[0]->visit = true;
            displayVertex(0);
            queueInsert(0);

            while(isQueueEmpty()) {
                  int unvisited = adjacentUnvisitedVertex(queueRemove());

                  if(unvisited == -1) {
                        queueRemove();
                  }
                  else {
                        vertices[unvisited]->visit = true;
                        displayVertex(unvisited);
                        queueInsert(unvisited);
                  }
            }

            for(int i = 0; i < vertexCount; i++) {
                  vertices[i]->visit = false;
            }
            cout << "----------------------" << endl;
      }
};

int main(int argc, char const *argv[]) {
      

      int a, b, size, choice;
      char ch;
      cout << "Enter the number of vertices of the graph : ";
      cin >> size;

      Graph gr(size);

      cout << "Enter " << size << " vertices >" << endl;
      for(int i = 0; i < size; i++) {
            cin >> ch;
            gr.addVertex(ch);
      }

      cout << "Now specify all the edges in the graph >" << endl;
      do {
            cout << "a: "; cin >> a;
            cout << "b: "; cin >> b;

            if(a <= size && b <= size) {
                  gr.addEdge(a, b);
            }
            else {
                  cout << "Check your input" << endl;
            }

            cout << "-------" << "        enter 1 to continue..." << endl;
            cin >> choice;
            cout << "-------" << endl;
      } while(choice == 1);

      cout << "Performing Breadth First Search >>>>" << endl;
      gr.breadthFirstSearch();

      return 0;
}
