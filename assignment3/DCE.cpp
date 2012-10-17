//===- DCE.cpp - Code to perform dead code elimination --------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements dead inst elimination and dead code elimination.
//
// Dead Inst Elimination performs a single pass over the function removing
// instructions that are obviously dead.  Dead Code Elimination is similar, but
// it rechecks instructions that were used by removed instructions to see if
// they are newly dead.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "dce"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Utils/Local.h"
#include "llvm/Instruction.h"
#include "llvm/Pass.h"
#include "llvm/Support/InstIterator.h"
#include "llvm/ADT/Statistic.h"
using namespace llvm;

#include "llvm/Support/raw_ostream.h"

STATISTIC(DIEEliminated, "Number of insts removed by DIE pass");
STATISTIC(DCEEliminated, "Number of insts removed");

namespace {
    //===--------------------------------------------------------------------===//
    // DeadInstElimination pass implementation
    //
    struct DeadInstElimination : public BasicBlockPass {
        static char ID; // Pass identification, replacement for typeid
        DeadInstElimination() : BasicBlockPass(ID) {
            initializeDeadInstEliminationPass(*PassRegistry::getPassRegistry());
        }
        virtual bool runOnBasicBlock(BasicBlock &BB) {
            bool Changed = false;
            for (BasicBlock::iterator DI = BB.begin(); DI != BB.end(); ) {
                Instruction *Inst = DI++;
                if (isInstructionTriviallyDead(Inst)) {
                    Inst->eraseFromParent();
                    Changed = true;
                    ++DIEEliminated;
                }
            }
            return Changed;
        }

        virtual void getAnalysisUsage(AnalysisUsage &AU) const {
            AU.setPreservesCFG();
        }
    };
}

char DeadInstElimination::ID = 0;
INITIALIZE_PASS(DeadInstElimination, "die",
        "Dead Instruction Elimination", false, false)

Pass *llvm::createDeadInstEliminationPass() {
    return new DeadInstElimination();
}


namespace {
    //===--------------------------------------------------------------------===//
    // DeadCodeElimination pass implementation
    //
    struct DCE : public FunctionPass {
        static char ID; // Pass identification, replacement for typeid
        DCE() : FunctionPass(ID) {
            initializeDCEPass(*PassRegistry::getPassRegistry());
        }

        virtual bool runOnFunction(Function &F);

        virtual void getAnalysisUsage(AnalysisUsage &AU) const {
            AU.setPreservesCFG();
        }
    };
}

char DCE::ID = 0;
INITIALIZE_PASS(DCE, "dce", "Dead Code Elimination", false, false)

bool DCE::runOnFunction(Function &F) {



    // Start out with all of the instructions in the worklist...
    std::vector<Instruction*> WorkList;

    // MISSING: Push all of the instructions in function F into the 
    //          worklist.

    // http://llvm.org/docs/ProgrammersManual.html	
    inst_iterator n = inst_end(F);
    for (inst_iterator i = inst_begin(F); i != n; ++i){
        WorkList.push_back(&*i);
    }

    // Loop over the worklist finding instructions that are dead.  If they are
    // dead make them drop all of their uses, making other instructions
    // potentially dead, and work until the worklist is empty.
    //
    bool MadeChange = false;
    while (!WorkList.empty()) {


        // MISSING: Extract an instruction I from the Worklist.
        // http://www.cplusplus.com/reference/stl/vector/
        Instruction *I = WorkList.back();
        WorkList.pop_back();

        // MISSING: If I is trivially dead, then do all of the 
        //          following inside the code of your conditional:

        //          1. Iterate over 
        //          all values used by I (check out the User class and 
        //          how to obtain the uses of instruction)
        //          and put them into the worklist, to see 
        //          whether they might become dead afterwards.

        //          2. Remove instruction I from its parent.

        //          3. Remove instruction I from Worklist, if you can
        //             find it.

        //          4. set MadeChange to true (as you have just removed
        //             at least I, which was a trivially dead inst).

        //          5. Increment the counter of eliminated insts 
        //             by one (DCEEliminated).


        if (isInstructionTriviallyDead(I)){
            User::op_iterator n = I->op_end();
            for (User::op_iterator i = I->op_begin(); i != n; ++i){
                Instruction * used = dyn_cast<Instruction> (*i);
                if (used)
                    WorkList.push_back(dyn_cast<Instruction>(*i));
            }
            I->eraseFromParent();
            //Use one temp WorkList to eliminate two neighbor I situation
            // I I, the second I could survive by previous method
            std::vector<Instruction*> new_WorkList;
            for (std::vector<Instruction*>::iterator i = WorkList.begin(); i != WorkList.end(); ++i){
                if (*i != I)
                    new_WorkList.push_back(*i);
            }
            WorkList = new_WorkList;
            MadeChange = true;
            ++DCEEliminated;
        }











    }

    // TESTING
    llvm::errs()<<"Instructions Eliminated: "<<DCEEliminated<<"\n";
    llvm::errs()<<"Live instructions after DCE:\n";
    for (inst_iterator i = inst_begin(F), e = inst_end(F); i != e; ++i)
        llvm::errs()<<(*i)<<"\n";

    return MadeChange;
}

FunctionPass *llvm::createDeadCodeEliminationPass() {
    return new DCE();
}

