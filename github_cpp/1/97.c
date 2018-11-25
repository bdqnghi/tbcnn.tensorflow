














#ifndef __vtkBoostBreadthFirstSearchTree_h
#define __vtkBoostBreadthFirstSearchTree_h

#include "vtkStdString.h" 
#include "vtkVariant.h" 

#include "vtkTreeAlgorithm.h"

class VTK_INFOVIS_EXPORT vtkBoostBreadthFirstSearchTree : public vtkTreeAlgorithm 
{
public:
  static vtkBoostBreadthFirstSearchTree *New();
  vtkTypeMacro(vtkBoostBreadthFirstSearchTree, vtkTreeAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);
  
  
  
  
  void SetOriginVertex(vtkIdType index);

  
  
  
  
  
  
  void SetOriginVertex(vtkStdString arrayName, vtkVariant value);
  
  
  
  
  vtkSetMacro(CreateGraphVertexIdArray, bool);
  vtkGetMacro(CreateGraphVertexIdArray, bool);
  vtkBooleanMacro(CreateGraphVertexIdArray, bool);

  
  
  vtkSetMacro(ReverseEdges, bool);
  vtkGetMacro(ReverseEdges, bool);
  vtkBooleanMacro(ReverseEdges, bool);

protected:
  vtkBoostBreadthFirstSearchTree();
  ~vtkBoostBreadthFirstSearchTree();

  int FillInputPortInformation(int port, vtkInformation* info);

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
  
private:

  vtkIdType OriginVertexIndex;
  char* ArrayName;
  vtkVariant OriginValue;
  bool ArrayNameSet;
  bool CreateGraphVertexIdArray;
  bool ReverseEdges;
  
  
  
  vtkSetStringMacro(ArrayName);

  
  
  
  vtkIdType GetVertexIndex(
    vtkAbstractArray *abstract,vtkVariant value);

  vtkBoostBreadthFirstSearchTree(const vtkBoostBreadthFirstSearchTree&);  
  void operator=(const vtkBoostBreadthFirstSearchTree&);  
};

#endif
