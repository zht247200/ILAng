module GB(
arg_0_TREADY,
arg_1_TDATA,
arg_1_TVALID,
RAM_w,
RAM_x,
RAM_y,
arg_0_TDATA,
arg_0_TVALID,
arg_1_TREADY,
proc_in,
stencil_0,
stencil_1,
stencil_2,
stencil_3,
stencil_4,
stencil_5,
stencil_6,
stencil_7,
stencil_8,
clk,rst,
step
);
input            arg_0_TREADY;
input      [7:0] arg_1_TDATA;
input            arg_1_TVALID;
input clk;
input rst;
input step;
output      [2:0] RAM_w;
output      [8:0] RAM_x;
output      [9:0] RAM_y;
output      [7:0] arg_0_TDATA;
output            arg_0_TVALID;
output            arg_1_TREADY;
output    [647:0] proc_in;
output     [71:0] stencil_0;
output     [71:0] stencil_1;
output     [71:0] stencil_2;
output     [71:0] stencil_3;
output     [71:0] stencil_4;
output     [71:0] stencil_5;
output     [71:0] stencil_6;
output     [71:0] stencil_7;
output     [71:0] stencil_8;
reg      [2:0] RAM_w;
reg      [8:0] RAM_x;
reg      [9:0] RAM_y;
reg      [7:0] arg_0_TDATA;
reg            arg_0_TVALID;
reg            arg_1_TREADY;
reg    [647:0] proc_in;
reg     [71:0] stencil_0;
reg     [71:0] stencil_1;
reg     [71:0] stencil_2;
reg     [71:0] stencil_3;
reg     [71:0] stencil_4;
reg     [71:0] stencil_5;
reg     [71:0] stencil_6;
reg     [71:0] stencil_7;
reg     [71:0] stencil_8;
wire            arg_0_TREADY;
wire      [7:0] arg_1_TDATA;
wire            arg_1_TVALID;
wire            n0;
wire            n1;
wire            n2;
wire            n3;
wire            n4;
wire            n5;
wire            n6;
wire            n7;
wire            n8;
wire            n9;
wire            n10;
wire            n11;
wire      [2:0] n12;
wire      [2:0] n13;
wire      [2:0] n14;
wire      [2:0] n15;
wire      [2:0] n16;
wire      [8:0] n17;
wire      [8:0] n18;
wire      [8:0] n19;
wire      [8:0] n20;
wire            n21;
wire      [9:0] n22;
wire      [9:0] n23;
wire      [9:0] n24;
wire      [9:0] n25;
wire      [9:0] n26;
wire            n27;
wire      [7:0] n28;
wire      [7:0] n29;
wire      [7:0] n30;
wire      [7:0] n31;
wire      [7:0] n32;
wire      [7:0] n33;
wire      [7:0] n34;
wire      [7:0] n35;
wire      [7:0] n36;
wire     [15:0] n37;
wire     [23:0] n38;
wire     [31:0] n39;
wire     [39:0] n40;
wire     [47:0] n41;
wire     [55:0] n42;
wire     [63:0] n43;
wire     [71:0] n44;
wire      [7:0] n45;
wire      [7:0] n46;
wire      [7:0] n47;
wire      [7:0] n48;
wire      [7:0] n49;
wire      [7:0] n50;
wire      [7:0] n51;
wire      [7:0] n52;
wire      [7:0] n53;
wire     [15:0] n54;
wire     [23:0] n55;
wire     [31:0] n56;
wire     [39:0] n57;
wire     [47:0] n58;
wire     [55:0] n59;
wire     [63:0] n60;
wire     [71:0] n61;
wire      [7:0] n62;
wire      [7:0] n63;
wire      [7:0] n64;
wire      [7:0] n65;
wire      [7:0] n66;
wire      [7:0] n67;
wire      [7:0] n68;
wire      [7:0] n69;
wire      [7:0] n70;
wire     [15:0] n71;
wire     [23:0] n72;
wire     [31:0] n73;
wire     [39:0] n74;
wire     [47:0] n75;
wire     [55:0] n76;
wire     [63:0] n77;
wire     [71:0] n78;
wire      [7:0] n79;
wire      [7:0] n80;
wire      [7:0] n81;
wire      [7:0] n82;
wire      [7:0] n83;
wire      [7:0] n84;
wire      [7:0] n85;
wire      [7:0] n86;
wire      [7:0] n87;
wire     [15:0] n88;
wire     [23:0] n89;
wire     [31:0] n90;
wire     [39:0] n91;
wire     [47:0] n92;
wire     [55:0] n93;
wire     [63:0] n94;
wire     [71:0] n95;
wire      [7:0] n96;
wire      [7:0] n97;
wire      [7:0] n98;
wire      [7:0] n99;
wire      [7:0] n100;
wire      [7:0] n101;
wire      [7:0] n102;
wire      [7:0] n103;
wire      [7:0] n104;
wire     [15:0] n105;
wire     [23:0] n106;
wire     [31:0] n107;
wire     [39:0] n108;
wire     [47:0] n109;
wire     [55:0] n110;
wire     [63:0] n111;
wire     [71:0] n112;
wire      [7:0] n113;
wire      [7:0] n114;
wire      [7:0] n115;
wire      [7:0] n116;
wire      [7:0] n117;
wire      [7:0] n118;
wire      [7:0] n119;
wire      [7:0] n120;
wire      [7:0] n121;
wire     [15:0] n122;
wire     [23:0] n123;
wire     [31:0] n124;
wire     [39:0] n125;
wire     [47:0] n126;
wire     [55:0] n127;
wire     [63:0] n128;
wire     [71:0] n129;
wire      [7:0] n130;
wire      [7:0] n131;
wire      [7:0] n132;
wire      [7:0] n133;
wire      [7:0] n134;
wire      [7:0] n135;
wire      [7:0] n136;
wire      [7:0] n137;
wire      [7:0] n138;
wire     [15:0] n139;
wire     [23:0] n140;
wire     [31:0] n141;
wire     [39:0] n142;
wire     [47:0] n143;
wire     [55:0] n144;
wire     [63:0] n145;
wire     [71:0] n146;
wire      [7:0] n147;
wire      [7:0] n148;
wire      [7:0] n149;
wire      [7:0] n150;
wire      [7:0] n151;
wire      [7:0] n152;
wire      [7:0] n153;
wire      [7:0] n154;
wire      [7:0] n155;
wire     [15:0] n156;
wire     [23:0] n157;
wire     [31:0] n158;
wire     [39:0] n159;
wire     [47:0] n160;
wire     [55:0] n161;
wire     [63:0] n162;
wire     [71:0] n163;
wire      [7:0] n164;
wire      [7:0] n165;
wire      [7:0] n166;
wire      [7:0] n167;
wire      [7:0] n168;
wire      [7:0] n169;
wire      [7:0] n170;
wire      [7:0] n171;
wire      [7:0] n172;
wire     [15:0] n173;
wire     [23:0] n174;
wire     [31:0] n175;
wire     [39:0] n176;
wire     [47:0] n177;
wire     [55:0] n178;
wire     [63:0] n179;
wire     [71:0] n180;
wire    [143:0] n181;
wire    [215:0] n182;
wire    [287:0] n183;
wire    [359:0] n184;
wire    [431:0] n185;
wire    [503:0] n186;
wire    [575:0] n187;
wire    [647:0] n188;
wire    [647:0] n189;
wire      [7:0] n190;
wire      [7:0] n191;
wire      [7:0] n192;
wire            n193;
wire            n194;
wire            n195;
wire            n196;
wire            n197;
wire            n198;
wire            n199;
wire            n200;
wire            n201;
wire    [647:0] n202;
wire            n203;
wire     [71:0] n204;
wire     [71:0] n205;
wire     [71:0] n206;
wire     [71:0] n207;
wire     [71:0] n208;
wire     [71:0] n209;
wire     [71:0] n210;
wire     [71:0] n211;
wire     [71:0] n212;
wire     [71:0] n213;
wire     [71:0] n214;
wire     [71:0] n215;
wire     [71:0] n216;
wire     [71:0] n217;
wire     [71:0] n218;
wire     [71:0] n219;
wire     [71:0] n220;
wire     [71:0] n221;
wire     [71:0] n222;
wire     [71:0] n223;
wire     [71:0] n224;
wire     [71:0] n225;
wire     [71:0] n226;
wire     [71:0] n227;
wire            n228;
wire      [8:0] n229;
wire      [7:0] n230;
wire            n231;
wire            n232;
wire            n233;
wire            n234;
wire            n235;
wire            n236;
wire      [7:0] n237;
wire      [7:0] n238;
wire      [7:0] n239;
wire      [7:0] n240;
wire      [7:0] n241;
wire      [7:0] n242;
wire      [7:0] n243;
wire      [7:0] n244;
wire      [7:0] n245;
wire      [7:0] n246;
wire      [7:0] n247;
wire      [7:0] n248;
wire      [7:0] n249;
wire      [7:0] n250;
wire      [7:0] n251;
wire      [7:0] n252;
wire      [7:0] n253;
wire      [7:0] n254;
wire      [7:0] n255;
wire      [7:0] n256;
wire      [7:0] n257;
wire      [7:0] n258;
wire      [7:0] n259;
wire      [7:0] n260;
wire      [7:0] n261;
wire      [7:0] n262;
wire      [7:0] n263;
wire      [7:0] n264;
wire      [7:0] n265;
wire      [7:0] n266;
wire      [7:0] n267;
wire      [7:0] n268;
wire      [7:0] n269;
wire      [7:0] n270;
wire      [7:0] n271;
wire      [7:0] n272;
wire      [7:0] n273;
wire      [7:0] n274;
wire      [7:0] n275;
wire      [7:0] n276;
wire      [7:0] n277;
wire      [7:0] n278;
wire      [7:0] n279;
wire      [7:0] n280;
wire      [7:0] n281;
wire      [7:0] n282;
wire      [7:0] n283;
wire      [7:0] n284;
wire      [7:0] n285;
wire      [7:0] n286;
wire      [7:0] n287;
wire      [7:0] n288;
wire      [7:0] n289;
wire      [7:0] n290;
wire      [7:0] n291;
wire      [7:0] n292;
wire      [7:0] n293;
wire      [7:0] n294;
wire      [7:0] n295;
wire      [7:0] n296;
wire      [7:0] n297;
wire      [7:0] n298;
wire      [7:0] n299;
wire     [15:0] n300;
wire     [23:0] n301;
wire     [31:0] n302;
wire     [39:0] n303;
wire     [47:0] n304;
wire     [55:0] n305;
wire     [63:0] n306;
wire     [71:0] n307;
wire     [71:0] n308;
wire     [71:0] n309;
wire     [71:0] n310;
wire      [8:0] RAM_0_addr0;
wire      [7:0] RAM_0_data0;
wire            n311;
wire            n312;
wire            n313;
wire            n314;
wire            n315;
wire            n316;
wire            n317;
wire      [8:0] RAM_1_addr0;
wire      [7:0] RAM_1_data0;
wire            n318;
wire            n319;
wire            n320;
wire      [8:0] RAM_2_addr0;
wire      [7:0] RAM_2_data0;
wire            n321;
wire            n322;
wire            n323;
wire      [8:0] RAM_3_addr0;
wire      [7:0] RAM_3_data0;
wire            n324;
wire            n325;
wire            n326;
wire      [8:0] RAM_4_addr0;
wire      [7:0] RAM_4_data0;
wire            n327;
wire            n328;
wire            n329;
wire      [8:0] RAM_5_addr0;
wire      [7:0] RAM_5_data0;
wire            n330;
wire            n331;
wire            n332;
wire      [8:0] RAM_6_addr0;
wire      [7:0] RAM_6_data0;
wire            n333;
wire            n334;
wire            n335;
wire      [8:0] RAM_7_addr0;
wire      [7:0] RAM_7_data0;
wire            n336;
wire            n337;
wire            n338;
reg      [7:0] RAM_0[487:0];
reg      [7:0] RAM_1[487:0];
reg      [7:0] RAM_2[487:0];
reg      [7:0] RAM_3[487:0];
reg      [7:0] RAM_4[487:0];
reg      [7:0] RAM_5[487:0];
reg      [7:0] RAM_6[487:0];
reg      [7:0] RAM_7[487:0];
wire clk;
wire rst;
wire step;
assign n0 =  ( arg_1_TREADY ) == ( 1'd0 )  ;
assign n1 =  ( arg_0_TVALID ) == ( 1'd0 )  ;
assign n2 =  ( n0 ) & ( n1 )  ;
assign n3 =  ( arg_0_TREADY ) == ( 1'd0 )  ;
assign n4 =  ( n2 ) & ( n3 )  ;
assign n5 =  ( arg_1_TVALID ) == ( 1'd1 )  ;
assign n6 =  ( arg_1_TREADY ) == ( 1'd1 )  ;
assign n7 =  ( n5 ) & ( n6 )  ;
assign n8 =  ( n7 ) & ( n1 )  ;
assign n9 =  ( n8 ) & ( n3 )  ;
assign n10 =  ( RAM_x ) == ( 9'd488 )  ;
assign n11 =  ( RAM_w ) == ( 3'd7 )  ;
assign n12 =  ( RAM_w ) + ( 3'd1 )  ;
assign n13 =  ( n11 ) ? ( 3'd0 ) : ( n12 ) ;
assign n14 =  ( n10 ) ? ( n13 ) : ( RAM_w ) ;
assign n15 =  ( n9 ) ? ( n14 ) : ( RAM_w ) ;
assign n16 =  ( n4 ) ? ( RAM_w ) : ( n15 ) ;
assign n17 =  ( RAM_x ) + ( 9'd1 )  ;
assign n18 =  ( n10 ) ? ( 9'd1 ) : ( n17 ) ;
assign n19 =  ( n9 ) ? ( n18 ) : ( RAM_x ) ;
assign n20 =  ( n4 ) ? ( RAM_x ) : ( n19 ) ;
assign n21 =  ( RAM_y ) == ( 10'd648 )  ;
assign n22 =  ( RAM_y ) + ( 10'd1 )  ;
assign n23 =  ( n21 ) ? ( 10'd0 ) : ( n22 ) ;
assign n24 =  ( n10 ) ? ( n23 ) : ( RAM_y ) ;
assign n25 =  ( n9 ) ? ( n24 ) : ( RAM_y ) ;
assign n26 =  ( n4 ) ? ( RAM_y ) : ( n25 ) ;
assign n27 =  ( RAM_x ) > ( 9'd9 )  ;
assign n28 = stencil_8[71:64] ;
assign n29 = stencil_7[71:64] ;
assign n30 = stencil_6[71:64] ;
assign n31 = stencil_5[71:64] ;
assign n32 = stencil_4[71:64] ;
assign n33 = stencil_3[71:64] ;
assign n34 = stencil_2[71:64] ;
assign n35 = stencil_1[71:64] ;
assign n36 = stencil_0[71:64] ;
assign n37 =  { ( n35 ) , ( n36 ) }  ;
assign n38 =  { ( n34 ) , ( n37 ) }  ;
assign n39 =  { ( n33 ) , ( n38 ) }  ;
assign n40 =  { ( n32 ) , ( n39 ) }  ;
assign n41 =  { ( n31 ) , ( n40 ) }  ;
assign n42 =  { ( n30 ) , ( n41 ) }  ;
assign n43 =  { ( n29 ) , ( n42 ) }  ;
assign n44 =  { ( n28 ) , ( n43 ) }  ;
assign n45 = stencil_8[63:56] ;
assign n46 = stencil_7[63:56] ;
assign n47 = stencil_6[63:56] ;
assign n48 = stencil_5[63:56] ;
assign n49 = stencil_4[63:56] ;
assign n50 = stencil_3[63:56] ;
assign n51 = stencil_2[63:56] ;
assign n52 = stencil_1[63:56] ;
assign n53 = stencil_0[63:56] ;
assign n54 =  { ( n52 ) , ( n53 ) }  ;
assign n55 =  { ( n51 ) , ( n54 ) }  ;
assign n56 =  { ( n50 ) , ( n55 ) }  ;
assign n57 =  { ( n49 ) , ( n56 ) }  ;
assign n58 =  { ( n48 ) , ( n57 ) }  ;
assign n59 =  { ( n47 ) , ( n58 ) }  ;
assign n60 =  { ( n46 ) , ( n59 ) }  ;
assign n61 =  { ( n45 ) , ( n60 ) }  ;
assign n62 = stencil_8[55:48] ;
assign n63 = stencil_7[55:48] ;
assign n64 = stencil_6[55:48] ;
assign n65 = stencil_5[55:48] ;
assign n66 = stencil_4[55:48] ;
assign n67 = stencil_3[55:48] ;
assign n68 = stencil_2[55:48] ;
assign n69 = stencil_1[55:48] ;
assign n70 = stencil_0[55:48] ;
assign n71 =  { ( n69 ) , ( n70 ) }  ;
assign n72 =  { ( n68 ) , ( n71 ) }  ;
assign n73 =  { ( n67 ) , ( n72 ) }  ;
assign n74 =  { ( n66 ) , ( n73 ) }  ;
assign n75 =  { ( n65 ) , ( n74 ) }  ;
assign n76 =  { ( n64 ) , ( n75 ) }  ;
assign n77 =  { ( n63 ) , ( n76 ) }  ;
assign n78 =  { ( n62 ) , ( n77 ) }  ;
assign n79 = stencil_8[47:40] ;
assign n80 = stencil_7[47:40] ;
assign n81 = stencil_6[47:40] ;
assign n82 = stencil_5[47:40] ;
assign n83 = stencil_4[47:40] ;
assign n84 = stencil_3[47:40] ;
assign n85 = stencil_2[47:40] ;
assign n86 = stencil_1[47:40] ;
assign n87 = stencil_0[47:40] ;
assign n88 =  { ( n86 ) , ( n87 ) }  ;
assign n89 =  { ( n85 ) , ( n88 ) }  ;
assign n90 =  { ( n84 ) , ( n89 ) }  ;
assign n91 =  { ( n83 ) , ( n90 ) }  ;
assign n92 =  { ( n82 ) , ( n91 ) }  ;
assign n93 =  { ( n81 ) , ( n92 ) }  ;
assign n94 =  { ( n80 ) , ( n93 ) }  ;
assign n95 =  { ( n79 ) , ( n94 ) }  ;
assign n96 = stencil_8[39:32] ;
assign n97 = stencil_7[39:32] ;
assign n98 = stencil_6[39:32] ;
assign n99 = stencil_5[39:32] ;
assign n100 = stencil_4[39:32] ;
assign n101 = stencil_3[39:32] ;
assign n102 = stencil_2[39:32] ;
assign n103 = stencil_1[39:32] ;
assign n104 = stencil_0[39:32] ;
assign n105 =  { ( n103 ) , ( n104 ) }  ;
assign n106 =  { ( n102 ) , ( n105 ) }  ;
assign n107 =  { ( n101 ) , ( n106 ) }  ;
assign n108 =  { ( n100 ) , ( n107 ) }  ;
assign n109 =  { ( n99 ) , ( n108 ) }  ;
assign n110 =  { ( n98 ) , ( n109 ) }  ;
assign n111 =  { ( n97 ) , ( n110 ) }  ;
assign n112 =  { ( n96 ) , ( n111 ) }  ;
assign n113 = stencil_8[31:24] ;
assign n114 = stencil_7[31:24] ;
assign n115 = stencil_6[31:24] ;
assign n116 = stencil_5[31:24] ;
assign n117 = stencil_4[31:24] ;
assign n118 = stencil_3[31:24] ;
assign n119 = stencil_2[31:24] ;
assign n120 = stencil_1[31:24] ;
assign n121 = stencil_0[31:24] ;
assign n122 =  { ( n120 ) , ( n121 ) }  ;
assign n123 =  { ( n119 ) , ( n122 ) }  ;
assign n124 =  { ( n118 ) , ( n123 ) }  ;
assign n125 =  { ( n117 ) , ( n124 ) }  ;
assign n126 =  { ( n116 ) , ( n125 ) }  ;
assign n127 =  { ( n115 ) , ( n126 ) }  ;
assign n128 =  { ( n114 ) , ( n127 ) }  ;
assign n129 =  { ( n113 ) , ( n128 ) }  ;
assign n130 = stencil_8[23:16] ;
assign n131 = stencil_7[23:16] ;
assign n132 = stencil_6[23:16] ;
assign n133 = stencil_5[23:16] ;
assign n134 = stencil_4[23:16] ;
assign n135 = stencil_3[23:16] ;
assign n136 = stencil_2[23:16] ;
assign n137 = stencil_1[23:16] ;
assign n138 = stencil_0[23:16] ;
assign n139 =  { ( n137 ) , ( n138 ) }  ;
assign n140 =  { ( n136 ) , ( n139 ) }  ;
assign n141 =  { ( n135 ) , ( n140 ) }  ;
assign n142 =  { ( n134 ) , ( n141 ) }  ;
assign n143 =  { ( n133 ) , ( n142 ) }  ;
assign n144 =  { ( n132 ) , ( n143 ) }  ;
assign n145 =  { ( n131 ) , ( n144 ) }  ;
assign n146 =  { ( n130 ) , ( n145 ) }  ;
assign n147 = stencil_8[15:8] ;
assign n148 = stencil_7[15:8] ;
assign n149 = stencil_6[15:8] ;
assign n150 = stencil_5[15:8] ;
assign n151 = stencil_4[15:8] ;
assign n152 = stencil_3[15:8] ;
assign n153 = stencil_2[15:8] ;
assign n154 = stencil_1[15:8] ;
assign n155 = stencil_0[15:8] ;
assign n156 =  { ( n154 ) , ( n155 ) }  ;
assign n157 =  { ( n153 ) , ( n156 ) }  ;
assign n158 =  { ( n152 ) , ( n157 ) }  ;
assign n159 =  { ( n151 ) , ( n158 ) }  ;
assign n160 =  { ( n150 ) , ( n159 ) }  ;
assign n161 =  { ( n149 ) , ( n160 ) }  ;
assign n162 =  { ( n148 ) , ( n161 ) }  ;
assign n163 =  { ( n147 ) , ( n162 ) }  ;
assign n164 = stencil_8[7:0] ;
assign n165 = stencil_7[7:0] ;
assign n166 = stencil_6[7:0] ;
assign n167 = stencil_5[7:0] ;
assign n168 = stencil_4[7:0] ;
assign n169 = stencil_3[7:0] ;
assign n170 = stencil_2[7:0] ;
assign n171 = stencil_1[7:0] ;
assign n172 = stencil_0[7:0] ;
assign n173 =  { ( n171 ) , ( n172 ) }  ;
assign n174 =  { ( n170 ) , ( n173 ) }  ;
assign n175 =  { ( n169 ) , ( n174 ) }  ;
assign n176 =  { ( n168 ) , ( n175 ) }  ;
assign n177 =  { ( n167 ) , ( n176 ) }  ;
assign n178 =  { ( n166 ) , ( n177 ) }  ;
assign n179 =  { ( n165 ) , ( n178 ) }  ;
assign n180 =  { ( n164 ) , ( n179 ) }  ;
assign n181 =  { ( n163 ) , ( n180 ) }  ;
assign n182 =  { ( n146 ) , ( n181 ) }  ;
assign n183 =  { ( n129 ) , ( n182 ) }  ;
assign n184 =  { ( n112 ) , ( n183 ) }  ;
assign n185 =  { ( n95 ) , ( n184 ) }  ;
assign n186 =  { ( n78 ) , ( n185 ) }  ;
assign n187 =  { ( n61 ) , ( n186 ) }  ;
assign n188 =  { ( n44 ) , ( n187 ) }  ;
assign n189 =  ( n27 ) ? ( n188 ) : ( proc_in ) ;
//assign n190 = gb_fun(n189) ;
gb_fun gb_fun_U ( 
        .a (n189),
        .b (n190)
        );

assign n191 =  ( n9 ) ? ( arg_0_TDATA ) : ( arg_0_TDATA ) ;
assign n192 =  ( n4 ) ? ( n190 ) : ( n191 ) ;
assign n193 =  ( RAM_x ) == ( 9'd1 )  ;
assign n194 =  ( n27 ) | ( n193 )  ;
assign n195 =  ( RAM_y ) >= ( 10'd8 )  ;
assign n196 =  ( n194 ) & ( n195 )  ;
assign n197 =  ( n196 ) ? ( 1'd1 ) : ( 1'd0 ) ;
assign n198 =  ( n9 ) ? ( 1'd0 ) : ( arg_0_TVALID ) ;
assign n199 =  ( n4 ) ? ( n197 ) : ( n198 ) ;
assign n200 =  ( n9 ) ? ( 1'd0 ) : ( arg_1_TREADY ) ;
assign n201 =  ( n4 ) ? ( 1'd1 ) : ( n200 ) ;
assign n202 =  ( n4 ) ? ( n189 ) : ( proc_in ) ;
assign n203 =  ( RAM_y ) < ( 10'd8 )  ;
assign n204 =  ( n203 ) ? ( stencil_0 ) : ( stencil_1 ) ;
assign n205 =  ( n9 ) ? ( stencil_0 ) : ( stencil_0 ) ;
assign n206 =  ( n4 ) ? ( n204 ) : ( n205 ) ;
assign n207 =  ( n203 ) ? ( stencil_1 ) : ( stencil_2 ) ;
assign n208 =  ( n9 ) ? ( stencil_1 ) : ( stencil_1 ) ;
assign n209 =  ( n4 ) ? ( n207 ) : ( n208 ) ;
assign n210 =  ( n203 ) ? ( stencil_2 ) : ( stencil_3 ) ;
assign n211 =  ( n9 ) ? ( stencil_2 ) : ( stencil_2 ) ;
assign n212 =  ( n4 ) ? ( n210 ) : ( n211 ) ;
assign n213 =  ( n203 ) ? ( stencil_3 ) : ( stencil_4 ) ;
assign n214 =  ( n9 ) ? ( stencil_3 ) : ( stencil_3 ) ;
assign n215 =  ( n4 ) ? ( n213 ) : ( n214 ) ;
assign n216 =  ( n203 ) ? ( stencil_4 ) : ( stencil_5 ) ;
assign n217 =  ( n9 ) ? ( stencil_4 ) : ( stencil_4 ) ;
assign n218 =  ( n4 ) ? ( n216 ) : ( n217 ) ;
assign n219 =  ( n203 ) ? ( stencil_5 ) : ( stencil_6 ) ;
assign n220 =  ( n9 ) ? ( stencil_5 ) : ( stencil_5 ) ;
assign n221 =  ( n4 ) ? ( n219 ) : ( n220 ) ;
assign n222 =  ( n203 ) ? ( stencil_6 ) : ( stencil_7 ) ;
assign n223 =  ( n9 ) ? ( stencil_6 ) : ( stencil_6 ) ;
assign n224 =  ( n4 ) ? ( n222 ) : ( n223 ) ;
assign n225 =  ( n203 ) ? ( stencil_7 ) : ( stencil_8 ) ;
assign n226 =  ( n9 ) ? ( stencil_7 ) : ( stencil_7 ) ;
assign n227 =  ( n4 ) ? ( n225 ) : ( n226 ) ;
assign n228 =  ( RAM_w ) == ( 3'd0 )  ;
assign n229 =  ( RAM_x ) - ( 9'd1 )  ;
assign n230 =  (  RAM_7 [ n229 ] )  ;
assign n231 =  ( RAM_w ) == ( 3'd1 )  ;
assign n232 =  ( RAM_w ) == ( 3'd2 )  ;
assign n233 =  ( RAM_w ) == ( 3'd3 )  ;
assign n234 =  ( RAM_w ) == ( 3'd4 )  ;
assign n235 =  ( RAM_w ) == ( 3'd5 )  ;
assign n236 =  ( RAM_w ) == ( 3'd6 )  ;
assign n237 =  (  RAM_6 [ n229 ] )  ;
assign n238 =  ( n236 ) ? ( n230 ) : ( n237 ) ;
assign n239 =  ( n235 ) ? ( n230 ) : ( n238 ) ;
assign n240 =  ( n234 ) ? ( n230 ) : ( n239 ) ;
assign n241 =  ( n233 ) ? ( n230 ) : ( n240 ) ;
assign n242 =  ( n232 ) ? ( n230 ) : ( n241 ) ;
assign n243 =  ( n231 ) ? ( n230 ) : ( n242 ) ;
assign n244 =  ( n228 ) ? ( n230 ) : ( n243 ) ;
assign n245 =  (  RAM_5 [ n229 ] )  ;
assign n246 =  ( n236 ) ? ( n237 ) : ( n245 ) ;
assign n247 =  ( n235 ) ? ( n237 ) : ( n246 ) ;
assign n248 =  ( n234 ) ? ( n237 ) : ( n247 ) ;
assign n249 =  ( n233 ) ? ( n237 ) : ( n248 ) ;
assign n250 =  ( n232 ) ? ( n237 ) : ( n249 ) ;
assign n251 =  ( n231 ) ? ( n237 ) : ( n250 ) ;
assign n252 =  ( n228 ) ? ( n237 ) : ( n251 ) ;
assign n253 =  (  RAM_4 [ n229 ] )  ;
assign n254 =  ( n236 ) ? ( n245 ) : ( n253 ) ;
assign n255 =  ( n235 ) ? ( n245 ) : ( n254 ) ;
assign n256 =  ( n234 ) ? ( n245 ) : ( n255 ) ;
assign n257 =  ( n233 ) ? ( n245 ) : ( n256 ) ;
assign n258 =  ( n232 ) ? ( n245 ) : ( n257 ) ;
assign n259 =  ( n231 ) ? ( n245 ) : ( n258 ) ;
assign n260 =  ( n228 ) ? ( n245 ) : ( n259 ) ;
assign n261 =  (  RAM_3 [ n229 ] )  ;
assign n262 =  ( n236 ) ? ( n253 ) : ( n261 ) ;
assign n263 =  ( n235 ) ? ( n253 ) : ( n262 ) ;
assign n264 =  ( n234 ) ? ( n253 ) : ( n263 ) ;
assign n265 =  ( n233 ) ? ( n253 ) : ( n264 ) ;
assign n266 =  ( n232 ) ? ( n253 ) : ( n265 ) ;
assign n267 =  ( n231 ) ? ( n253 ) : ( n266 ) ;
assign n268 =  ( n228 ) ? ( n253 ) : ( n267 ) ;
assign n269 =  (  RAM_2 [ n229 ] )  ;
assign n270 =  ( n236 ) ? ( n261 ) : ( n269 ) ;
assign n271 =  ( n235 ) ? ( n261 ) : ( n270 ) ;
assign n272 =  ( n234 ) ? ( n261 ) : ( n271 ) ;
assign n273 =  ( n233 ) ? ( n261 ) : ( n272 ) ;
assign n274 =  ( n232 ) ? ( n261 ) : ( n273 ) ;
assign n275 =  ( n231 ) ? ( n261 ) : ( n274 ) ;
assign n276 =  ( n228 ) ? ( n261 ) : ( n275 ) ;
assign n277 =  (  RAM_1 [ n229 ] )  ;
assign n278 =  ( n236 ) ? ( n269 ) : ( n277 ) ;
assign n279 =  ( n235 ) ? ( n269 ) : ( n278 ) ;
assign n280 =  ( n234 ) ? ( n269 ) : ( n279 ) ;
assign n281 =  ( n233 ) ? ( n269 ) : ( n280 ) ;
assign n282 =  ( n232 ) ? ( n269 ) : ( n281 ) ;
assign n283 =  ( n231 ) ? ( n269 ) : ( n282 ) ;
assign n284 =  ( n228 ) ? ( n269 ) : ( n283 ) ;
assign n285 =  (  RAM_0 [ n229 ] )  ;
assign n286 =  ( n236 ) ? ( n277 ) : ( n285 ) ;
assign n287 =  ( n235 ) ? ( n277 ) : ( n286 ) ;
assign n288 =  ( n234 ) ? ( n277 ) : ( n287 ) ;
assign n289 =  ( n233 ) ? ( n277 ) : ( n288 ) ;
assign n290 =  ( n232 ) ? ( n277 ) : ( n289 ) ;
assign n291 =  ( n231 ) ? ( n277 ) : ( n290 ) ;
assign n292 =  ( n228 ) ? ( n277 ) : ( n291 ) ;
assign n293 =  ( n236 ) ? ( n285 ) : ( n230 ) ;
assign n294 =  ( n235 ) ? ( n285 ) : ( n293 ) ;
assign n295 =  ( n234 ) ? ( n285 ) : ( n294 ) ;
assign n296 =  ( n233 ) ? ( n285 ) : ( n295 ) ;
assign n297 =  ( n232 ) ? ( n285 ) : ( n296 ) ;
assign n298 =  ( n231 ) ? ( n285 ) : ( n297 ) ;
assign n299 =  ( n228 ) ? ( n285 ) : ( n298 ) ;
assign n300 =  { ( n292 ) , ( n299 ) }  ;
assign n301 =  { ( n284 ) , ( n300 ) }  ;
assign n302 =  { ( n276 ) , ( n301 ) }  ;
assign n303 =  { ( n268 ) , ( n302 ) }  ;
assign n304 =  { ( n260 ) , ( n303 ) }  ;
assign n305 =  { ( n252 ) , ( n304 ) }  ;
assign n306 =  { ( n244 ) , ( n305 ) }  ;
assign n307 =  { ( arg_1_TDATA ) , ( n306 ) }  ;
assign n308 =  ( n203 ) ? ( stencil_8 ) : ( n307 ) ;
assign n309 =  ( n9 ) ? ( n308 ) : ( stencil_8 ) ;
assign n310 =  ( n4 ) ? ( stencil_8 ) : ( n309 ) ;
assign n311 = ~ ( n4 ) ;
assign n312 = ~ ( n9 ) ;
assign n313 =  ( n311 ) & ( n312 )  ;
assign n314 =  ( n311 ) & ( n9 )  ;
assign n315 = ~ ( n228 ) ;
assign n316 =  ( n314 ) & ( n315 )  ;
assign n317 =  ( n314 ) & ( n228 )  ;
assign RAM_0_addr0 = n317 ? (n229) : (0);
assign RAM_0_data0 = n317 ? (arg_1_TDATA) : (RAM_0[0]);
assign n318 = ~ ( n231 ) ;
assign n319 =  ( n314 ) & ( n318 )  ;
assign n320 =  ( n314 ) & ( n231 )  ;
assign RAM_1_addr0 = n320 ? (n229) : (0);
assign RAM_1_data0 = n320 ? (arg_1_TDATA) : (RAM_1[0]);
assign n321 = ~ ( n232 ) ;
assign n322 =  ( n314 ) & ( n321 )  ;
assign n323 =  ( n314 ) & ( n232 )  ;
assign RAM_2_addr0 = n323 ? (n229) : (0);
assign RAM_2_data0 = n323 ? (arg_1_TDATA) : (RAM_2[0]);
assign n324 = ~ ( n233 ) ;
assign n325 =  ( n314 ) & ( n324 )  ;
assign n326 =  ( n314 ) & ( n233 )  ;
assign RAM_3_addr0 = n326 ? (n229) : (0);
assign RAM_3_data0 = n326 ? (arg_1_TDATA) : (RAM_3[0]);
assign n327 = ~ ( n234 ) ;
assign n328 =  ( n314 ) & ( n327 )  ;
assign n329 =  ( n314 ) & ( n234 )  ;
assign RAM_4_addr0 = n329 ? (n229) : (0);
assign RAM_4_data0 = n329 ? (arg_1_TDATA) : (RAM_4[0]);
assign n330 = ~ ( n235 ) ;
assign n331 =  ( n314 ) & ( n330 )  ;
assign n332 =  ( n314 ) & ( n235 )  ;
assign RAM_5_addr0 = n332 ? (n229) : (0);
assign RAM_5_data0 = n332 ? (arg_1_TDATA) : (RAM_5[0]);
assign n333 = ~ ( n236 ) ;
assign n334 =  ( n314 ) & ( n333 )  ;
assign n335 =  ( n314 ) & ( n236 )  ;
assign RAM_6_addr0 = n335 ? (n229) : (0);
assign RAM_6_data0 = n335 ? (arg_1_TDATA) : (RAM_6[0]);
assign n336 = ~ ( n11 ) ;
assign n337 =  ( n314 ) & ( n336 )  ;
assign n338 =  ( n314 ) & ( n11 )  ;
assign RAM_7_addr0 = n338 ? (n229) : (0);
assign RAM_7_data0 = n338 ? (arg_1_TDATA) : (RAM_7[0]);
/*
function [7:0] gb_fun ;
input [647:0] arg0;
    begin
//TODO: Add the specific function HERE.    end
endfunction
*/

always @(posedge clk) begin
   if(rst) begin
       RAM_w <= RAM_w;
       RAM_x <= RAM_x;
       RAM_y <= RAM_y;
       arg_0_TDATA <= arg_0_TDATA;
       arg_0_TVALID <= arg_0_TVALID;
       arg_1_TREADY <= arg_1_TREADY;
       proc_in <= proc_in;
       stencil_0 <= stencil_0;
       stencil_1 <= stencil_1;
       stencil_2 <= stencil_2;
       stencil_3 <= stencil_3;
       stencil_4 <= stencil_4;
       stencil_5 <= stencil_5;
       stencil_6 <= stencil_6;
       stencil_7 <= stencil_7;
       stencil_8 <= stencil_8;
   end
   else if(step) begin
       RAM_w <= n16;
       RAM_x <= n20;
       RAM_y <= n26;
       arg_0_TDATA <= n192;
       arg_0_TVALID <= n199;
       arg_1_TREADY <= n201;
       proc_in <= n202;
       stencil_0 <= n206;
       stencil_1 <= n209;
       stencil_2 <= n212;
       stencil_3 <= n215;
       stencil_4 <= n218;
       stencil_5 <= n221;
       stencil_6 <= n224;
       stencil_7 <= n227;
       stencil_8 <= n310;
       RAM_0 [ RAM_0_addr0 ] <= RAM_0_data0;
       RAM_1 [ RAM_1_addr0 ] <= RAM_1_data0;
       RAM_2 [ RAM_2_addr0 ] <= RAM_2_data0;
       RAM_3 [ RAM_3_addr0 ] <= RAM_3_data0;
       RAM_4 [ RAM_4_addr0 ] <= RAM_4_data0;
       RAM_5 [ RAM_5_addr0 ] <= RAM_5_data0;
       RAM_6 [ RAM_6_addr0 ] <= RAM_6_data0;
       RAM_7 [ RAM_7_addr0 ] <= RAM_7_data0;
   end
end
endmodule
