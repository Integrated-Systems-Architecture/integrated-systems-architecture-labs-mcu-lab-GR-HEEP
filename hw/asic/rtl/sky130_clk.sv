// Copyright 2022 OpenHW Group
// Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
// SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1

module sky130_clk_gating (
   input  logic clk_i,
   input  logic en_i,
   input  logic test_en_i,
   output logic clk_o
);


  sky130_fd_sc_hd__dlclkp_2 clkp_i (
    .GCLK(clk_o),
    .GATE(en_i),
    .CLK(clk_i)
  );


endmodule

module sky130_clk_inverter (
  input  logic clk_i,
  output logic clk_o
);
  
  sky130_fd_sc_hd__clkinv_2 inv_i (
    .A(clk_i),
    .Y(clk_o)
  );

endmodule


module sky130_clk_mux2 (
  input  logic clk0_i,
  input  logic clk1_i,
  input  logic clk_sel_i,
  output logic clk_o
);

  sky130_fd_sc_hdll__clkmux2_2 mux2_i (
    .A0(clk0_i),
    .A1(clk1_i),
    .S(clk_sel_i),
    .X(clk_o)
  );

endmodule

module tc_clk_mux2(
  input logic clk0_i,
  input logic clk1_i,
  input logic clk_sel_i,
  output logic clk_o
);

  sky130_clk_mux2 clk_mux2_i (
    .*
  );

endmodule

module  tc_clk_gating (
  input logic clk_i,
  input logic en_i,
  input logic test_en_i,
  output logic clk_o
);

  sky130_clk_gating clk_gating_i (
    .*
  );


endmodule

module cluster_clock_inverter(
  input  logic clk_i,
  output logic clk_o
);

  sky130_clk_inverter clk_inv_i (
    .*
  );

endmodule

module tc_clk_inverter(
  input  logic clk_i,
  output logic clk_o
);

  sky130_clk_inverter clk_inv_i (
    .*
  );

endmodule

module pulp_clock_mux2 (
  input  logic clk0_i,
  input  logic clk1_i,
  input  logic clk_sel_i,
  output logic clk_o
);

  sky130_clk_mux2 clk_mux2_i (
    .*
  );

endmodule

module cv32e40p_clock_gate (
   input  logic clk_i,
   input  logic en_i,
   input  logic scan_cg_en_i,
   output logic clk_o
);

  sky130_clk_gating clk_gate_i (
    .clk_i,
    .en_i,
    .test_en_i(scan_cg_en_i),
    .clk_o
  );

endmodule

module cve2_clock_gate (
   input  logic clk_i,
   input  logic en_i,
   input  logic scan_cg_en_i,
   output logic clk_o
);

  sky130_clk_gating clk_gate_i (
    .clk_i,
    .en_i,
    .test_en_i(scan_cg_en_i),
    .clk_o
  );

endmodule
