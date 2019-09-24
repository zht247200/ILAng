/// \file
/// Rewrite the STORE-LOAD pattern in the AST.

#include <ilang/ila-mngr/pass.h>

#include <ilang/ila-mngr/u_rewriter.h>
#include <ilang/ila/ast_fuse.h>
#include <ilang/util/log.h>

namespace ilang {

class FuncObjStoreStore {

public:
  inline const ExprPtrVec& addr() const { return addr_; }
  inline const ExprPtrVec& data() const { return data_; }

  bool pre(const ExprPtr e) {
    ILA_ASSERT(GetUidExprOp(e) == AST_UID_EXPR_OP::LOAD);

    addr_.push_back(e->arg(1));
    data_.push_back(e->arg(2));

    // return true if is store to store
    return e->arg(0)->is_op();
  }

  void post(const ExprPtr e) {}

private:
  ExprPtrVec addr_;
  ExprPtrVec data_;

}; // class FuncObjStoreStore

class FuncObjRewrStoreLoad : public FuncObjRewrExpr {
public:
  FuncObjRewrStoreLoad(const ExprMap& rule) : FuncObjRewrExpr(rule) {}

private:
  ExprPtr RewriteOp(const ExprPtr e) const {
    // override LOAD op; use default otherwise
    auto expr_op_uid = GetUidExprOp(e);
    if (expr_op_uid == AST_UID_EXPR_OP::LOAD) {
      return RewriteLoad(e);
    } else {
      return FuncObjRewrExpr::RewriteOp(e);
    }
  }

  ExprPtr RewriteLoad(const ExprPtr e) const {
    auto mem = get(e->arg(0));
    if (mem->is_var() || mem->is_const()) {
      return e;
    }

    // e = Load(Store(mem', addr', data'), addr)
    //  => ITE(addr == addr', data', Load(mem', addr))
    //
    // e - Load(Store(Store(mem', addr', data'), addr'', data''), addr)
    //  => ITE(addr == addr'',
    //         data'',
    //         ITE(addr == addr',
    //             data',
    //             Load(mem', addr)
    //            )
    //        )

    ILA_ERROR << "TODO: Store-Load pattern " << e;

    // TODO
    auto func = FuncObjStoreStore();
    e->DepthFirstVisitPrePost(func);
    ILA_INFO << func.addr().size();
    ILA_INFO << func.data().size();

    return e;
  }

}; // class FuncObjRewrStoreLoad

bool PassRewriteStoreLoad(const InstrLvlAbsPtr& m) {
  ILA_NOT_NULL(m);

  // function object of the rewriting rule
  auto func = FuncObjRewrStoreLoad({});
  auto Rewr = [=, &func](const ExprPtr e) {
    if (e) {
      e->DepthFirstVisitPrePost(func);
      return func.get(e);
    }
    return e;
  };

  // rewrite valid
  auto new_valid = Rewr(m->valid());
  if (new_valid) {
    m->ForceSetValid(new_valid);
  }

  // rewrite fetch
  auto new_fetch = Rewr(m->fetch());
  if (new_fetch) {
    m->ForceSetFetch(new_fetch);
  }

  // TODO rewrite init

  // for each instruction
  for (size_t i = 0; i < m->instr_num(); i++) {
    auto instr = m->instr(i);

    // rewrite decode
    auto new_decode = Rewr(instr->decode());
    if (new_decode) {
      instr->ForceSetDecode(new_decode);
    }

    // rewrite updates
    for (size_t s = 0; s < m->state_num(); s++) {
      auto new_update = Rewr(instr->update(m->state(s)));
      if (new_update) {
        instr->ForceAddUpdate(m->state(s)->name().str(), new_update);
      }
    }
  }

  // traverse the ILA hierarchy
  for (size_t c = 0; c < m->child_num(); c++) {
    PassRewriteStoreLoad(m->child(c));
  }

  return true;
}

}; // namespace ilang
