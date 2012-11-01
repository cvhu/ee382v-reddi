//===-- RegAllocBase.cpp - Register Allocator Base Class ------------------===//
//
// 	   Name 1: Yilin Zhang
//     UTEID 1: yz3383
// 
//     Name 2: Chinwei Hu
//     UTEID 2: ch26773
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the RegAllocBase class which provides comon functionality
// for LiveIntervalUnion-based register allocators.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "regalloc"
#include "RegAllocBase.h"
#include "LiveRegMatrix.h"
#include "Spiller.h"
#include "VirtRegMap.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/CodeGen/LiveIntervalAnalysis.h"
#include "llvm/CodeGen/LiveRangeEdit.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetRegisterInfo.h"
#ifndef NDEBUG
#include "llvm/ADT/SparseBitVector.h"
#endif
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Timer.h"

using namespace llvm;

STATISTIC(NumNewQueued    , "Number of new live ranges queued");

// Temporary verification option until we can put verification inside
// MachineVerifier.
static cl::opt<bool, true>
VerifyRegAlloc("verify-regalloc", cl::location(RegAllocBase::VerifyEnabled),
               cl::desc("Verify during register allocation"));

const char *RegAllocBase::TimerGroupName = "Register Allocation";
bool RegAllocBase::VerifyEnabled = false;

//===----------------------------------------------------------------------===//
//                         RegAllocBase Implementation
//===----------------------------------------------------------------------===//

void RegAllocBase::init(VirtRegMap &vrm,
                        LiveIntervals &lis,
                        LiveRegMatrix &mat) {
  TRI = &vrm.getTargetRegInfo();
  MRI = &vrm.getRegInfo();
  VRM = &vrm;
  LIS = &lis;
  Matrix = &mat;
  MRI->freezeReservedRegs(vrm.getMachineFunction());
  RegClassInfo.runOnMachineFunction(vrm.getMachineFunction());
}

// Visit all the live registers. If they are already assigned to a physical
// register, unify them with the corresponding LiveIntervalUnion, otherwise push
// them on the priority queue for later assignment.
void RegAllocBase::seedLiveRegs() {
  NamedRegionTimer T("Seed Live Regs", TimerGroupName, TimePassesIsEnabled);
  for (unsigned i = 0, e = MRI->getNumVirtRegs(); i != e; ++i) {
    unsigned Reg = TargetRegisterInfo::index2VirtReg(i);
    if (MRI->reg_nodbg_empty(Reg))
      continue;
    enqueue(&LIS->getInterval(Reg));
  }
}

// Top-level driver to manage the queue of unassigned VirtRegs and call the
// selectOrSplit implementation.
void RegAllocBase::allocatePhysRegs() {
  seedLiveRegs();


  // Continue assigning vregs one at a time to available physical registers.
  while (LiveInterval *VirtReg = dequeue()) {
    assert(!VRM->hasPhys(VirtReg->reg) && "Register already assigned");

    // Unused registers can appear when the spiller coalesces snippets.

    // MISSING : If the register is unused, eliminate it from the 
    //             Live Intervals of the class.
    if (MRI->reg_nodbg_empty(VirtReg->reg)){//reg_empty - Return true if only debug use
        LIS->removeInterval(VirtReg->reg);
		// continue;
    }

    // Invalidate all interference queries, live ranges could have changed.
    Matrix->invalidateVirtRegs();

    // selectOrSplit requests the allocator to return an available physical
    // register if possible and populate a list of new live intervals that
    // result from splitting.
    DEBUG(dbgs() << "\nselectOrSplit "
                 << MRI->getRegClass(VirtReg->reg)->getName()
                 << ':' << PrintReg(VirtReg->reg) << ' ' << *VirtReg << '\n');
    typedef SmallVector<LiveInterval*, 4> VirtRegVec;
    VirtRegVec SplitVRegs;



    // MISSING: Find a physical register to assign to VirtReg, using 
    //          functions from RegAllocGreedy.
    unsigned assigned_phy_reg = selectOrSplit(*VirtReg, SplitVRegs);
    

    // MISSING: If no physical register can be assigned to the virtual
    //          register, print an error message and return.
    if (assigned_phy_reg == ~0u){
        DEBUG (dbgs()<< "No available physical register for current virtual register\n");
    }


    // MISSING: If a physical register can be assigned, then 
    //            assign it to the virtual register, updating 
    //          Matrix from RegAllocBase.h

    if (assigned_phy_reg != 0){//0 means this vreg is spilled, not allocation for it
        Matrix->assign(*VirtReg, assigned_phy_reg);
    }


    for (VirtRegVec::iterator I = SplitVRegs.begin(), E = SplitVRegs.end();
         I != E; ++I) {
      LiveInterval *SplitVirtReg = *I;
      assert(!VRM->hasPhys(SplitVirtReg->reg) && "Register already assigned");
      if (MRI->reg_nodbg_empty(SplitVirtReg->reg)) {
        DEBUG(dbgs() << "not queueing unused  " << *SplitVirtReg << '\n');
        LIS->removeInterval(SplitVirtReg->reg);
        continue;
      }
      DEBUG(dbgs() << "queuing new interval: " << *SplitVirtReg << "\n");
      assert(TargetRegisterInfo::isVirtualRegister(SplitVirtReg->reg) &&
             "expect split value in virtual register");
      enqueue(SplitVirtReg);
      ++NumNewQueued;
    }
  }
}
