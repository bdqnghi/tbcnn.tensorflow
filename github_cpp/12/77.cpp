













#ifndef __vtkBoostKruskalMinimumSpanningTree_h
#define __vtkBoostKruskalMinimumSpanningTree_h

#include "vtkStdString.h" 
#include "vtkVariant.h" 

#include "vtkSelectionAlgorithm.h"

class VTK_INFOVIS_EXPORT vtkBoostKruskalMinimumSpanningTree : public vtkSelectionAlgorithm 
{
public:
  static vtkBoostKruskalMinimumSpanningTree *New();
  vtkTypeRevisionMacro(vtkBoostKruskalMinimumSpanningTree, vtkSelectionAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);
  
  
  
  
  
  
  
  vtkSetStringMacro(EdgeWeightArrayName);
  
  
  
  
  
  vtkSetStringMacro(OutputSelectionType);
  
  
  
  
  
  
  
  void SetNegateEdgeWeights(bool value);
  vtkGetMacro(NegateEdgeWeights, bool);
  vtkBooleanMacro(NegateEdgeWeights, bool);
  
protected:
  vtkBoostKruskalMinimumSpanningTree();
  ~vtkBoostKruskalMinimumSpanningTree();
  
  int RequestData(
    vtkInformation *,
    vtkInformationVector **,
    vtkInformationVector *);
  
  int FillInputPortInformation(
    int port, vtkInformation* info);
  
  int FillOutputPortInformation(
    int port, vtkInformation* info);
  
private:
  char* EdgeWeightArrayName;
  char* OutputSelectionType;
  bool NegateEdgeWeights;
  float EdgeWeightMultiplier;
  
  vtkBoostKruskalMinimumSpanningTree(const vtkBoostKruskalMinimumSpanningTree&);  
  void operator=(const vtkBoostKruskalMinimumSpanningTree&);  
};

#endif
