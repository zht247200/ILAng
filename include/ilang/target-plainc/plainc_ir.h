/// \file
/// The header of the plain C intermediate representation.

#ifndef ILANG_TARGET_PLAINC_PLAINC_IR_H__
#define ILANG_TARGET_PLAINC_PLAINC_IR_H__

#include <set>
#include <string>

/// \namespace ilang
namespace ilang {

/// \brief Variable of plain C.
class PlainCVar {
public:
  /// Variable types.
  enum VarType { BOOL = 0, I8, I32, ARR_I8, ARR_I32 };

  // ------------------------- CONSTRUCTOR/DESTRUCTOR ----------------------- //
  /// Constructor
  PlainCVar(const VarType& type, const size_t& size = 1);
  /// Default destructor
  ~PlainCVar();

  // ------------------------- ACCESSORS/MUTATORS --------------------------- //
  /// Return the variable type.
  inline const VarType& type() const { return type_; }
  /// Return the size of allocated content.
  inline const size_t& size() const { return size_; }

private:
  /// Variable type
  VarType type_;
  /// Allocated content size
  size_t size_;

}; // PlainCVar

/// \brief The IR of plain C.
class PlainCIR {
public:
  // ------------------------- CONSTRUCTOR/DESTRUCTOR ----------------------- //
  /// Default constructor.
  PlainCIR();
  /// Default destructor.
  ~PlainCIR();

  // ------------------------- METHODS -------------------------------------- //

private:
  // ------------------------- MEMBERS -------------------------------------- //
  std::set<std::string> global_vars_;

  // ------------------------- METHODS -------------------------------------- //

}; // PlainCIR

}; // namespace ilang

#endif // ILANG_TARGET_PLAINC_PLAINC_IR_H__
