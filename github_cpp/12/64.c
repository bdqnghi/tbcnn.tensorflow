#include <vtkSmartPointer.h>

#include <vtkMutableUndirectedGraph.h>
#include <vtkBoostPrimMinimumSpanningTree.h>
#include <vtkBoostBreadthFirstSearch.h>
#include <vtkTree.h>
#include <vtkDoubleArray.h>
#include <vtkDataSetAttributes.h>
#include <vtkTreeDFSIterator.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkMutableUndirectedGraph> g = 
    vtkSmartPointer<vtkMutableUndirectedGraph>::New();
  
  
  vtkIdType v1 = g->AddVertex();
  vtkIdType v2 = g->AddVertex();
  vtkIdType v3 = g->AddVertex();
  
  
  g->AddEdge(v1, v2);
  g->AddEdge(v2, v3);
  g->AddEdge(v1, v3);
  
  
  vtkSmartPointer<vtkDoubleArray> weights =
    vtkSmartPointer<vtkDoubleArray>::New();
  weights->SetNumberOfComponents(1);
  weights->SetName("Weights");
  
  
  weights->InsertNextValue(1.0);
  weights->InsertNextValue(1.0);
  weights->InsertNextValue(2.0);
  
  
  g->GetEdgeData()->AddArray(weights);
  
  
  std::cout << "Original Graph" << std::endl << "----------" << std::endl;
  std::cout << "Number of vertices: "
            << g->GetNumberOfVertices() << std::endl;
  std::cout << "Number of edges: "
            << g->GetNumberOfEdges() << std::endl;
  
  
  vtkSmartPointer<vtkBoostPrimMinimumSpanningTree> minimumSpanningTreeFilter = 
    vtkSmartPointer<vtkBoostPrimMinimumSpanningTree>::New();
  minimumSpanningTreeFilter->SetOriginVertex(v1);
  minimumSpanningTreeFilter->SetInput(g);
  minimumSpanningTreeFilter->SetEdgeWeightArrayName("Weights");
  
  
  minimumSpanningTreeFilter->Update();
  
  
  vtkSmartPointer<vtkTree> minimumSpanningTree =
    vtkSmartPointer<vtkTree>::New();
  minimumSpanningTree->ShallowCopy(minimumSpanningTreeFilter->GetOutput());
  
  
  std::cout << std::endl;
  std::cout << "Minimum spanning tree" << std::endl
            << "----------" << std::endl;
  std::cout << "Number of vertices: "
            << minimumSpanningTree->GetNumberOfVertices() << std::endl;
  std::cout << "Number of edges: "
            << minimumSpanningTree->GetNumberOfEdges() << std::endl;
  
  vtkIdType root = minimumSpanningTree->GetRoot();
  std::cout << "Root: " << root << std::endl;
  
  vtkSmartPointer<vtkTreeDFSIterator> dFS =
    vtkSmartPointer<vtkTreeDFSIterator>::New();
  dFS->SetStartVertex(root);
  dFS->SetTree(minimumSpanningTree);
  
  
  while(dFS->HasNext())
    {
    vtkIdType NextVertex = dFS->Next();
    std::cout << "Next vertex: "
              << NextVertex
              << " level: "
              << minimumSpanningTree->GetLevel(NextVertex)
              << std::endl;
    }

  return EXIT_SUCCESS;
}
