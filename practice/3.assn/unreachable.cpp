#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include<string>
using namespace llvm;

namespace {
class MyUnreachablePass : public PassInfoMixin<MyUnreachablePass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
    StringRef funcName = F.getName();
    outs() << "<<" << funcName << ">>\n";
    std::set<std::string> block, succBlock;

    for (auto I = F.begin(); I != F.end(); ++I) {
      BasicBlock &BB = *I;
      outs() << "BasicBlock: " << BB.getName() << "\n";
      block.insert(BB.getName());

      unsigned successorCnt = BB.getTerminator()->getNumSuccessors();
      outs() << "\tSuccessors: total " << successorCnt << " (";
      for (unsigned i = 0; i < successorCnt; ++i){
        outs() << (i == 0 ? "" : " ")
               << BB.getTerminator()->getSuccessor(i)->getName();
        succBlock.insert(BB.getTerminator()->getSuccessor(i)->getName());
      }
        
      outs() << ")\n";
    }



    return PreservedAnalyses::all();
  }
};
}

extern "C" ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "MyUnreachablePass", "v0.1",
    [](PassBuilder &PB) {
      PB.registerPipelineParsingCallback(
        [](StringRef Name, FunctionPassManager &FPM,
           ArrayRef<PassBuilder::PipelineElement>) {
          if (Name == "my-unreachable") {
            FPM.addPass(MyUnreachablePass());
            return true;
          }
          return false;
        }
      );
    }
  };
}
