#include "systemc.h"
#include <map>
SC_MODULE(TEST) {
  sc_in< sc_biguint<2> > TEST_cmd_in;
  sc_biguint<2> TEST_cmd;
  sc_in< sc_biguint<16> > TEST_cmdaddr_in;
  sc_biguint<16> TEST_cmdaddr;
  sc_in< sc_biguint<8> > TEST_cmddata_in;
  sc_biguint<8> TEST_cmddata;
  sc_in<bool> TEST_cmdflag_in;
  bool TEST_cmdflag;
  sc_out< sc_biguint<2> > TEST_status_out;
  sc_biguint<2> TEST_status;
  sc_out< sc_biguint<16> > TEST_address_out;
  sc_biguint<16> TEST_address;
  sc_out< sc_biguint<16> > TEST_length_out;
  sc_biguint<16> TEST_length;
  sc_out< sc_biguint<128> > TEST_counter_out;
  sc_biguint<128> TEST_counter;
  sc_biguint<8> TEST_XRAM[65536];
  sc_out<bool> TEST_flag_out;
  bool TEST_flag;
  std::map< sc_biguint<32>, sc_biguint<32> > TEST_big_ram;
  sc_biguint<128> ENCRYPT_rd_data;
  sc_biguint<128> ENCRYPT_enc_data;
  sc_biguint<4> ENCRYPT_byte_cnt;
  sc_biguint<16> ENCRYPT_blk_cnt;
  void init_ENCRYPT();
  bool c_95388;
  bool c_95390;
  bool decode_TEST_WRITE_ADDRESS();
  bool c_95309;
  bool c_95305;
  bool c_95311;
  bool c_95334;
  bool c_95327;
  bool c_95329;
  bool c_95331;
  bool c_95336;
  bool c_95323;
  bool c_95337;
  bool decode_TEST_START_ENCRYPT();
  bool c_95371;
  bool c_95367;
  bool c_95373;
  bool c_95363;
  bool c_95374;
  bool decode_ENCRYPT_LOAD();
  bool c_95410;
  bool decode_ENCRYPT_ENC();
  bool c_95685;
  bool c_95681;
  bool c_95687;
  bool decode_ENCRYPT_STORE();
  bool c_95709;
  sc_biguint<16> decode_TEST_WRITE_ADDRESS_update_TEST_address();
  bool c_95314;
  bool c_95349;
  sc_biguint<8> c_95345;
  sc_biguint<8> c_95351;
  bool c_95342;
  sc_biguint<8> c_95338;
  sc_biguint<8> c_95344;
  sc_biguint<16> c_95356;
  sc_biguint<16> c_95358;
  bool decode_TEST_WRITE_ADDRESS_update_TEST_flag();
  bool c_95359;
  sc_biguint<2> decode_TEST_START_ENCRYPT_update_TEST_status();
  sc_biguint<2> unknown0();
  sc_biguint<2> c_95377;
  sc_biguint<2> c_95380;
  sc_biguint<4> decode_ENCRYPT_LOAD_update_ENCRYPT_byte_cnt();
  sc_biguint<4> c_95414;
  sc_biguint<128> decode_ENCRYPT_LOAD_update_ENCRYPT_rd_data();
  sc_biguint<4> c_95659;
  bool c_95662;
  sc_biguint<16> c_95417;
  sc_biguint<16> c_95415;
  sc_biguint<16> c_95418;
  sc_biguint<8> c_95419;
  sc_biguint<8> c_95655;
  sc_biguint<8> c_95664;
  sc_biguint<4> c_95643;
  bool c_95646;
  sc_biguint<8> c_95639;
  sc_biguint<8> c_95648;
  sc_biguint<4> c_95627;
  bool c_95630;
  sc_biguint<8> c_95623;
  sc_biguint<8> c_95632;
  sc_biguint<4> c_95611;
  bool c_95614;
  sc_biguint<8> c_95607;
  sc_biguint<8> c_95616;
  sc_biguint<4> c_95595;
  bool c_95598;
  sc_biguint<8> c_95591;
  sc_biguint<8> c_95600;
  sc_biguint<4> c_95579;
  bool c_95582;
  sc_biguint<8> c_95575;
  sc_biguint<8> c_95584;
  sc_biguint<4> c_95563;
  bool c_95566;
  sc_biguint<8> c_95559;
  sc_biguint<8> c_95568;
  sc_biguint<4> c_95547;
  bool c_95550;
  sc_biguint<8> c_95543;
  sc_biguint<8> c_95552;
  sc_biguint<4> c_95531;
  bool c_95534;
  sc_biguint<8> c_95527;
  sc_biguint<8> c_95536;
  sc_biguint<4> c_95515;
  bool c_95518;
  sc_biguint<8> c_95511;
  sc_biguint<8> c_95520;
  sc_biguint<4> c_95499;
  bool c_95502;
  sc_biguint<8> c_95495;
  sc_biguint<8> c_95504;
  sc_biguint<4> c_95483;
  bool c_95486;
  sc_biguint<8> c_95479;
  sc_biguint<8> c_95488;
  sc_biguint<4> c_95467;
  bool c_95470;
  sc_biguint<8> c_95463;
  sc_biguint<8> c_95472;
  sc_biguint<4> c_95451;
  bool c_95454;
  sc_biguint<8> c_95447;
  sc_biguint<8> c_95456;
  sc_biguint<4> c_95435;
  bool c_95438;
  sc_biguint<8> c_95431;
  sc_biguint<8> c_95440;
  sc_biguint<4> c_95425;
  bool c_95428;
  sc_biguint<8> c_95421;
  sc_biguint<8> c_95430;
  sc_biguint<16> c_95445;
  sc_biguint<24> c_95461;
  sc_biguint<32> c_95477;
  sc_biguint<40> c_95493;
  sc_biguint<48> c_95509;
  sc_biguint<56> c_95525;
  sc_biguint<64> c_95541;
  sc_biguint<72> c_95557;
  sc_biguint<80> c_95573;
  sc_biguint<88> c_95589;
  sc_biguint<96> c_95605;
  sc_biguint<104> c_95621;
  sc_biguint<112> c_95637;
  sc_biguint<120> c_95653;
  sc_biguint<128> c_95669;
  sc_biguint<2> decode_ENCRYPT_LOAD_update_TEST_status();
  bool c_95675;
  sc_biguint<2> c_95677;
  sc_biguint<128> decode_ENCRYPT_ENC_update_ENCRYPT_enc_data();
  const sc_biguint<128> c_95689[16] = {0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  sc_biguint<128> c_95697;
  sc_biguint<128> c_95699;
  sc_biguint<128> c_95693;
  sc_biguint<128> c_95700;
  sc_biguint<128> c_95691;
  sc_biguint<128> c_95701;
  sc_biguint<128> process128(sc_biguint<128> arg_0, sc_biguint<128> arg_1);
  sc_biguint<128> c_95702;
  sc_biguint<128> c_95703;
  sc_biguint<2> decode_ENCRYPT_ENC_update_TEST_status();
  void ite_95871(std::map<int, int>& mem_update_map);
  sc_biguint<16> c_95713;
  sc_biguint<16> c_95711;
  sc_biguint<16> c_95714;
  sc_biguint<4> c_95864;
  bool c_95867;
  sc_biguint<8> c_95860;
  sc_biguint<4> c_95854;
  bool c_95857;
  sc_biguint<8> c_95850;
  sc_biguint<4> c_95844;
  bool c_95847;
  sc_biguint<8> c_95840;
  sc_biguint<4> c_95834;
  bool c_95837;
  sc_biguint<8> c_95830;
  sc_biguint<4> c_95824;
  bool c_95827;
  sc_biguint<8> c_95820;
  sc_biguint<4> c_95814;
  bool c_95817;
  sc_biguint<8> c_95810;
  sc_biguint<4> c_95804;
  bool c_95807;
  sc_biguint<8> c_95800;
  sc_biguint<4> c_95794;
  bool c_95797;
  sc_biguint<8> c_95790;
  sc_biguint<4> c_95784;
  bool c_95787;
  sc_biguint<8> c_95780;
  sc_biguint<4> c_95774;
  bool c_95777;
  sc_biguint<8> c_95770;
  sc_biguint<4> c_95764;
  bool c_95767;
  sc_biguint<8> c_95760;
  sc_biguint<4> c_95754;
  bool c_95757;
  sc_biguint<8> c_95750;
  sc_biguint<4> c_95744;
  bool c_95747;
  sc_biguint<8> c_95740;
  sc_biguint<4> c_95734;
  bool c_95737;
  sc_biguint<8> c_95730;
  sc_biguint<4> c_95724;
  bool c_95727;
  sc_biguint<8> c_95720;
  sc_biguint<8> c_95718;
  sc_biguint<8> c_95729;
  sc_biguint<8> c_95739;
  sc_biguint<8> c_95749;
  sc_biguint<8> c_95759;
  sc_biguint<8> c_95769;
  sc_biguint<8> c_95779;
  sc_biguint<8> c_95789;
  sc_biguint<8> c_95799;
  sc_biguint<8> c_95809;
  sc_biguint<8> c_95819;
  sc_biguint<8> c_95829;
  sc_biguint<8> c_95839;
  sc_biguint<8> c_95849;
  sc_biguint<8> c_95859;
  sc_biguint<8> c_95869;
  std::map<int, int> decode_ENCRYPT_STORE_update_TEST_XRAM_map;
  void decode_ENCRYPT_STORE_update_TEST_XRAM(std::map<int, int>& mem_update_map);
  sc_biguint<16> decode_ENCRYPT_STORE_update_ENCRYPT_blk_cnt();
  bool c_95883;
  sc_biguint<16> c_95877;
  bool c_95878;
  sc_biguint<16> c_95874;
  sc_biguint<16> c_95880;
  sc_biguint<16> c_95885;
  sc_biguint<4> decode_ENCRYPT_STORE_update_ENCRYPT_byte_cnt();
  sc_biguint<4> c_95717;
  sc_biguint<2> decode_ENCRYPT_STORE_update_TEST_status();
  bool c_95898;
  sc_biguint<16> c_95892;
  bool c_95893;
  sc_biguint<2> c_95895;
  sc_biguint<2> c_95900;
  void compute();
  SC_HAS_PROCESS(TEST);
  TEST(sc_module_name name_) : sc_module(name_) {
    SC_METHOD(compute);
    sensitive << TEST_cmd_in << TEST_cmdaddr_in << TEST_cmddata_in << TEST_cmdflag_in;
  }
};
