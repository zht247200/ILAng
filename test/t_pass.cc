/// \file
/// Unit tests for ILA passes.

#include <ilang/ila-mngr/pass.h>
#include <ilang/ilang++.h>
#include <ilang/util/fs.h>

#include "unit-include/config.h"
#include "unit-include/util.h"

namespace ilang {

void ApplyPass(const std::string& dir, const std::string& file,
               bool simplify = true) {
  SetToStdErr(true);

  EnableDebug("PassSimpInstrUpdate");
  EnableDebug("PassRewrCondStore");
  EnableDebug("PassRewrStoreLoad");
  EnableDebug("PassInferChildProgCFG");
  EnableDebug("PassMapChildProgEntry");

  auto file_dir = os_portable_append_dir(ILANG_TEST_DATA_DIR, dir);
  auto ila_file = os_portable_append_dir(file_dir, file);
  auto ila = ImportIlaPortable(ila_file).get();

  PassSimplifyInstrUpdate(ila);

  PassRewriteConditionalStore(ila);
  PassRewriteStoreLoad(ila);

  PassInferChildProgCFG(ila);
  PassMapChildProgEntryPoint(ila);

  auto out_file = "opt_" + file;
  ExportIlaPortable(Ila(ila), out_file);
}

TEST(TestPass, AES) { ApplyPass("aes", "aes.json"); }

TEST(TestPass, AES_128) { ApplyPass("aes", "aes_128.json"); }

TEST(TestPass, AES_C) { ApplyPass("aes", "aes_c.json"); }

#if 0
TEST(TestPass, AES_V) { ApplyPass("aes", "aes_v.json"); }
#endif

TEST(TestPass, GB_LOW) { ApplyPass("gb", "gb_low.json"); }

TEST(TestPass, RBM) { ApplyPass("rbm", "rbm.json"); }

#if 0
TEST(TestPass, OC8051) { ApplyPass("oc", "oc.json"); }
#endif

}; // namespace ilang
