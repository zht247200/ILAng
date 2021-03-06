#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;
typedef number<cpp_int_backend<2, 2, unsigned_magnitude, unchecked, void> > uint2_t;
typedef number<cpp_int_backend<4, 4, unsigned_magnitude, unchecked, void> > uint4_t;
typedef number<cpp_int_backend<24, 24, unsigned_magnitude, unchecked, void> > uint24_t;
typedef number<cpp_int_backend<40, 40, unsigned_magnitude, unchecked, void> > uint40_t;
typedef number<cpp_int_backend<48, 48, unsigned_magnitude, unchecked, void> > uint48_t;
typedef number<cpp_int_backend<56, 56, unsigned_magnitude, unchecked, void> > uint56_t;
typedef number<cpp_int_backend<72, 72, unsigned_magnitude, unchecked, void> > uint72_t;
typedef number<cpp_int_backend<80, 80, unsigned_magnitude, unchecked, void> > uint80_t;
typedef number<cpp_int_backend<88, 88, unsigned_magnitude, unchecked, void> > uint88_t;
typedef number<cpp_int_backend<96, 96, unsigned_magnitude, unchecked, void> > uint96_t;
typedef number<cpp_int_backend<104, 104, unsigned_magnitude, unchecked, void> > uint104_t;
typedef number<cpp_int_backend<112, 112, unsigned_magnitude, unchecked, void> > uint112_t;
typedef number<cpp_int_backend<120, 120, unsigned_magnitude, unchecked, void> > uint120_t;
#include <map>
class TEST {
public:
  uint2_t TEST_cmd;
  uint16_t TEST_cmdaddr;
  uint8_t TEST_cmddata;
  bool TEST_cmdflag;
  uint2_t TEST_status;
  uint16_t TEST_address;
  uint16_t TEST_length;
  uint128_t TEST_counter;
  uint8_t TEST_XRAM[65536];
  bool TEST_flag;
  std::map<uint32_t, uint32_t>TEST_big_ram;
  uint128_t ENCRYPT_rd_data;
  uint128_t ENCRYPT_enc_data;
  uint4_t ENCRYPT_byte_cnt;
  uint16_t ENCRYPT_blk_cnt;
  void init_ENCRYPT();
  bool c_120;
  bool c_122;
  bool decode_69();
  bool c_41;
  bool c_37;
  bool c_43;
  bool c_66;
  bool c_59;
  bool c_61;
  bool c_63;
  bool c_68;
  bool c_55;
  bool c_69;
  bool decode_106();
  bool c_103;
  bool c_99;
  bool c_105;
  bool c_95;
  bool c_106;
  bool decode_142();
  bool c_142;
  bool decode_419();
  bool c_417;
  bool c_413;
  bool c_419;
  bool decode_441();
  bool c_441;
  uint16_t decode_69_update_TEST_address();
  bool c_46;
  bool c_81;
  uint8_t c_77;
  uint8_t c_83;
  bool c_74;
  uint8_t c_70;
  uint8_t c_76;
  uint16_t c_88;
  uint16_t c_90;
  bool decode_69_update_TEST_flag();
  bool c_91;
  uint2_t decode_106_update_TEST_status();
  uint2_t unknown0();
  uint2_t c_109;
  uint2_t c_112;
  uint4_t decode_142_update_ENCRYPT_byte_cnt();
  uint4_t c_146;
  uint128_t decode_142_update_ENCRYPT_rd_data();
  uint4_t c_391;
  bool c_394;
  uint16_t c_149;
  uint16_t c_147;
  uint16_t c_150;
  uint8_t c_151;
  uint8_t c_387;
  uint8_t c_396;
  uint4_t c_375;
  bool c_378;
  uint8_t c_371;
  uint8_t c_380;
  uint4_t c_359;
  bool c_362;
  uint8_t c_355;
  uint8_t c_364;
  uint4_t c_343;
  bool c_346;
  uint8_t c_339;
  uint8_t c_348;
  uint4_t c_327;
  bool c_330;
  uint8_t c_323;
  uint8_t c_332;
  uint4_t c_311;
  bool c_314;
  uint8_t c_307;
  uint8_t c_316;
  uint4_t c_295;
  bool c_298;
  uint8_t c_291;
  uint8_t c_300;
  uint4_t c_279;
  bool c_282;
  uint8_t c_275;
  uint8_t c_284;
  uint4_t c_263;
  bool c_266;
  uint8_t c_259;
  uint8_t c_268;
  uint4_t c_247;
  bool c_250;
  uint8_t c_243;
  uint8_t c_252;
  uint4_t c_231;
  bool c_234;
  uint8_t c_227;
  uint8_t c_236;
  uint4_t c_215;
  bool c_218;
  uint8_t c_211;
  uint8_t c_220;
  uint4_t c_199;
  bool c_202;
  uint8_t c_195;
  uint8_t c_204;
  uint4_t c_183;
  bool c_186;
  uint8_t c_179;
  uint8_t c_188;
  uint4_t c_167;
  bool c_170;
  uint8_t c_163;
  uint8_t c_172;
  uint4_t c_157;
  bool c_160;
  uint8_t c_153;
  uint8_t c_162;
  uint16_t c_177;
  uint24_t c_193;
  uint32_t c_209;
  uint40_t c_225;
  uint48_t c_241;
  uint56_t c_257;
  uint64_t c_273;
  uint72_t c_289;
  uint80_t c_305;
  uint88_t c_321;
  uint96_t c_337;
  uint104_t c_353;
  uint112_t c_369;
  uint120_t c_385;
  uint128_t c_401;
  uint2_t decode_142_update_TEST_status();
  bool c_407;
  uint2_t c_409;
  uint128_t decode_419_update_ENCRYPT_enc_data();
  const uint128_t c_421[16] = {0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  uint128_t c_429;
  uint128_t c_431;
  uint128_t c_425;
  uint128_t c_432;
  uint128_t c_423;
  uint128_t c_433;
  uint128_t process128(uint128_t arg_0, uint128_t arg_1);
  uint128_t c_434;
  uint128_t c_435;
  uint2_t decode_419_update_TEST_status();
  void ite_603(std::map<int, int>& mem_update_map);
  uint16_t c_445;
  uint16_t c_443;
  uint16_t c_446;
  uint4_t c_596;
  bool c_599;
  uint8_t c_592;
  uint4_t c_586;
  bool c_589;
  uint8_t c_582;
  uint4_t c_576;
  bool c_579;
  uint8_t c_572;
  uint4_t c_566;
  bool c_569;
  uint8_t c_562;
  uint4_t c_556;
  bool c_559;
  uint8_t c_552;
  uint4_t c_546;
  bool c_549;
  uint8_t c_542;
  uint4_t c_536;
  bool c_539;
  uint8_t c_532;
  uint4_t c_526;
  bool c_529;
  uint8_t c_522;
  uint4_t c_516;
  bool c_519;
  uint8_t c_512;
  uint4_t c_506;
  bool c_509;
  uint8_t c_502;
  uint4_t c_496;
  bool c_499;
  uint8_t c_492;
  uint4_t c_486;
  bool c_489;
  uint8_t c_482;
  uint4_t c_476;
  bool c_479;
  uint8_t c_472;
  uint4_t c_466;
  bool c_469;
  uint8_t c_462;
  uint4_t c_456;
  bool c_459;
  uint8_t c_452;
  uint8_t c_450;
  uint8_t c_461;
  uint8_t c_471;
  uint8_t c_481;
  uint8_t c_491;
  uint8_t c_501;
  uint8_t c_511;
  uint8_t c_521;
  uint8_t c_531;
  uint8_t c_541;
  uint8_t c_551;
  uint8_t c_561;
  uint8_t c_571;
  uint8_t c_581;
  uint8_t c_591;
  uint8_t c_601;
  std::map<int, int> decode_441_update_TEST_XRAM_map;
  void decode_441_update_TEST_XRAM(std::map<int, int>& mem_update_map);
  uint16_t decode_441_update_ENCRYPT_blk_cnt();
  bool c_615;
  uint16_t c_609;
  bool c_610;
  uint16_t c_606;
  uint16_t c_612;
  uint16_t c_617;
  uint4_t decode_441_update_ENCRYPT_byte_cnt();
  uint4_t c_449;
  uint2_t decode_441_update_TEST_status();
  bool c_630;
  uint16_t c_624;
  bool c_625;
  uint2_t c_627;
  uint2_t c_632;
  void compute();
};
