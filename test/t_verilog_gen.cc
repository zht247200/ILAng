/// \file
/// Unit test for Verilog parser.
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <ilang/ila-mngr/u_abs_knob.h>
#include <ilang/ilang++.h>
#include <ilang/util/fs.h>
#include <ilang/util/log.h>
#include <ilang/verilog-in/verilog_parse.h>
#include <ilang/verilog-out/verilog_gen.h>

#include "unit-include/config.h"
#include "unit-include/eq_ilas.h"
#include "unit-include/simple_cpu.h"
#include "unit-include/util.h"

namespace ilang {

void parseable(const std::string& fname, VerilogGenerator& vgen) {
  std::ofstream fout(fname);
  if (fout.is_open()) {
    vgen.DumpToFile(fout);
    fout.close();
  } else
    ILA_WARN << "Cannot write tmpfile:" << fname << " for vlog-gen test.";

  int result = TestParseVerilogFrom(fname);
  EXPECT_EQ(result, 0);
  if (result != 0)
    ILA_INFO << "ParseErrorFileName = " << fname;
}

void ParseIla(const InstrLvlAbsPtr& ila) {
  // test 1 gen all : internal mem
  {
    SetLogLevel(2);
    auto vgen = VerilogGenerator();
    vgen.ExportIla(ila);

    char tmp_file_template[] = "/tmp/vlog_XXXXXX";
    auto tmp_file_name = GetRandomFileName(tmp_file_template);
    parseable(tmp_file_name, vgen);
  }
  // test 2 gen all : external mem
  {
    auto config = VerilogGenerator::VlgGenConfig(
        true, VerilogGenerator::VlgGenConfig::funcOption::Internal);
    auto vgen = VerilogGenerator(config);
    vgen.ExportIla(ila);

    char tmp_file_template[] = "/tmp/vlog_ext_XXXXXX";
    auto tmp_file_name = GetRandomFileName(tmp_file_template);
    parseable(tmp_file_name, vgen);
  }
}

void FlattenIla(const InstrLvlAbsPtr& ila) {

  for (auto i = 0; i < ila->instr_num(); i++) {
    auto dep_ila = AbsKnob::ExtrDeptModl(ila->instr(i), "Flatten");
    AbsKnob::FlattenIla(dep_ila);

    auto vgen = VerilogGenerator();
    vgen.ExportIla(dep_ila);

    char tmp_file_template[] = "/tmp/vlog_flat_XXXXXX";
    auto tmp_file_name = GetRandomFileName(tmp_file_template);
    parseable(tmp_file_name, vgen);
  }
}

TEST(TestVerilogGen, Init) { VerilogGenerator(); }

TEST(TestVerilogGen, VlgCnst) {
  EXPECT_EQ(VerilogGeneratorBase::ToVlgNum(1, 8), "8'h1");
  EXPECT_EQ(VerilogGeneratorBase::ToVlgNum(255, 8), "8'hff");
  EXPECT_EQ(VerilogGeneratorBase::ToVlgNum(0, 8), "8'h0");

  EXPECT_EQ(VerilogGeneratorBase::ToVlgNum(0, 128), "128'h0");
  EXPECT_EQ(VerilogGeneratorBase::ToVlgNum(1, 256), "256'h1");
  {
    std::string hex_not_last_byte;
    for (int i = 0; i < sizeof(VerilogGeneratorBase::IlaBvValType) * 2 - 2; i++)
      hex_not_last_byte += 'f';
    EXPECT_EQ(VerilogGeneratorBase::ToVlgNum(-1, 128),
              "128'h" + hex_not_last_byte + "ff");
    EXPECT_EQ(VerilogGeneratorBase::ToVlgNum(-2, 128),
              "128'h" + hex_not_last_byte + "fe");
    EXPECT_EQ(VerilogGeneratorBase::ToVlgNum(-10, 128),
              "128'h" + hex_not_last_byte + "f6");
  }

  {
    std::string hex_not_last_byte;
    for (int i = 0; i < sizeof(VerilogGeneratorBase::IlaBvValType) * 2 - 2; i++)
      hex_not_last_byte += 'f';
    EXPECT_EQ(VerilogGeneratorBase::ToVlgNum(-1, 64),
              "64'h" + hex_not_last_byte + "ff");
    EXPECT_EQ(VerilogGeneratorBase::ToVlgNum(-2, 64),
              "64'h" + hex_not_last_byte + "fe");
    EXPECT_EQ(VerilogGeneratorBase::ToVlgNum(-10, 64),
              "64'h" + hex_not_last_byte + "f6");
  }

#ifndef NDEBUG
  EXPECT_DEATH(VerilogGeneratorBase::ToVlgNum(-256, 8), ".*");
  EXPECT_DEATH(VerilogGeneratorBase::ToVlgNum(-1, 8), ".*");
  EXPECT_DEATH(VerilogGeneratorBase::ToVlgNum(256, 8), ".*");
  EXPECT_DEATH(VerilogGeneratorBase::ToVlgNum(-257, 8), ".*");
#endif
}

TEST(TestVerilogGen, ParseInst) {
  auto ila_ptr_ = SimpleCpu("proc");
  // test 1 gen Add : internal mem
  {
    auto vgen = VerilogGenerator();

    // DebugLog::Enable("VerilogGen.ParseNonMemUpdateExpr");
    vgen.ExportTopLevelInstr(ila_ptr_->instr("Add"));

    parseable(std::string(ILANG_TEST_BIN_ROOT) + "/t_proc_Add.v", vgen);
  }
  // test 2 gen Add : external mem
  {
    auto config = VerilogGenerator::VlgGenConfig(
        true, VerilogGenerator::VlgGenConfig::funcOption::Internal);
    auto vgen = VerilogGenerator(config);

    // DebugLog::Enable("VerilogGen.ParseNonMemUpdateExpr");
    vgen.ExportTopLevelInstr(ila_ptr_->instr("Add"));

    parseable(std::string(ILANG_TEST_BIN_ROOT) + "/t_proc_Add_extmem.v", vgen);
  }
  // test 3 gen Load : internal mem
  {
    auto vgen = VerilogGenerator();
    // DebugLog::Enable("VerilogGen.ParseNonMemUpdateExpr");
    vgen.ExportTopLevelInstr(ila_ptr_->instr("Load"));
    parseable(std::string(ILANG_TEST_BIN_ROOT) + "/t_proc_Load.v", vgen);
  }
  // test 4 gen Store : internal mem
  {
    auto vgen = VerilogGenerator();
    // DebugLog::Enable("VerilogGen.ParseNonMemUpdateExpr");
    vgen.ExportTopLevelInstr(ila_ptr_->instr("Store"));
    parseable(std::string(ILANG_TEST_BIN_ROOT) + "/t_proc_Store.v", vgen);
  }
  // test 5 gen Load : external mem
  {
    auto config = VerilogGenerator::VlgGenConfig(
        true, VerilogGenerator::VlgGenConfig::funcOption::Internal);
    auto vgen = VerilogGenerator(config);
    // DebugLog::Enable("VerilogGen.ParseNonMemUpdateExpr");
    vgen.ExportTopLevelInstr(ila_ptr_->instr("Load"));
    parseable(std::string(ILANG_TEST_BIN_ROOT) + "/t_proc_Load_extmem.v", vgen);
  }
  // test 6 gen Store : external mem
  {
    auto config = VerilogGenerator::VlgGenConfig(
        true, VerilogGenerator::VlgGenConfig::funcOption::Internal);
    auto vgen = VerilogGenerator(config);
    // DebugLog::Enable("VerilogGen.ParseNonMemUpdateExpr");
    vgen.ExportTopLevelInstr(ila_ptr_->instr("Store"));
    parseable(std::string(ILANG_TEST_BIN_ROOT) + "/t_proc_Store_extmem.v",
              vgen);
  }
} // TEST (ParseInst)

TEST(TestVerilogGen, CpReg) {
  EqIlaGen ila_gen;
  auto ila = ila_gen.GetIlaHier1("CpReg");
  ParseIla(ila);
  FlattenIla(ila);
}

TEST(TestVerilogGen, SimpleProc) {
  auto ila = SimpleCpu("proc");
  ParseIla(ila);
  FlattenIla(ila);
}

TEST(TestVerilogGen, AES_V) {
  auto dir = os_portable_append_dir(ILANG_TEST_DATA_DIR, "aes");
  auto file = os_portable_append_dir(dir, "aes_v.json");
  auto ila = ImportIlaPortable(file);
  ParseIla(ila.get());
  FlattenIla(ila.get());
}

TEST(TestVerilogGen, AES_C) {
  auto dir = os_portable_append_dir(ILANG_TEST_DATA_DIR, "aes");
  auto file = os_portable_append_dir(dir, "aes_c.json");
  auto ila = ImportIlaPortable(file);
  ParseIla(ila.get());
  FlattenIla(ila.get());
}

TEST(TestVerilogGen, GB_Low) {
  auto dir = os_portable_append_dir(ILANG_TEST_DATA_DIR, "gb");
  auto file = os_portable_append_dir(dir, "gb_low.json");
  auto ila = ImportIlaPortable(file);
  ParseIla(ila.get());
  FlattenIla(ila.get());
}

TEST(TestVerilogGen, RBM) {
  auto dir = os_portable_append_dir(ILANG_TEST_DATA_DIR, "rbm");
  auto file = os_portable_append_dir(dir, "rbm.json");
  auto ila = ImportIlaPortable(file);
  ParseIla(ila.get());
  FlattenIla(ila.get());
}

TEST(TestVerilogGen, OC) {
  auto dir = os_portable_append_dir(ILANG_TEST_DATA_DIR, "oc");
  auto file = os_portable_append_dir(dir, "oc.json");
  auto ila = ImportIlaPortable(file);
  ParseIla(ila.get());
  FlattenIla(ila.get());
}

class T1 {
  friend class TestVerilogExport;

protected:
  int a;
};

class TestVerilogExport : public ::testing::Test {
public:
  TestVerilogExport() {
    ila = InstrLvlAbs::New("host");
    x = ila->NewBoolState("x");
    y = ila->NewBoolState("y");
    z = ila->NewBoolState("z");
    bi = ila->NewBoolInput("bi");
    bv_x = ila->NewBvState("bv_x", 8);
    bv_y = ila->NewBvState("bv_y", 8);
    bv_z = ila->NewBvState("bv_z", 8);
    bv_u = ila->NewMemState("bv_u", 8, 8);

    ila->NewInstr("NoDecode");

    T1 a;
    a.a = 1;
  }

