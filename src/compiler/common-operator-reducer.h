// Copyright 2014 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_COMPILER_COMMON_OPERATOR_REDUCER_H_
#define V8_COMPILER_COMMON_OPERATOR_REDUCER_H_

#include "src/compiler/graph-reducer.h"

namespace v8 {
namespace internal {
namespace compiler {

// Forward declarations.
class CommonOperatorBuilder;
class Graph;
class MachineOperatorBuilder;
class Operator;


// Performs strength reduction on nodes that have common operators.
class CommonOperatorReducer final : public AdvancedReducer {
 public:
  CommonOperatorReducer(Editor* editor, Graph* graph,
                        CommonOperatorBuilder* common,
                        MachineOperatorBuilder* machine)
      : AdvancedReducer(editor),
        graph_(graph),
        common_(common),
        machine_(machine) {}
  ~CommonOperatorReducer() final {}

  Reduction Reduce(Node* node) final;

 private:
  Reduction ReduceEffectPhi(Node* node);
  Reduction ReducePhi(Node* node);
  Reduction ReduceSelect(Node* node);

  Reduction Change(Node* node, Operator const* op, Node* a);
  Reduction Change(Node* node, Operator const* op, Node* a, Node* b);

  Graph* graph() const { return graph_; }
  CommonOperatorBuilder* common() const { return common_; }
  MachineOperatorBuilder* machine() const { return machine_; }

  Graph* const graph_;
  CommonOperatorBuilder* const common_;
  MachineOperatorBuilder* const machine_;
};

}  // namespace compiler
}  // namespace internal
}  // namespace v8

#endif  // V8_COMPILER_COMMON_OPERATOR_REDUCER_H_
