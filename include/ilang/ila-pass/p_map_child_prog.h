/// \file
/// ILA pass - create and map child programs to instructions

#ifndef ILANG_ILA_PASS_P_MAP_CHILD_PROG_H__
#define ILANG_ILA_PASS_P_MAP_CHILD_PROG_H__

#include <ilang/ila/instr_lvl_abs.h>

/// \namespace ilang
namespace ilang {

/// \brief ILA pass - create and map child programs to instructions
class PassMapChildProg {
public:
  // ------------------------- CONSTRUCTOR/DESTRUCTOR ----------------------- //
  /// Default constructor.
  PassMapChildProg();
  /// Default destructor.
  ~PassMapChildProg();

  // ------------------------- HELPERS -------------------------------------- //

  // ------------------------- METHODS -------------------------------------- //
  bool operator()(const InstrLvlAbsPtr& m) const;

private:
  // ------------------------- MEMBERS -------------------------------------- //

  // ------------------------- METHODS -------------------------------------- //

}; // class PassMapChildProg

}; // namespace ilang

#endif // ILANG_ILA_PASS_P_MAP_CHILD_PROG_H__
