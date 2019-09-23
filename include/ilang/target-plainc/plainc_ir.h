/// \file
/// The header of the plain C intermediate representation.

#ifndef ILANG_TARGET_PLAINC_PLAINC_IR_H__
#define ILANG_TARGET_PLAINC_PLAINC_IR_H__

#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

/// \namespace ilang
namespace ilang {

/// \brief Variable of plain C.
class PCVar {
public:
  typedef std::shared_ptr<PCVar> PCVarPtr;

  /// Variable types.
  enum VarType { BOOL = 0, I8, I32, ARR_I8, ARR_I32 };

  // ------------------------- CONSTRUCTOR/DESTRUCTOR ----------------------- //
  /// Constructor
  PCVar(const std::string& name, const VarType& type, const size_t& size);
  /// Default destructor
  ~PCVar();

  // ------------------------- HELPERS -------------------------------------- //
  static PCVarPtr New(const std::string& name, const VarType& type,
                      const size_t& size = 1);

  // ------------------------- ACCESSORS/MUTATORS --------------------------- //
  /// Return the variable name.
  inline const std::string& name() const { return name_; }
  /// Return the variable type.
  inline const VarType& type() const { return type_; }
  /// Return the size of allocated content.
  inline const size_t& size() const { return size_; }

private:
  /// Variable name
  std::string name_;
  /// Variable type
  VarType type_;
  /// Allocated content size
  size_t size_;

}; // PCVar

typedef PCVar::PCVarPtr PCVarPtr;

class PCStmt {
public:
  typedef std::shared_ptr<PCStmt> PCStmtPtr;

  PCStmt();
  ~PCStmt();

  static PCStmtPtr New();

private:
}; // class PCStmt

typedef PCStmt::PCStmtPtr PCStmtPtr;

class PCFunc {
public:
  typedef std::shared_ptr<PCFunc> PCFuncPtr;

  // ------------------------- CONSTRUCTOR/DESTRUCTOR ----------------------- //
  /// Default constructor.
  PCFunc(const std::string& name);
  /// Default destructor.
  ~PCFunc();

  // ------------------------- HELPERS -------------------------------------- //
  static PCFuncPtr New(const std::string& name);

  // ------------------------- METHODS -------------------------------------- //
  bool DeclareInputArg(const PCVarPtr& arg);

private:
  // ------------------------- MEMBERS -------------------------------------- //
  std::string name_;
  std::vector<PCStmtPtr> stmts_;

  // ------------------------- METHODS -------------------------------------- //

}; // class PCFunc

typedef PCFunc::PCFuncPtr PCFuncPtr;

/// \brief The IR of plain C.
class PlainCIR {
public:
  typedef std::shared_ptr<PlainCIR> PlainCIRPtr;

  // ------------------------- CONSTRUCTOR/DESTRUCTOR ----------------------- //
  /// Default constructor.
  PlainCIR();
  /// Default destructor.
  ~PlainCIR();

  // ------------------------- HELPERS -------------------------------------- //
  static PlainCIRPtr New();

  // ------------------------- METHODS -------------------------------------- //
  /// Declare a global variable.
  bool DeclareGlobalVar(const PCVarPtr& gv);
  bool DeclareFunction(const PCFuncPtr& func);

private:
  // ------------------------- MEMBERS -------------------------------------- //
  std::unordered_map<std::string, PCVarPtr> global_vars_;
  std::unordered_map<std::string, PCFuncPtr> functions_;

  // ------------------------- METHODS -------------------------------------- //

}; // PlainCIR

typedef PlainCIR::PlainCIRPtr PlainCIRPtr;

}; // namespace ilang

#endif // ILANG_TARGET_PLAINC_PLAINC_IR_H__
