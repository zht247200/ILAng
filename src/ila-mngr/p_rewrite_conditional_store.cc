/// \file
/// Rewrite the conditional STORE pattern in the AST.

#include <ilang/ila-mngr/pass.h>

#include <ilang/ila-mngr/u_rewriter.h>
#include <ilang/ila/ast_fuse.h>
#include <ilang/util/log.h>

namespace ilang {

class FuncObjRewrCondStore : public FuncObjRewrExpr {
public:
  FuncObjRewrCondStore() : FuncObjRewrExpr({}) {}

private:
  ExprPtr RewriteOp(const ExprPtr e) const {
    if (e->is_mem()) {
      return RewriteMem(e);
    } else {
      return FuncObjRewrExpr::RewriteOp(e);
    }
  }

  ExprPtr RewriteMem(const ExprPtr e) const {
    if (GetUidExprOp(e) == AST_UID_EXPR_OP::ITE) {
      ILA_INFO << "Visit conditional store " << e;
    }
    auto mem = get(e->arg(0));
    return e;
  }

}; // class FuncObjRewrCondStore

bool PassRewriteConditionalStore(const InstrLvlAbsPtr& m) {
  ILA_NOT_NULL(m);

  auto func = FuncObjRewrCondStore();
  auto Rewr = [=, &func](const ExprPtr e) {
    if (e) {
      e->DepthFirstVisitPrePost(func);
      return func.get(e);
    }
    return e;
  };

  return PassRewriteGeneric(m, Rewr);
}

}; // namespace ilang
