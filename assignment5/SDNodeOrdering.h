//===-- llvm/CodeGen/SDNodeOrdering.h - SDNode Ordering ---------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the SDNodeOrdering class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CODEGEN_SDNODEORDERING_H
#define LLVM_CODEGEN_SDNODEORDERING_H

#include "llvm/ADT/DenseMap.h"

namespace llvm {

class SDNode;

/// SDNodeOrdering - Maps a unique (monotonically increasing) value to each
/// SDNode that roughly corresponds to the ordering of the original LLVM
/// instruction. This is used for turning off scheduling, because we'll forgo
/// the normal scheduling algorithms and output the instructions according to
/// this ordering.
class SDNodeOrdering {
  DenseMap<const SDNode*, unsigned> OrderMap;

  void operator=(const SDNodeOrdering&);   // Do not implement.
  SDNodeOrdering(const SDNodeOrdering&);   // Do not implement.
public:
  SDNodeOrdering() {}

  void add(const SDNode *Node, unsigned O) {
    /* MISSING :
       
       Set 'Node' to O in OrderMap.

    */

		// http://legup.eecg.utoronto.ca/doxygen/classllvm_1_1DenseMap.html

		OrderMap[Node] = 0;
  }
  void remove(const SDNode *Node) {
    /*
      MISSING:
      Find 'Node' in OrderMap and eliminate it 
    */
		OrderMap.erase(Node);

  }
  void clear() {
    /* 
       MISSING:
       Remove all nodes from OrderMap.
    */
		OrderMap.clear();

  }
  unsigned getOrder(const SDNode *Node) {
    /*
      MISSING:
      Return the ordering assigned to 'Node', according to OrderMap.
    */
		return OrderMap[Node];

  }
};

} // end llvm namespace

#endif
