#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Metadata.h"
#include <map>
#include <list> 
using namespace llvm;

namespace {
  struct SkeletonPass : public FunctionPass {
    static char ID;
    SkeletonPass() : FunctionPass(ID) {}

    void merge_chains(BasicBlock *start, BasicBlock *end, std::map<BasicBlock*, BasicBlock*>* chains, std::map<BasicBlock*, bool> * start_blocks){
        errs() << (*start_blocks)[end] << "\n";
        errs() << ((*chains)[start] == start) << "\n";
        if((*start_blocks)[end] && (*chains)[start] == start) {
           errs() << "merged \n";
           (*start_blocks)[end] = false;
           (*chains)[start] = end;
        }
        return;
    }
      virtual bool runOnFunction(Function &F) {
        std::map<BasicBlock*, BasicBlock*> chains;
        std::map<BasicBlock*, bool> start_blocks;
        std::vector<std::tuple<int,  BasicBlock*,BasicBlock*> > prof_edges;
        std::vector<std::tuple<BasicBlock*,BasicBlock*> > non_profedges;
        for (auto &B: F) {
          BasicBlock *b = dyn_cast <BasicBlock> (&B);
          chains[b] = b; 
          start_blocks[b] = true; 
          Instruction *terminator = b -> getTerminator();
          errs() << "ter " << *(terminator) << "!\n";
          
          BasicBlock * parent = terminator -> getParent();
          uint n = terminator -> getNumSuccessors();
          if (terminator -> hasMetadata()){
            for(int i =0; i < n ; i ++ ) {
              // errs() << "prof " << *cast<ConstantAsMetadata>(terminator -> getMetadata("prof") -> getOperand(i+1))) << "!\n";
              // errs() << "prof " << *(terminator-> getSuccessor(i)) << "!\n";
              prof_edges.push_back({i, parent, terminator-> getSuccessor(i)});
            }
          } else if(terminator -> getNumSuccessors () > 0) {
            non_profedges.push_back({parent, terminator-> getSuccessor(0)});
          }      
        }
        sort(prof_edges.begin(), prof_edges.end());

        // merge
  
        for(int i = 0; i < non_profedges.size() ; i ++ ) {
          BasicBlock *start = std::get<0>(non_profedges.at(i));
          BasicBlock *end = std::get<1>(non_profedges.at(i));
          merge_chains(start, end, &chains, &start_blocks);
        }

        for(int i = prof_edges.size() - 1; i >= 0 ; i --) {
          // traversing edges in descending freq order
          BasicBlock *start = std::get<1>(prof_edges.at(i));
          BasicBlock *end = std::get<2>(prof_edges.at(i));
          merge_chains(start, end, &chains, &start_blocks);
        }
        
        // final order
        // traversing chains
        Function::BasicBlockListType &all_blocks = F.getBasicBlockList();
        Function::iterator InsertPos = F.begin();
        unsigned moved = 0;
        for (auto &B: F) {
          BasicBlock *b = dyn_cast <BasicBlock> (&B);
          if(start_blocks[b]) {
            // start of a chain
            BasicBlock *curr = b; 
            while (true) {
                errs() << "blocks " << *curr << "!\n";
                if (&*InsertPos != curr) {
                  all_blocks.splice(InsertPos, all_blocks, curr);
                  moved += 1;
                }
                InsertPos++;
                if (curr == chains[curr]) 
                  break;
                else curr = chains[curr];
            }
          }
        }
        
        
        
        return moved > 0;
    }
  };
}


char SkeletonPass::ID = 0;

// Register the pass so `opt -skeleton` runs it.
static RegisterPass<SkeletonPass> X("skeleton", "a useless pass");

