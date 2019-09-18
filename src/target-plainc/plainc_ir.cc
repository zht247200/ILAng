/// \file
/// The source of the plain C intermediate representation.

#include <ilang/target-plainc/plainc_ir.h>

#include <ilang/util/log.h>

namespace ilang {

PlainCVar::PlainCVar(const VarType& type, const size_t& size)
    : type_(type), size_(size) {
  ILA_WARN_IF(((type == VarType::ARR_I8) || (type == VarType::ARR_I32)) &&
              size <= 1)
      << "Declaring array with size <= 1";
}

PlainCVar::~PlainCVar() {}

PlainCIR::PlainCIR() {
  //
}

PlainCIR::~PlainCIR() {
  //
}

}; // namespace ilang