  ~TestVerilogExport() {}

  void SetUp() {}

  void TearDown() {}

  InstrLvlAbsPtr ila = NULL;
  ExprPtr x = NULL;
  ExprPtr y = NULL;
  ExprPtr z = NULL;
  ExprPtr bi = NULL;
  ExprPtr bv_x = NULL;
  ExprPtr bv_y = NULL;
  ExprPtr bv_z = NULL;
  ExprPtr bv_u = NULL;

  void check_reserved_name() {
    auto vgen = VerilogGenerator();

    EXPECT_FALSE(vgen.check_reserved_name("clk"));

    vgen.ExportTopLevelInstr(ila->instr("NoDecode"));
    EXPECT_FALSE(vgen.check_reserved_name("__ILA_host_decode_of_NoDecode__"));

    EXPECT_TRUE(vgen.check_reserved_name("nouse"));
  }

  void sanitizeName() {
    auto vgen = VerilogGenerator();
    EXPECT_EQ(vgen.sanitizeName("0"), "__ZERO__");
    EXPECT_EQ(vgen.sanitizeName("s`"), "s_s_n0_s_");
    EXPECT_EQ(vgen.sanitizeName("s`"), "s_s_n0_s_");
  }

  void get_width() {
    auto vgen = VerilogGenerator();
    EXPECT_EQ(vgen.get_width(bv_u), 8);
  }

