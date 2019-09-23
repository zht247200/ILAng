/// \file
/// The source of the plain C intermediate representation.

#include <ilang/target-plainc/plainc_ir.h>

#include <ilang/util/log.h>

namespace ilang {

PCVar::PCVar(const std::string& name, const VarType& type, const size_t& size)
    : name_(name), type_(type), size_(size) {
  ILA_CHECK_NE(name, "") << "Require non-empty variable name.";

  if ((type == VarType::ARR_I8) || (type == VarType::ARR_I32))
    ILA_WARN_IF(size <= 1) << "Declaring array " << name_ << " with size <= 1";
}

PCVar::~PCVar() {}

PCVarPtr PCVar::New(const std::string& name, const VarType& type,
                    const size_t& size) {
  return std::make_shared<PCVar>(name, type, size);
}

PCFunc::PCFunc(const std::string& name) : name_(name) {
  //
}

PCFunc::~PCFunc() {
  //
}

PlainCIR::PlainCIR() {
  //
}

PlainCIR::~PlainCIR() {
  //
}

PlainCIRPtr PlainCIR::New() { return std::make_shared<PlainCIR>(); }

bool PlainCIR::DeclareGlobalVar(const PCVarPtr& gv) {
  auto pos = global_vars_.find(gv->name());
  if (pos != global_vars_.end()) {
    ILA_CHECK_EQ(gv->type(), pos->second->type()) << "Var type inconsistent";
    ILA_CHECK_EQ(gv->size(), pos->second->size()) << "Var size inconsistent";
  } else {
    global_vars_[gv->name()] = gv;
  }
  return true;
}

}; // namespace ilang
