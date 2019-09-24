/// \file
/// ILA passes

#ifndef ILANG_ILA_MNGR_PASS_H__
#define ILANG_ILA_MNGR_PASS_H__

#include <ilang/ila/instr_lvl_abs.h>

/// \namespace ilang
namespace ilang {

/// Infer the control flow graph among the child-instructions (instr. seq.)
bool PassInferChildProgCFG(const InstrLvlAbsPtr& m);

/// Map the child program (and its entry point) to the parent instruction
bool PassMapChildProgEntryPoint(const InstrLvlAbsPtr& m);

/// Rewrite the conditional STORE in the AST.
bool PassRewriteConditionalStore(const InstrLvlAbsPtr& m);

/// Rewrite the STORE-LOAD pattern in the AST.
bool PassRewriteStoreLoad(const InstrLvlAbsPtr& m);

}; // namespace ilang

#endif // ILANG_ILA_MNGR_PASS_H__
