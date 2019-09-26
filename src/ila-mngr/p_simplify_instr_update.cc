/// \file
/// Simplify instruction state update functions.

#include <ilang/ila-mngr/pass.h>

#include <ilang/ila-mngr/u_rewriter.h>
#include <ilang/util/log.h>

namespace ilang {

bool SimplifyInstrUpdateTemplate(const InstrLvlAbsPtr& m,
                                 std::function<ExprPtr(const ExprPtr)> Simp) {
  ILA_NOT_NULL(m);

  // for each instruction
  for (size_t i = 0; i < m->instr_num(); i++) {
    // for each state
    for (size_t s = 0; s < m->state_num(); s++) {
      auto state_var = m->state(s);
      auto new_update = Simp(m->instr(i)->update(state_var));
      if (new_update) {
        m->instr(i)->ForceAddUpdate(state_var->name().str(), new_update);
      }
    }
  }

  for (size_t c = 0; c < m->child_num(); c++) {
    SimplifyInstrUpdateTemplate(m->child(c), Simp);
  }

  return true;
}

bool PassSimplifyInstrUpdate(const InstrLvlAbsPtr& m) {
  ILA_NOT_NULL(m);

  // pattern - trivial w.r.t. decode

  // pattern - trivial w.r.t. valid

  // pattern - dead branch

  return true;
}

}; // namespace ilang