  void new_id() {
    auto config = VerilogGenerator::VlgGenConfig(
        true, VerilogGenerator::VlgGenConfig::funcOption::Internal);
    config.pass_node_name = true;

    auto vgen = VerilogGenerator(config);
    EXPECT_TRUE(vgen.new_id(NULL) != "");
    EXPECT_TRUE(vgen.new_id(x).find("x") != std::string::npos);

    auto vgen2 = VerilogGenerator();
    vgen2.reference_name_set.insert({"x", "xxx"});
    EXPECT_TRUE(vgen2.new_id(x).find("xxx") != std::string::npos);
  }

  void dup() {
    auto vgen = VerilogGenerator();
    vgen.add_input("x", 1);
    vgen.add_input("x", 1);
    EXPECT_DEATH(vgen.add_input("x", 2), ".*");

    vgen.add_output("y", 1);
    vgen.add_output("y", 1);
    EXPECT_DEATH(vgen.add_output("y", 2), ".*");

    vgen.add_wire("z", 1);
    vgen.add_wire("z", 1);
    EXPECT_DEATH(vgen.add_wire("z", 2), ".*");
  }

  void death() {
    InstrLvlAbsPtr i2 = InstrLvlAbs::New("i2");
    auto mi = i2->NewMemInput("mi", 8, 8);

    auto vgen = VerilogGenerator();
    EXPECT_DEATH(vgen.insertInput(mi), ".*");
  }

