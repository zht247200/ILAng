/// \file
/// Unit tests for exporting ILA to plain C.

#include <ilang/ilang++.h>
#include <ilang/target-plainc/ila_to_plainc.h>
#include <ilang/util/fs.h>

#include "unit-include/config.h"
#include "unit-include/util.h"

namespace ilang {

// void Check(Ila& a, Ila& b) { CheckIlaEqLegacy(a.get(), b.get()); }

void GenPlainC(const std::string& dir, const std::string& file,
               bool check = true) {
  SetToStdErr(true);

  EnableDebug("PassSimpInstrUpdate");
  // EnableDebug("PassRewrCondStore");
  // EnableDebug("PassRewrStoreLoad");
  EnableDebug("PassInferChildProgCFG");
  EnableDebug("PassMapChildProgEntry");

  auto file_dir = os_portable_append_dir(ILANG_TEST_DATA_DIR, dir);
  auto ila_file = os_portable_append_dir(file_dir, file);
  auto ila = ImportIlaPortable(ila_file);

  auto gen = Ila2PlainC(ila.get());
  gen.Convert();

#if 0
  char tmp_file_template[] = "/tmp/ila_XXXXXX";
  auto tmp_file_name = GetRandomFileName(tmp_file_template);

  ExportIlaPortable(ila, tmp_file_name);
  auto des = ImportIlaPortable(tmp_file_name);

  if (check) {
    Check(ila, des);
  }
#endif
}

TEST(TestPlainC, AES) { GenPlainC("aes", "aes.json"); }

TEST(TestPlainC, AES_128) { GenPlainC("aes", "aes_128.json"); }

TEST(TestPlainC, AES_C) { GenPlainC("aes", "aes_c.json"); }

// TEST(TestPlainC, AES_V) { GenPlainC("aes", "aes_v.json"); }

TEST(TestPlainC, GB_LOW) { GenPlainC("gb", "gb_low.json"); }

TEST(TestPlainC, RBM) { GenPlainC("rbm", "rbm.json"); }

TEST(TestPlainC, OC8051) { GenPlainC("oc", "oc.json"); }

#if 0
TEST(TestPlainC, AES_V_TOP) { GenPlainC("aes", "aes_v_top.json"); }

TEST(TestPortable, AES_V_CHILD) { SerDes("aes", "aes_v_child.json"); }

TEST(TestPortable, AES_C_TOP) { SerDes("aes", "aes_c_top.json"); }

TEST(TestPortable, AES_C_CHILD) { SerDes("aes", "aes_c_child.json"); }
#endif

} // namespace ilang
