/// \file
/// Simplify instruction state update functions.

#include <ilang/ila-mngr/pass.h>

#include <ilang/ila/z3_expr_adapter.h>
#include <ilang/util/log.h>

namespace ilang {

bool SimplifyInstrUpdateTemplate(
    const InstrLvlAbsPtr& m,
    std::function<ExprPtr(const ExprPtr, const InstrPtr)> Simp) {
  ILA_NOT_NULL(m);

  // for each instruction
  for (size_t i = 0; i < m->instr_num(); i++) {
    // for each state
    for (size_t s = 0; s < m->state_num(); s++) {
      auto state_var = m->state(s);
      auto new_update = Simp(m->instr(i)->update(state_var), m->instr(i));
      if (new_update) {
        ILA_DLOG("PassSimpInstrUpdate")
            << "Simplify " << m->instr(i) << " update of " << state_var;
        m->instr(i)->ForceAddUpdate(state_var->name().str(), new_update);
      }
    }
  }

  for (size_t c = 0; c < m->child_num(); c++) {
    SimplifyInstrUpdateTemplate(m->child(c), Simp);
  }

  return true;
}

class FuncObjEqSubtree {
public:
  FuncObjEqSubtree(const ExprPtr& target, const ExprPtr& assump)
      : target_(target), assump_(assump) {}

  ExprPtr get(const ExprPtr& e) const {
    auto pos = rule_.find(e);
    ILA_CHECK(pos != rule_.end()) << "No mapping for " << e;
    return pos->second;
  }

  bool pre(const ExprPtr e) const {
    auto pos = rule_.find(e);
    return pos != rule_.end(); // if found --> break
  }

  void post(const ExprPtr e) {
    auto dst = Rewrite(e);
    rule_.insert({e, dst}).second;
  }

private:
  ExprMap rule_;
  ExprPtr target_;
  ExprPtr assump_;
  ExprPtr candidate_ = NULL;

  ExprPtr Rewrite(const ExprPtr e) {

    // assump -> (e == target)
    auto CheckEqModAssump = [=](const ExprPtr x) {
      z3::context ctx;
      z3::solver s(ctx);
      auto gen = Z3ExprAdapter(ctx);

      auto ass = gen.GetExpr(assump_);
      auto tar = gen.GetExpr(target_);
      auto can = gen.GetExpr(x);

      s.add(ass && (can != tar));
      return (s.check() == z3::unsat);
    };

    // skip target itself
    if (e == target_) {
      return candidate_ ? candidate_ : e;
    }

    // check equivalence if not found yet and have a same type
    if (!candidate_ && e->sort() == target_->sort()) {
      if (CheckEqModAssump(e)) {
        ILA_DLOG("PassSimpInstrUpdate") << "Simplify - equivalent sub-tree";
        candidate_ = e;
      }
    }

    return e;
  }

}; // class FuncObjSimpInstrUpdateRedundant

bool PassSimplifyInstrUpdate(const InstrLvlAbsPtr& m) {
  ILA_NOT_NULL(m);

  // pattern - equivalent sub-tree modulo valid and decode
  auto SimpEqSubtree = [=](const ExprPtr e, const InstrPtr i) {
    auto host = i->host();
    ILA_NOT_NULL(host);

    auto valid = host->valid();
    ILA_NOT_NULL(valid);
    auto decode = i->decode();
    ILA_NOT_NULL(decode);

    auto func = FuncObjEqSubtree(e, ExprFuse::And(valid, decode));
    e->DepthFirstVisitPrePost(func);
    return func.get(e);
  };

  auto res_eq_subtree = SimplifyInstrUpdateTemplate(m, SimpEqSubtree);

  // pattern - dead branch

  return res_eq_subtree;
}

}; // namespace ilang
