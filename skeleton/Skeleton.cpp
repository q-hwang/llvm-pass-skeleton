#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Metadata.h"
#include <map>
#include <list> 
#include "llvm/IR/Constants.h"

using namespace llvm;

namespace {
  struct SkeletonPass : public FunctionPass {
    static char ID;
    SkeletonPass() : FunctionPass(ID) {}

    void merge_chains(BasicBlock *fb, BasicBlock *start, BasicBlock *end, std::map<BasicBlock*, BasicBlock*>* chains, std::map<BasicBlock*, bool> * start_blocks){
   
        if((*start_blocks)[end] && (*chains)[start] == start && end != fb) {

            // errs() << "merge start " << *start << "!\n";
            // errs() << "merge end " << *end << "!\n";
           (*start_blocks)[end] = false;
           (*chains)[start] = end;
        }
        return;
    }

    BasicBlock* insert_chain(BasicBlock *start, std::map<BasicBlock*, bool> &start_blocks, std::map<BasicBlock*, BasicBlock*> &chains, Function::iterator & InsertPos, Function::BasicBlockListType &all_blocks, uint* moved){
        BasicBlock *next_start_block = nullptr;
        uint max_cross_weight = 0;

        BasicBlock *curr = start; 
        while (true) {       
            // insert      
            if (&*InsertPos != curr) {
                all_blocks.splice(InsertPos, all_blocks, curr);
              moved += 1;
            } else{
              InsertPos ++;
            }
            start_blocks[curr] = false;
            BasicBlock *next = chains[curr];

            Instruction * terminator = curr -> getTerminator();
            MDNode * prof_n = terminator -> getMetadata("prof") ;
            uint n = terminator -> getNumSuccessors();
            if (dyn_cast <BranchInst> ( terminator) or dyn_cast <SwitchInst> (terminator)) {
                for(int i =0; i < n ; i ++ ) {
                   BasicBlock * succ = terminator -> getSuccessor(i);
                   uint weight =  mdconst::dyn_extract<ConstantInt>(prof_n -> getOperand(i+1))->getZExtValue();
                   if( succ != next && start_blocks[succ] &&weight > max_cross_weight) {
                     next_start_block = succ;
                     max_cross_weight = weight;
                   }
                }
            }

            if(curr == next) break;
            curr = next;
        }
        return next_start_block;
    }

      virtual bool runOnFunction(Function &F) {
        std::map<BasicBlock*, BasicBlock*> chains;
        std::map<BasicBlock*, bool> start_blocks;
        std::vector<std::tuple<int,  BasicBlock*,BasicBlock*> > prof_edges;
        std::vector<std::tuple<BasicBlock*,BasicBlock*> > non_profedges;
        std::vector<BasicBlock*> v_blocks;
        bool first = true;
        BasicBlock* fb  ;
        for (auto &B: F) {
          BasicBlock *b = dyn_cast <BasicBlock> (&B);
          if (first) {

            first = false;
            fb = b;
          }
          chains[b] = b; 
          start_blocks[b] = true; 
          v_blocks.push_back(b);
          Instruction *terminator = b -> getTerminator();
          
          BasicBlock * parent = terminator -> getParent();
          MDNode * prof_n = terminator -> getMetadata("prof") ;
          uint n = terminator -> getNumSuccessors();
          if (terminator -> hasMetadata() and prof_n and (prof_n->getNumOperands() == n+1)){
            for(int i =0; i < n ; i ++ ) {
              uint weight =  mdconst::dyn_extract<ConstantInt>(prof_n -> getOperand(i+1))->getZExtValue();
              if (dyn_cast <BranchInst> (terminator) or dyn_cast <SwitchInst> (terminator)) {
                prof_edges.push_back({i, parent, terminator-> getSuccessor(i)});
              }
            }
          } else if(dyn_cast <BranchInst> (terminator) and terminator -> getNumSuccessors () == 1) {
            non_profedges.push_back({parent, terminator-> getSuccessor(0)});
          }      
        }
        std::sort(prof_edges.begin(), prof_edges.end());


        // merge
  
        for(int i = 0; i < non_profedges.size() ; i ++ ) {
          BasicBlock *start = std::get<0>(non_profedges.at(i));
          BasicBlock *end = std::get<1>(non_profedges.at(i));
          merge_chains(fb, start, end, &chains, &start_blocks);
        }

        for(int i = prof_edges.size() - 1; i >= 0 ; i --) {
          // traversing edges in descending freq order
          BasicBlock *start = std::get<1>(prof_edges.at(i));
          BasicBlock *end = std::get<2>(prof_edges.at(i));
          merge_chains(fb,start, end, &chains, &start_blocks);
        }
        
        
        // final order
        // traversing chains
        Function::BasicBlockListType &all_blocks = F.getBasicBlockList();
        Function::iterator InsertPos = F.begin();
        unsigned moved = 0;
        
        BasicBlock *start_block = &F.getEntryBlock();
        while(start_block != nullptr) {
          start_block = insert_chain(start_block, start_blocks, chains, InsertPos, all_blocks, &moved);
        }
   
        std::vector<BasicBlock*>::iterator b_it =v_blocks.begin();
        while (b_it != v_blocks.end()) {
          BasicBlock *b = *b_it;
          if(start_blocks[b]) {
            // start of a chain
            insert_chain(b, start_blocks, chains, InsertPos, all_blocks, &moved);
          }
          b_it ++;
        }

        return moved > 0;
    }
  };
}



char SkeletonPass::ID = 0;

// Register the pass so `opt -skeleton` runs it.
static RegisterPass<SkeletonPass> X("skeleton", "a useless pass");