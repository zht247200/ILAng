/// \file
/// The source of the class Ila2PlainC.

#include <ilang/target-plainc/ila_to_plainc.h>

#include <ilang/target-plainc/plainc_ir.h>
#include <ilang/util/log.h>

namespace ilang {

Ila2PlainC::Ila2PlainC(const InstrLvlAbsPtr& m) : m_(m) {
  //
}

Ila2PlainC::~Ila2PlainC() {}

bool Ila2PlainC::Convert() {
  // Sanity check
  // Convert
  return true;
}

bool Ila2PlainC::ExportToSingleFile(const std::string& file_name) {
  //
  return true;
}

bool Ila2PlainC::ExportToMultipleFiles(const std::string& dir_path) {
  //
  return true;
}

}; // namespace ilang
