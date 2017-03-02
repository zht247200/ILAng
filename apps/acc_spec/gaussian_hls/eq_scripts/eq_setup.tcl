# analyze and elaborate two implementations (integrated)

set ROOT /home/byhuang/ILA/apps/acc_spec/gaussian_hls
set SRC $ROOT/eq_verilog

analyze -clear
elaborate -clear

analyze -verilog $SRC/FIFO_hls_target_call_slice_stream_V_value_V.v 
analyze -verilog $SRC/FIFO_hls_target_linebuffer_1_in_stream_V_value_V.v
analyze -verilog $SRC/FIFO_hls_target_p_p2_in_bounded_stencil_stream_s.v
analyze -verilog $SRC/eq_top.v
analyze -verilog $SRC/hls_target.v
analyze -verilog $SRC/hls_target_Loop_1_proc.v
analyze -verilog $SRC/hls_target_call.v
analyze -verilog $SRC/hls_target_call_Loop_LB2D_buf_proc.v
analyze -verilog $SRC/hls_target_call_Loop_LB2D_buf_proc_buffer_0_value_V.v
analyze -verilog $SRC/hls_target_call_Loop_LB2D_shift_proc.v
analyze -verilog $SRC/hls_target_linebuffer.v
analyze -verilog $SRC/hls_target_linebuffer_1.v
analyze -verilog $SRC/hls_target_linebuffer_Loop_1_proc.v
analyze -verilog $SRC/ila_target.v

elaborate -bbox {1} -bbox_a {4096}

clock -clear; clock clk

reset -expression {:global_formal_reset} {rst_init};
