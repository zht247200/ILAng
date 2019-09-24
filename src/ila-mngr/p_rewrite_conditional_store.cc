/// \file
/// Rewrite the conditional STORE pattern in the AST.

#include <ilang/ila-mngr/pass.h>

#include <ilang/util/log.h>

namespace ilang {

bool PassRewriteConditionalStore(const InstrLvlAbsPtr& m) {
  ILA_NOT_NULL(m);

  // traverse the ILA hierarchy
  for (size_t c = 0; c < m->child_num(); c++) {
    PassRewriteStoreLoad(m->child(c));
  }

  return true;
}

}; // namespace ilang
