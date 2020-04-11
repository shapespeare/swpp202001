#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include<string>
using namespace llvm;

void counter(BasicBlock &CC, std::set<std::string> &succBlock){
  succBlock.insert(CC.getName().str());
  if (CC.getTerminator()->getNumSuccessors() == 0)  return;
  for (unsigned i = 0; i < CC.getTerminator()->getNumSuccessors(); ++i){
    if (succBlock.find(CC.getTerminator()->getSuccessor(i)->getName().str()) != succBlock.end()) return;
    counter(*(CC.getTerminator()->getSuccessor(i)), succBlock);
  }  
}

namespace {
class MyUnreachablePass : public PassInfoMixin<MyUnreachablePass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
    StringRef funcName = F.getName();
    std::set<std::string> block;
    std::set<std::string> succBlock;
    std::set<std::string>::iterator itB;

    for (auto I = F.begin(); I != F.end(); ++I) {
      BasicBlock &BB = *I;
      block.insert(BB.getName().str());
    }

    auto K = F.begin();
    BasicBlock &CC = *K;
    counter(CC, succBlock);

    for (itB = succBlock.begin(); itB != succBlock.end(); itB++){
      if (block.find(*itB) != block.end())  block.erase(block.find(*itB));
    }
    for (itB = block.begin(); itB != block.end(); itB++)
      outs() << *itB << "\n";

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
