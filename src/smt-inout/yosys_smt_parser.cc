/// \file Parser for SMT-LIB2 generated by Yosys
/// the use of it is
///   1. translate data-type to bitvector declarations
///     a. datatype : recursively defined...
///     b. fix some
///   2. add a no-change transition function
///   3. -- (currently no ) change variable name to their meaningful names

#include <ilang/smt-inout/yosys_smt_parser.h>
#include <ilang/util/container_shortcut.h>
#include <ilang/util/log.h>
#include <ilang/util/str_util.h>

namespace ilang {
namespace smt {

//#define get_mod_name(s) ((s).substr(1,(s).length()-4))
#define get_mod_name(s) (s)

// |module1 inst| -> inst
std::string get_mod_inst_name(const std::string& in) {
  ILA_ASSERT(S_IN(' ', in));
  ILA_ASSERT(in.back() == '|');
  auto pos = in.find(' ') + 1;
  return in.substr(pos, in.length() - pos - 1);
} // get_mod_inst_name

/// construct flatten_datatype (hierarchically)
void YosysSmtParser::construct_flatten_dataype() {
  for (auto&& module_name : smt_ast.data_type_order) {
    ILA_ASSERT(IN(module_name, smt_ast.datatypes));
    {
      auto& state_var_vec = smt_ast.datatypes[module_name];
      // create the same module there
      // one by one insert the elements
      // check if it is Datatype
      // find in the flatten_one, it must exist
      // copy all its var here
      ILA_ASSERT(!IN(module_name, flatten_datatype));
      for (const auto& state_var : state_var_vec) {
        if (state_var._type.is_datatype()) {
          const auto& mod_tp_name = state_var._type.module_name;
          auto inst_name = get_mod_inst_name(state_var.internal_name);
          auto tp_mod_name = get_mod_name(mod_tp_name); // | _s|
          ILA_ASSERT(IN(tp_mod_name, flatten_datatype))
              << "state_var:" << state_var.internal_name << "/"
              << state_var.verilog_name << " mod:" << mod_tp_name
              << " not in flatten_datatype";
          auto& sub_mod_state_var_vec = flatten_datatype[tp_mod_name];
          // from there, insert all the state here
          for (const auto& sub_mod_state_var : sub_mod_state_var_vec) {
            flatten_datatype[module_name].push_back(sub_mod_state_var);
            // you need to rename it
            auto& sub_st_var = flatten_datatype[module_name].back();
            sub_st_var.internal_name =
                st_name_add_prefix(sub_st_var.internal_name, inst_name + ".");
            // sub_st_var.module_name = ? // no one use it
            sub_st_var.verilog_name = inst_name + "." + sub_st_var.verilog_name;
            ILA_ASSERT(!sub_st_var._type.is_datatype());
          }
        } // if itself is a datatype
        else
          flatten_datatype[module_name].push_back(state_var);
      } // for all state_vars under this module name
    }   // end of create the same module there in flatten_...
  }     // for all module in order
} // construct_flatten_dataype

void YosysSmtParser::convert_datatype_to_type_vec(
    const std::vector<state_var_t>& all_flattened_state_var,
    std::vector<var_type>& args) {
  for (auto&& st : all_flattened_state_var) {
    args.push_back(st._type);
  } // just use its internal_name as the arg name
} // convert_datatype_to_type_vec

void YosysSmtParser::convert_flatten_datatype_to_arg_vec(
    const std::vector<state_var_t>& all_flattened_state_var,
    std::vector<arg_t>& args, const std::string& suffix) {
  for (auto&& st : all_flattened_state_var) {
    ILA_ASSERT(!st._type.is_datatype());
    // should already flattened.
    args.push_back(
        arg_t(st_name_add_suffix(st.internal_name, suffix), st._type));
  } // just use its internal_name as the arg name
} // convert_flatten_datatype_to_arg_vec

std::string YosysSmtParser::st_name_add_suffix(const std::string& stname,
                                               const std::string& suffix) {
  if (suffix.empty())
    return stname;
  if (stname.front() == '|' && stname.back() == '|')
    return stname.substr(0, stname.length() - 1) + suffix + "|";
  // else
  return stname + suffix;
} // st_name_add_suffix

std::string YosysSmtParser::st_name_add_prefix(const std::string& stname,
                                               const std::string& prefix) {
  if (prefix.empty())
    return stname;
  if (stname.front() == '|' && stname.back() == '|')
    return "|" + prefix + stname.substr(1);
  // else
  return prefix + stname;
} // st_name_add_suffix

#define sep(c) ((c) == ' ' || (c) == '\t' || (c) == '\n' || (c) == '\r')
std::vector<std::string> YosysSmtParser::str_to_list(const std::string& in) {
  std::vector<std::string> ret_l;
  std::string cur;
  bool in_sep = false;
  for (auto c : in) {
    if (c == '|' && in_sep == false) {
      ILA_ASSERT(cur.empty());
      in_sep = true;
      cur += c;
    } else if (c == '|' && in_sep == true) {
      cur += c;
      in_sep = false;
    } else if (sep(c) && in_sep) {
      cur += c;
    } else if (sep(c) && !in_sep) {
      if (!cur.empty()) {
        ret_l.push_back(cur);
        cur = "";
      }
    } else
      cur += c;
  }
  if (!cur.empty())
    ret_l.push_back(cur);
  return ret_l;
}

// it should also have knowledge of the current
std::string YosysSmtParser::replace_a_body(
    const std::string& current_module,
    // string -> state_var of current map
    const std::map<std::string, state_var_t>& current_mod_state_var_idx,
    const std::vector<std::string>& arg_def, // [state] or [state,next_state]
    const std::set<std::string>& defined_func, const std::string& body_text) {

  std::string ret(body_text);
  std::vector<size_t> left_pos_stack;
  std::vector<bool> leaf_level_flag_stack;
  std::map<std::string, std::string> cached_body_replace;
  std::set<std::string> cached_no_replace;
  auto len = body_text.length();
  // const auto & datatype = smt_ast.datatypes[current_module];

  for (decltype(len) idx = 0; idx < len; ++idx) {
    if (body_text.at(idx) == '(') {
      if (!leaf_level_flag_stack.empty())
        leaf_level_flag_stack.back() = false;
      leaf_level_flag_stack.push_back(true);
      left_pos_stack.push_back(idx);
    } else if (body_text.at(idx) == ')') {
      if (leaf_level_flag_stack.back()) {
        // if it is really a leaf
        auto start_pos = left_pos_stack.back() + 1; // not including '('
        auto leaf_text = body_text.substr(start_pos, idx - start_pos);
        auto leaf_text_w_para = "(" + leaf_text + ")";
        // then ?
        if (!IN(leaf_text_w_para, cached_no_replace) &&
            !IN(leaf_text_w_para, cached_body_replace)) {
          // if it is first time encounter
          auto leaf_vec =
              str_to_list(leaf_text); // SplitSpaceTabEnter(leaf_text);
          if (leaf_vec.size() == 2) {
            if (leaf_vec[1] == arg_def[0]) {
              // state
              const auto& pred = leaf_vec[0];
              // check if it is a function name
              // or if it is a datatype name
              if (IN(pred, defined_func)) { // --> (pred bv1 bv2 bv3)
                std::string arg_use;
                for (auto&& st : flatten_datatype[current_module])
                  arg_use += " " + st.internal_name;
                cached_body_replace.insert(std::make_pair(
                    leaf_text_w_para, "(" + pred + arg_use + ")"));
              } else if (IN(pred, current_mod_state_var_idx)) {
                const auto& st = current_mod_state_var_idx.at(pred);
                if (st._type.is_datatype()) {
                  const auto& mod_full_name = st._type.module_name;
                  auto module_name = get_mod_name(mod_full_name); // | _s|
                  auto mod_inst_name = get_mod_inst_name(pred);
                  const auto& dt = flatten_datatype[module_name];

                  std::vector<std::string> arg_name_vec;
                  bool special_case = false;

                  { // a special case here:
                    // (|simplePipe__DOT__ADD_is| (|wrapper_h m0| state))
                    // where : |simplePipe__DOT__ADD_is| a state pred
                    if (left_pos_stack.size() >= 2 && idx + 1 < len &&
                        body_text.at(idx + 1)) {
                      auto left = *(left_pos_stack.rbegin() + 1);
                      auto right = *(left_pos_stack.rbegin());
                      auto outer_pred =
                          body_text.substr(left + 1, right - 2 - left);
                      const auto& st_vec = smt_ast.datatypes[module_name];
                      for (const auto& st_sub : st_vec) {
                        if (st_sub.internal_name == outer_pred) {
                          auto orig_text =
                              body_text.substr(left, idx + 2 - left);
                          cached_body_replace.insert(std::make_pair(
                              orig_text, st_name_add_prefix(
                                             outer_pred, mod_inst_name + ".")));
                          special_case = true;
                          break;
                        }
                      } // for (search for st)
                    }
                  } // end special case

                  if (!special_case) {
                    // if not found to be the special case, we will do the
                    // normal
                    for (auto&& arg : dt)
                      arg_name_vec.push_back(st_name_add_prefix(
                          arg.internal_name, mod_inst_name + "."));

                    cached_body_replace.insert(std::make_pair(
                        leaf_text_w_para, Join(arg_name_vec, " ")));
                  }
                  // find the flattened
                } else { // a normal replacement
                  cached_body_replace.insert(
                      std::make_pair(leaf_text_w_para, pred));
                } // if datatype or BV/Bool

              } else {
                ILA_ERROR << pred << " is unknown, will not replace";
                cached_no_replace.insert(leaf_text_w_para);
              } // func or datatype element
            } else if (arg_def.size() == 2 && leaf_vec[1] == arg_def[1]) {
              // next_state
              const auto& pred = leaf_vec[0];
              ILA_ASSERT(!IN(pred, defined_func));
              ILA_ASSERT(IN(pred, current_mod_state_var_idx));
              const auto& st = current_mod_state_var_idx.at(pred);
              if (st._type.is_datatype()) {
                const auto& mod_full_name = st._type.module_name;
                auto module_name = get_mod_name(mod_full_name); // | _s|
                auto mod_inst_name = get_mod_inst_name(pred);
                const auto& dt = flatten_datatype[module_name];

                std::vector<std::string> arg_name_vec;
                for (auto&& arg : dt)
                  arg_name_vec.push_back(st_name_add_prefix(
                      st_name_add_suffix(arg.internal_name, "_next"),
                      mod_inst_name + "."));

                cached_body_replace.insert(
                    std::make_pair(leaf_text_w_para, Join(arg_name_vec, " ")));

                // find the flattened
              } else { // a normal replacement
                cached_body_replace.insert(std::make_pair(
                    leaf_text_w_para, st_name_add_suffix(pred, "_next")));
              } // if datatype or BV/Bool
            } else
              cached_no_replace.insert(leaf_text_w_para);
          } else
            cached_no_replace.insert(leaf_text_w_para);
        } // else : cached already, do nothing
      }   // else : not a leaf : do nothing
      //
      left_pos_stack.pop_back();
      leaf_level_flag_stack.pop_back();
    } // else if( right paranthesis)
  }   // for (idx)
  for (const auto& orig_new_pair : cached_body_replace) {
    ILA_ASSERT(!IN(orig_new_pair.first, cached_no_replace));
    ret = ReplaceAll(ret, orig_new_pair.first, orig_new_pair.second);
  }
  return ret;
} // replace_a_body

void YosysSmtParser::replace_a_func(
    std::shared_ptr<func_def_t> fn, const std::string& current_module,
    // string -> state_var of current map
    const std::map<std::string, state_var_t>& current_mod_state_var_idx,
    const std::set<std::string>& defined_func) {
  ILA_ASSERT(fn->args.empty());
  std::vector<std::string> arg_def; // [state] or [state,next_state]
  auto single_state = "((state |" + current_module + "_s|))";
  auto double_state = "((state |" + current_module + "_s|) (next_state |" +
                      current_module + "_s|))";
  if (fn->args_text == single_state) {
    arg_def.push_back("state");
    convert_flatten_datatype_to_arg_vec(flatten_datatype[current_module],
                                        fn->args, "");
  } else if (fn->args_text == double_state) {
    arg_def.push_back("state");
    arg_def.push_back("next_state");
    convert_flatten_datatype_to_arg_vec(flatten_datatype[current_module],
                                        fn->args, "");
    convert_flatten_datatype_to_arg_vec(flatten_datatype[current_module],
                                        fn->args, "_next");
  } else
    ILA_ASSERT(false) << "unhandled: arg" << fn->args_text;
  fn->func_body = replace_a_body(current_module, current_mod_state_var_idx,
                                 arg_def, defined_func, fn->func_body);
} // replace_a_func

/// replace function body and argument
void YosysSmtParser::replace_all_function_arg_body() {
  // now we have flatten_datatype for reference
  // a function should only refer to a mod's own datatype
  // prepare a replace map for it
  // (string --> string)
  // ((state |mod_s|)) -> (flattened, but var name)
  // arg_name, arg_type
  // (|??| state) -> internal_name

  std::map<std::string, state_var_t> current_mod_state_var_cached;
  std::string module_cached;
  std::set<std::string> defined_func;

  for (auto&& one_smt_item_ptr : smt_ast.items) {
    std::shared_ptr<func_def_t> fn =
        std::dynamic_pointer_cast<func_def_t>(one_smt_item_ptr);
    if (!fn) // only handle functions
      continue;
    ILA_ASSERT(!fn->func_module.empty());
    if (fn->func_module != module_cached) { // re-cache
      module_cached = fn->func_module;
      current_mod_state_var_cached.clear();

      for (const auto& st : smt_ast.datatypes[module_cached]) {
        ILA_ASSERT(!st.internal_name.empty());
        current_mod_state_var_cached.insert(
            std::make_pair(st.internal_name, st));
      }
    } // end of re-cache
    replace_a_func(fn, fn->func_module, current_mod_state_var_cached,
                   defined_func);
    defined_func.insert(fn->func_name);
  } // for smt_item
} // replace_function_arg_body

/// add the no-change-function (hierarchically)
/// should be after the replace_func_arg_body
void YosysSmtParser::add_no_change_function() {
  var_type bool_type;
  bool_type._type = var_type::tp::Bool;

  for (const auto& module_name : smt_ast.data_type_order) { // do this in order
    ILA_ASSERT(IN(module_name, smt_ast.datatypes));
    ILA_ASSERT(IN(module_name, flatten_datatype));
    const auto& st_vec = smt_ast.datatypes[module_name];
    const auto& flatten_st_vec = flatten_datatype[module_name];
    // add a nc function
    std::shared_ptr<func_def_t> fn = std::make_shared<func_def_t>();
    // func_name
    fn->func_name = "|" + module_name + "_k|"; // keep (NC)
    // func_module
    fn->func_module = module_name;
    // args
    convert_flatten_datatype_to_arg_vec(flatten_st_vec, fn->args, "");
    convert_flatten_datatype_to_arg_vec(flatten_st_vec, fn->args, "_next");
    // ret_type
    fn->ret_type = bool_type;
    // func_body
    fn->func_body = "(and ";
    std::vector<std::string> eqlist;
    for (auto&& st : st_vec) {
      if (st._type.is_datatype()) {
        // add a hierarchy func call
        std::string hier_func_call =
            "(" + ("|" + get_mod_name(st._type.module_name) + "_k|");
        auto module_name = get_mod_name(st._type.module_name);
        ILA_ASSERT(IN(module_name, flatten_datatype));
        const auto& st_vec_sub = flatten_datatype[module_name];
        for (const auto& sub_st : st_vec_sub)
          hier_func_call += " " + sub_st.internal_name;
        // let's do it twice
        for (const auto& sub_st : st_vec_sub)
          hier_func_call +=
              " " + st_name_add_suffix(sub_st.internal_name, "_next");
        hier_func_call += ")";
        eqlist.push_back(hier_func_call);
      }      // end if datatypes
      else { // add a =
        std::string eq = "(=";
        eq += " " + st.internal_name;
        eq += " " + st_name_add_suffix(st.internal_name, "_next");
        eq += ")";
        eqlist.push_back(eq);
      } // BV-Bool / datatype
    }   // for all state
    fn->func_body += Join(eqlist, " ") + ")";
  } // for all module, add keep function
} // add_no_change_function

/// create the variable indices
void YosysSmtParser::create_variable_idx() {
  ILA_ASSERT(IN(smt_ast.data_type_order.back(), flatten_datatype));
  for (auto&& v : flatten_datatype[smt_ast.data_type_order.back()]) {
    const auto& vname =
        v.verilog_name.empty() ? v.internal_name : v.verilog_name;
    ILA_ASSERT(!IN(vname, variable_idx));
    variable_idx.insert(std::make_pair(vname, &v));
    // we will try to avoid copying
  }
}

// -------------- CONSTRUCTOR -------------------- //
YosysSmtParser::YosysSmtParser(const std::string& buf) {
  // parse from string
  str_iterator iter(buf);
  ParseFromString(iter, smt_ast);
  construct_flatten_dataype();
  // from the flatten datatype we extract the variable indices
  create_variable_idx();
}

YosysSmtParser::~YosysSmtParser() {
  // do nothing
}

void YosysSmtParser::BreakDatatypes() { replace_all_function_arg_body(); }
/// Add the no change function
void YosysSmtParser::AddNoChangeStateUpdateFunction() {
  add_no_change_function();
}
/// Export to string
std::string YosysSmtParser::Export() { return smt_ast.toString(); }

const smt_file& YosysSmtParser::GetRawSmtAst() const { return smt_ast; }

/// return a reference to module def order
const std::vector<std::string>& YosysSmtParser::get_module_def_orders() const {
  return smt_ast.data_type_order;
}
/// return a module's flatten datatypes
const std::vector<state_var_t>&
YosysSmtParser::get_module_flatten_dt(const std::string& mod_name) const {
  ILA_ASSERT(!flatten_datatype.empty()) << "BUG: use before flatten datatypes";
  auto pos = flatten_datatype.find(mod_name);
  ILA_ASSERT(pos != flatten_datatype.end());
  return pos->second;
}

const YosysSmtParser::variable_idx_t& YosysSmtParser::get_var_idx() const {
  return variable_idx;
}

/// check if a name is a state
bool YosysSmtParser::is_state_name(const std::string& state_name) const {
  // std::cout << "Checking name " << state_name << " in : " << (IN(state_name,
  // variable_idx)) << std::endl;
  return IN(state_name, variable_idx);
}

}; // namespace smt
}; // namespace ilang