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
  
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *outInfoColoredPoints = outputVector->GetInformationObject(0);
  vtkInformation *outInfoClusterCenters = outputVector->GetInformationObject(1);

  
  vtkGraph *input = vtkGraph::SafeDownCast(
      inInfo->Get(vtkDataObject::DATA_OBJECT()));

  
  vtkSmartPointer<vtkMutableDirectedGraph> residualNetwork =
    vtkSmartPointer<vtkMutableDirectedGraph>::New();
  for(vtkIdType i = 0; i < input->GetNumberOfVertices(); i++)
    {
    residualNetwork->AddVertex();
    }

  
  vtkSmartPointer<vtkEdgeListIterator> edgeListIterator =
    vtkSmartPointer<vtkEdgeListIterator>::New();
  input->GetEdges(edgeListIterator);
  while(edgeListIterator->HasNext())
    {
    vtkEdgeType edge = edgeListIterator->Next();
    residualNetwork->AddEdge(edge.Source, edge.Target);
    residualNetwork->AddEdge(edge.Target, edge.Source);
    }

  
  vtkFloatArray* capacities = vtkFloatArray::SafeDownCast(input->GetEdgeData()->GetArray("Weights"));

  
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
  
}