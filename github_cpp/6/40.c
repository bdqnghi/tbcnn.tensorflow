


#ifndef ART_COMPILER_DEX_PASS_ME_H_
#define ART_COMPILER_DEX_PASS_ME_H_

#include <string>
#include "pass.h"

namespace art {


struct BasicBlock;
struct CompilationUnit;
class Pass;


enum OptimizationFlag {
  kOptimizationBasicBlockChange = 1,  
  kOptimizationDefUsesChange = 2,     
  kLoopStructureChange = 4,           
};


class PassMEDataHolder: public PassDataHolder {
  public:
    CompilationUnit* c_unit;
    BasicBlock* bb;
    void* data;               
    bool dirty;               
};

enum DataFlowAnalysisMode {
  kAllNodes = 0,                           
  kPreOrderDFSTraversal,                   
  kRepeatingPreOrderDFSTraversal,          
  kReversePostOrderDFSTraversal,           
  kRepeatingPostOrderDFSTraversal,         
  kRepeatingReversePostOrderDFSTraversal,  
  kPostOrderDOMTraversal,                  
  kTopologicalSortTraversal,               
  kRepeatingTopologicalSortTraversal,      
  kLoopRepeatingTopologicalSortTraversal,  
  kNoNodes,                                
};


class PassME: public Pass {
 public:
  explicit PassME(const char* name, DataFlowAnalysisMode type = kAllNodes,
          unsigned int flags = 0u, const char* dump = "")
    : Pass(name), traversal_type_(type), flags_(flags), dump_cfg_folder_(dump) {
  }

  PassME(const char* name, DataFlowAnalysisMode type, const char* dump)
    : Pass(name), traversal_type_(type), flags_(0), dump_cfg_folder_(dump) {
  }

  PassME(const char* name, const char* dump)
    : Pass(name), traversal_type_(kAllNodes), flags_(0), dump_cfg_folder_(dump) {
  }

  ~PassME() {
  }

  virtual DataFlowAnalysisMode GetTraversal() const {
    return traversal_type_;
  }

  const char* GetDumpCFGFolder() const {
    return dump_cfg_folder_;
  }

  bool GetFlag(OptimizationFlag flag) const {
    return (flags_ & flag);
  }

 protected:
  
  const DataFlowAnalysisMode traversal_type_;

  
  const unsigned int flags_;

  
  const char* const dump_cfg_folder_;
};
}  
#endif  
