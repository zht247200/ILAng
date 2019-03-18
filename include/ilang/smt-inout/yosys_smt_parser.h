/// \file Parser for SMT-LIB2 generated by Yosys
/// the use of it is
///   1. translate data-type to bitvector declarations
///   2. add a no-change transition function
///   3. change variable name to their meaningful names

#ifndef YOSYS_SMT_PARSER_H__
#define YOSYS_SMT_PARSER_H__

#include <ilang/smt-inout/smt_ast.h>

#include <iostream>
#include <string>
#include <set>

namespace ilang {
namespace smt {

/// \brief to parse an smt file
/// this will only work on the yosys's generated smt
/// and not on the assemblied CHC
class YosysSmtParser {
  // ---------------- TYPE DEFs -------------------- //
protected:
  /// the internal smt-ast
  smt_file smt_ast;
  /// the datatype defs without datatypes
  datatypes_t flatten_datatype;
  // ------------- HELPER FUNCTIONS ---------------- //
  /// construct flatten_datatype (hierarchically)
  void construct_flatten_dataype();
  /// replace function body and argument 
  void replace_all_function_arg_body();
  /// add the no-change-function (hierarchically)
  void add_no_change_function();

public:
  // ----------- HELPER FUNCTIONS - Low Level ----- //
  /// convert a flatten_datatype to function arg
  static void convert_flatten_datatype_to_arg_vec(
    const std::vector<state_var_t> & , std::vector<arg_t> &,
    const std::string & suffix);
  /// convert a flatten_datatype to function type decl
  static void convert_datatype_to_type_vec(
    const std::vector<state_var_t> & all_flattened_state_var,
    std::vector<var_type> & args);
  /// add a suffix (for next state)
  static std::string st_name_add_suffix (const std::string & stname,
    const std::string & suffix);
  /// add a prefix (for state name)
  std::string YosysSmtParser::st_name_add_prefix(
    const std::string & stname,
    const std::string & prefix);
  /// extract list from a space seped text 
  static std::vector<std::string> str_to_list(const std::string & in);

protected:
  // ----------- HELPER FUNCTIONS - Low Level ----- //
  /// replace : handle a func_body
  std::string replace_a_body( 
    const std::string & current_module,
    const std::map<std::string,state_var_t> & current_mod_state_var_idx,
    const std::vector<std::string> & arg_def, // [state] or [state,next_state]
    const std::set<std::string> & defined_func, 
    const std::string & body_text );
  /// replace : handle a func (arg) and invoke the body repl part
  void replace_a_func( 
    std::shared_ptr<func_def_t> fn,
    const std::string & current_module, 
    // string -> state_var of current map
    const std::map<std::string,state_var_t> & current_mod_state_var_idx,
    const std::set<std::string> & defined_func);

public:
  // -------------- CONSTRUCTOR -------------------- //
  YosysSmtParser(const std::string & buf);
  // -------------- Procedures -------------------- //
  /// Process (replace and add)
  void BreakDatatypes();
  /// Add the no change function
  void AddNoChangeStateUpdateFunction();
  /// Export to string
  std::string Export();
  // -------------- Helpers -------------------- //
  /// return a reference to module def order
  const std::vector<std::string> & get_module_def_orders() const;
  /// return a module's flatten datatypes
  const std::vector<state_var_t> & get_module_flatten_dt(const std::string & mod_name) const;
}; // class YosysSmtParser

}; // namespace smt
}; // namespace ilang

#endif