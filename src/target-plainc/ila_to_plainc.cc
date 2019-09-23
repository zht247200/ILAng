/// \file
/// The source of the class Ila2PlainC.

#include <ilang/target-plainc/ila_to_plainc.h>

#include <ilang/ila-pass/p_map_child_prog.h>
#include <ilang/ila/ast_fuse.h>
#include <ilang/target-plainc/plainc_ir.h>
#include <ilang/util/log.h>

namespace ilang {

Ila2PlainC::Ila2PlainC(const InstrLvlAbsPtr& m) : m_(m) {
  //
}

Ila2PlainC::~Ila2PlainC() {}

bool Ila2PlainC::Convert() {
  // sanity check -- no non-determinism

  // sanity check -- completeness (optional)

  // rewriting - store-load

  // rewriting - conditional store

  // resolve child-program
  // under invariants and assumptions, the update implies the child decode
  auto res_pass_map_child_prog = PassMapChildProg()(m_);
  // ILA_ASSERT(res_pass_map_child_prog);

  // start converting
  auto ir = PlainCIR::New();

  // state variables
  for (size_t i = 0; i != m_->state_num(); i++) {
    auto gv = ConvertVar(m_->state(i));
    ILA_CHECK(gv) << "Fail converting state var to global var";
    ir->DeclareGlobalVar(gv);
  }

  // input signals (no need to create variables)

  // instructions
  for (size_t i = 0; i != m_->instr_num(); i++) {
    // ILA_INFO << "instr name " << m_->instr(i)->name();

    // call child program
  }

  return true;
}

bool Ila2PlainC::ExportToSingleFile(const std::string& file_name) {
  //
  return true;
}

bool Ila2PlainC::ExportToMultipleFiles(const std::string& dir_path) {
  //
  return true;
}

PCVarPtr Ila2PlainC::ConvertVar(const ExprPtr& e) {
  auto sort_uid = GetUidSort(e->sort());
  switch (sort_uid) {
  // bit-vector
  case AST_UID_SORT::BV: {
    // FIXME
    return PCVar::New(e->name().str(), PCVar::VarType::BOOL);
  }
  // memory
  case AST_UID_SORT::MEM: {
    // FIXME
    return PCVar::New(e->name().str(), PCVar::VarType::BOOL);
  }
  // boolean
  default: { return PCVar::New(e->name().str(), PCVar::VarType::BOOL); }
  }; // switch sort_uid
}

}; // namespace ilang
