/// \file
/// ILA pass - create and map child programs to instructions

#include <ilang/ila-pass/p_map_child_prog.h>

#include <ilang/ila/expr_fuse.h>
#include <ilang/util/log.h>
#include <ilang/verification/unroller.h>

namespace ilang {

PassMapChildProg::PassMapChildProg() {}

PassMapChildProg::~PassMapChildProg() {}

bool InferCFG(const InstrLvlAbsPtr& m) {
  ILA_NOT_NULL(m);

  // iterate through child-ILAs
  for (size_t i = 0; i < m->child_num(); i++) {
    auto child = m->child(i);

    // check if the child program is defined
    if (!child->instr_seq()) {

      // check if a can trigger b
      auto CheckCausality = [=](InstrPtr a, InstrPtr b) {
        z3::context ctx;
        z3::solver s(ctx);
        PathUnroll unroller(ctx);

        // a.decode && a.update -> b.decode
        auto path = unroller.PathAssn({a});
        auto decode = unroller.GetZ3Expr(b->decode(), 1);
        s.add(path && decode);

        auto res = s.check();
        if (res == z3::sat) {
          ILA_INFO << a << " -> " << b;
          child->AddSeqTran(a, b, ExprFuse::BoolConst(true));
        }
      };

      // iterate through child-instruction combination
      for (size_t j = 0; j < child->instr_num(); j++) {
        for (size_t k = j + 1; k < child->instr_num(); k++) {
          CheckCausality(child->instr(j), child->instr(k));
          CheckCausality(child->instr(k), child->instr(j));
        }
      }
    }

    // check if the CFG is inferred
    ILA_WARN_IF(!child->instr_seq()) << "Fail to infer CFG for " << child;

    // traverse the hierarchy
    InferCFG(child);
  }

  return true;
}

bool MapEntryPoint(const InstrLvlAbsPtr& m) {
  ILA_NOT_NULL(m);

  // check if a can trigger b
  auto CheckCausality = [=](InstrPtr a, InstrPtr b) {
    z3::context ctx;
    z3::solver s(ctx);
    PathUnroll unroller(ctx);

    // a.decode && a.update && !b.valid -> b.valid && b.decode
    auto path = unroller.PathAssn({a});

    auto decode = unroller.GetZ3Expr(b->decode(), 1);

    ILA_NOT_NULL(b->host());
    auto valid_prev = unroller.GetZ3Expr(b->host()->valid(), 0);
    auto valid_next = unroller.GetZ3Expr(b->host()->valid(), 1);

    s.add(!valid_prev && path && decode && valid_next);

    auto res = s.check();
    return (res == z3::sat);
  };

  // for each instructions
  for (size_t i = 0; i < m->instr_num(); i++) {
    auto instr = m->instr(i);

    // for each child-ILAs (child-programs)
    for (size_t j = 0; j < m->child_num(); j++) {
      auto child = m->child(j);

      if (child->instr_seq()) {
        auto entry = child->instr_seq()->root();

        if (entry) { // if root already found

          auto res = CheckCausality(instr, entry);
          if (res && !instr->program()) {
            instr->set_program(child);
          }

        } else { // no root defined

          for (size_t k = 0; k < child->instr_num(); k++) {
            // check if can be triggered
            auto res = CheckCausality(instr, child->instr(k));

            ILA_WARN_IF(res && child->instr_seq()->root())
                << "Multiple entry point of " << child << " " << k;

            if (res && !child->instr_seq()->root()) {
              ILA_INFO << "Set " << child->instr(k) << " as entry of " << child;
              child->instr_seq()->set_root(child->instr(k));

              ILA_INFO << "Set " << child << " as child-program of " << instr;
              if (!instr->program()) {
                instr->set_program(child);
              }
              // break;
            }
          }
        }
      }
    }
  }

  // check if all childs program sequence is defined and has a root
  for (size_t i = 0; i < m->child_num(); i++) {
    auto prog = m->child(i)->instr_seq();
    ILA_WARN_IF(!prog) << "No instr seq found in " << m->child(i);
    ILA_WARN_IF(prog && !prog->root()) << "No root found in " << m->child(i);
  }

  return true;
}

bool PassMapChildProg::operator()(const InstrLvlAbsPtr& m) const {
  ILA_NOT_NULL(m);

  // infer the control flow graph of the child-programs
  auto res_cfg = InferCFG(m);

  // search for parent instructions that trigger the program and set the root
  auto res_map = MapEntryPoint(m);

  return res_cfg && res_map;
}

}; // namespace ilang
