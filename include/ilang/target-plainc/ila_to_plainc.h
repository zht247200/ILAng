/// \file
/// The header of the class Ila2PlainC.

#ifndef ILANG_TARGET_PLAINC_ILA_TO_PLAINC_H__
#define ILANG_TARGET_PLAINC_ILA_TO_PLAINC_H__

#include <ilang/ila/instr_lvl_abs.h>

#include <memory>
#include <string>

/// \namespace ilang
namespace ilang {

/// \brief The class of translating a ILA model to plain C.
class Ila2PlainC {
public:
  // base integer type
  typedef uint32_t BaseInt_t;

  // ------------------------- CONSTRUCTOR/DESTRUCTOR ----------------------- //
  /// Constructor.
  Ila2PlainC(const InstrLvlAbsPtr& m);
  /// Default destructor..
  ~Ila2PlainC();

  // ------------------------- METHODS -------------------------------------- //
  /// Convert the given ILA model to plain C (internal structure).
  bool Convert();

  /// Generate everything into one single file.
  bool ExportToSingleFile(const std::string& file_name);

  /// Generate multiple files in the directory.
  bool ExportToMultipleFiles(const std::string& dir_path);

private:
  // ------------------------- MEMBERS -------------------------------------- //
  /// The target ILA model.
  InstrLvlAbsPtr m_;

  /// Some map.
  std::unordered_map<size_t, size_t> map_;

  // ------------------------- METHODS -------------------------------------- //
  /// Convert an uninterpreted function.
  bool ConvertFunc();

}; // class Ila2PlainC

}; // namespace ilang

#endif // ILANG_TARGET_PLAINC_ILA_TO_PLAINC_H__
