#include "vtkGraphCutFordFulkerson.h"

#include <vtkObjectFactory.h>
#include <vtkDataSetAttributes.h>
#include <vtkFloatArray.h>
#include <vtkInformationVector.h>
#include <vtkInformation.h>
#include <vtkSmartPointer.h>
#include <vtkMutableDirectedGraph.h>

vtkStandardNewMacro(vtkGraphCutFordFulkerson);

vtkGraphCutFordFulkerson::vtkGraphCutFordFulkerson()
{

}

int vtkGraphCutFordFulkerson::RequestData(vtkInformation *vtkNotUsed(request),
                                    vtkInformationVector **inputVector,
                                    vtkInformationVector *outputVector)
{
  // Get the info objects
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfoColoredPoints = outputVector->GetInformationObject(0);
  vtkInformation *outInfoClusterCenters = outputVector->GetInformationObject(1);

  // Get the input and ouptut
  vtkGraph *input = vtkGraph::SafeDownCast(
      inInfo->Get(vtkDataObject::DATA_OBJECT()));

  // Add a vertex to the residual network for every vertex in the original network
  vtkSmartPointer<vtkMutableDirectedGraph> residualNetwork =
    vtkSmartPointer<vtkMutableDirectedGraph>::New();
  for(vtkIdType i = 0; i < input->GetNumberOfVertices(); i++)
    {
    residualNetwork->AddVertex();
    }

  // Add a forward and a reverse edge in the residual network for every edge in the original network
  vtkSmartPointer<vtkEdgeListIterator> edgeListIterator =
    vtkSmartPointer<vtkEdgeListIterator>::New();
  input->GetEdges(edgeListIterator);
  while(edgeListIterator->HasNext())
    {
    vtkEdgeType edge = edgeListIterator->Next();
    residualNetwork->AddEdge(edge.Source, edge.Target);
    residualNetwork->AddEdge(edge.Target, edge.Source);
    }

  // Get the weights/capacities of the original network
  vtkFloatArray* capacities = vtkFloatArray::SafeDownCast(input->GetEdgeData()->GetArray("Weights"));

  // Create an array to store the flow
  vtkSmartPointer<vtkFloatArray> flow =
    vtkSmartPointer<vtkFloatArray>::New();
  flow->SetNumberOfComponents(1);
  flow->SetNumberOfTuples(input->GetNumberOfEdges());

  for(vtkIdType i = 0; i < flow->GetNumberOfTuples(); i++)
    {
    flow->SetValue(i, 0);
    }
    
  return 1;
}


void vtkGraphCutFordFulkerson::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
  //os << indent << "K: " << this->K << std::endl;
}