  void internal_func() {
    auto config = VerilogGenerator::VlgGenConfig(
        true, VerilogGenerator::VlgGenConfig::funcOption::Internal);

    auto vgen = VerilogGenerator(config);

    SortPtr rs = std::make_shared<SortBv>(8);
    FuncPtr f1 = Func::New("f1", rs, {rs, rs});

    auto f1a = ExprFuse::AppFunc(f1, bv_x, bv_y);

    auto a = ila->NewInstr("a");
    { a->set_update(bv_x, f1a); }

    vgen.ExportTopLevelInstr(a);
  }

}; // TestVerilogExport

TEST_F(TestVerilogExport, check_reserved_name) { check_reserved_name(); }

TEST_F(TestVerilogExport, sanitizeName) { sanitizeName(); }

TEST_F(TestVerilogExport, get_width) { get_width(); }

// pass node name, refset
TEST_F(TestVerilogExport, new_id) { new_id(); }

using TestVerilogExportDeathTest = TestVerilogExport;

TEST_F(TestVerilogExportDeathTest, dup) { dup(); }

TEST_F(TestVerilogExportDeathTest, death) { death(); }

// ?? func -- death
TEST_F(TestVerilogExport, internalfunc) { internal_func(); }

// external func

// null decode

// bool: xor, imply, ULT, UGT, ITE,
// bv : NEGATE, COMPLEMENT
// SIGN_EXTEND, OR, XOR (ZEXT 32-32), SHL, ASHR,
// LSHR, CONCAT,
// LOAD(ITE bug)
//
TEST_F(TestVerilogExport, OPs) {
  auto i1 = ila->NewInstr();
  {
    i1->set_update(x,

                   ExprFuse::Ite(x, ExprFuse::Ult(x, y), ExprFuse::Ugt(y, z)));
    i1->set_update(y,

                   ExprFuse::Imply(ExprFuse::Xor(x, y), z));
    i1->set_update(bv_z, ExprFuse::Mul(bv_x, bv_y));

    auto vgen = VerilogGenerator();
    vgen.ExportTopLevelInstr(i1);
  }

  auto i2 = ila->NewInstr();
  {
    i2->set_update(bv_x, ExprFuse::Negate(bv_x));
    auto vgen = VerilogGenerator();
    vgen.ExportTopLevelInstr(i2);
  }

  auto i3 = ila->NewInstr();
  {
    i3->set_update(bv_x, ExprFuse::SExt(bv_x, 8));
    auto vgen = VerilogGenerator();
    vgen.ExportTopLevelInstr(i3);
  }

  auto i32 = ila->NewInstr();
  {
    i32->set_update(bv_x, ExprFuse::ZExt(bv_x, 8));
    auto vgen = VerilogGenerator();
    vgen.ExportTopLevelInstr(i32);
  }
  auto i33 = ila->NewInstr();
  {
    i33->set_update(bv_x, ExprFuse::Extract(ExprFuse::ZExt(bv_x, 9), 8, 1));
    auto vgen = VerilogGenerator();
    vgen.ExportTopLevelInstr(i33);
  }
  auto i34 = ila->NewInstr();
  {
    i34->set_update(bv_x, ExprFuse::Extract(ExprFuse::SExt(bv_x, 9), 8, 1));
    auto vgen = VerilogGenerator();
    vgen.ExportTopLevelInstr(i34);
  }

  auto i4 = ila->NewInstr();
  {
    i4->set_update(bv_x, ExprFuse::Complement(bv_x));
    auto vgen = VerilogGenerator();
    vgen.ExportTopLevelInstr(i4);
  }

  auto i = ila->NewInstr();
  {
    i->set_update(bv_x, ExprFuse::Or(bv_x, bv_y));
    auto vgen = VerilogGenerator();
    vgen.ExportTopLevelInstr(i);
  }
  i = ila->NewInstr();
  {
    i->set_update(bv_x, ExprFuse::Xor(bv_x, bv_y));
    auto vgen = VerilogGenerator();
    vgen.ExportTopLevelInstr(i);
  }

  i = ila->NewInstr();
  {
    i->set_update(bv_x, ExprFuse::Shl(bv_x, 1));
    auto vgen = VerilogGenerator();
    vgen.ExportTopLevelInstr(i);
  }

  i = ila->NewInstr();
  {
    i->set_update(bv_x, ExprFuse::Ashr(bv_x, 1));
    auto vgen = VerilogGenerator();
    vgen.ExportTopLevelInstr(i);
  }

  i = ila->NewInstr();
  {
    i->set_update(bv_x, ExprFuse::Lshr(bv_x, 1));
    auto vgen = VerilogGenerator();
    vgen.ExportTopLevelInstr(i);
  }

  i = ila->NewInstr();
  {
    i->set_update(bv_x, ExprFuse::Extract(ExprFuse::Concat(bv_x, bv_y), 9, 2));
    auto vgen = VerilogGenerator();
    vgen.ExportTopLevelInstr(i);
  }

  i = ila->NewInstr();
  {
    i->set_update(bv_u, ExprFuse::Ite(x, ExprFuse::Store(bv_u, bv_x, bv_y),
                                      ExprFuse::Store(bv_u, bv_z, bv_x)));
    auto vgen = VerilogGenerator();
    vgen.ExportTopLevelInstr(i);
  }
}

}; // namespace ilang
