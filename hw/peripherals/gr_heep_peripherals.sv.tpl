// Copyright 2024 Politecnico di Torino.
// Copyright and related rights are licensed under the Solderpad Hardware
// License, Version 2.0 (the "License"); you may not use this file except in
// compliance with the License. You may obtain a copy of the License at
// http://solderpad.org/licenses/SHL-2.0. Unless required by applicable law
// or agreed to in writing, software, hardware and materials distributed under
// this License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.
//
// File: gr_heep_peripherals.sv
// Author(s):
//   Luigi Giuffrida
// Date: 08/11/2024
// Description: Template for the GR-heep peripherals module

module gr_heep_peripherals (
    input logic clk_i,
    input logic rst_ni,

% if (xbar_nmasters > 0):
    // External peripherals master ports
    obi_pkg::obi_req_t  [gr_heep_pkg::ExtXbarNmasterRnd-1:0] gr_heep_master_req_o,
    obi_pkg::obi_resp_t [gr_heep_pkg::ExtXbarNmasterRnd-1:0] gr_heep_master_resp_i${'' if (xbar_nslave + periph_nslaves + ext_interrupts == 0) else ','}
% endif

% if (xbar_nslaves > 0):
    // External peripherals slave ports
    obi_pkg::obi_req_t  [gr_heep_pkg::ExtXbarNmasterRnd-1:0] gr_heep_slave_req_i,
    obi_pkg::obi_resp_t [gr_heep_pkg::ExtXbarNmasterRnd-1:0] gr_heep_slave_resp_o${'' if (periph_nslaves + ext_interrupts == 0) else ','}
% endif

% if (periph_nslaves > 0):
    // External peripherals configuration ports
    reg_pkg::reg_req_t [gr_heep_pkg::ExtPeriphNSlaveRnd-1:0] gr_heep_peripheral_req_i,
    reg_pkg::reg_rsp_t [gr_heep_pkg::ExtPeriphNSlaveRnd-1:0] gr_heep_peripheral_rsp_o${'' if (ext_interrupts == 0) else ','}
% endif

% if (ext_interrupts > 0):
    // External peripherals interrupt ports
    logic [ExtInterrupts-1:0] gr_heep_peripheral_int_o
%endif
);

  // Instantiate here the external peripherals

  cnt_obi u_cnt_obi (
    .clk_i,
    .rst_ni,

    .obi_req_i(gr_heep_slave_req_i[0].req),
    .obi_we_i(gr_heep_slave_req_i[0].we),
    .obi_be_i(gr_heep_slave_req_i[0].be),
    .obi_addr_i(gr_heep_slave_req_i[0].addr),
    .obi_wdata_i(gr_heep_slave_req_i[0].wdata),
    .obi_gnt_o(gr_heep_slave_resp_o[0].gnt),
    .obi_rvalid_o(gr_heep_slave_resp_o[0].rvalid),
    .obi_rdata_o(gr_heep_slave_resp_o[0].rdata),

    .reg_valid_i(gr_heep_peripheral_req_i[0].valid),
    .reg_write_i(gr_heep_peripheral_req_i[0].write),
    .reg_wstrb_i(gr_heep_peripheral_req_i[0].wstrb),
    .reg_addr_i(gr_heep_peripheral_req_i[0].addr),
    .reg_wdata_i(gr_heep_peripheral_req_i[0].wdata),
    .reg_error_o(gr_heep_peripheral_rsp_o[0].error),
    .reg_ready_o(gr_heep_peripheral_rsp_o[0].ready),
    .reg_rdata_o(gr_heep_peripheral_rsp_o[0].rdata),

    .tc_int_o(gr_heep_peripheral_int_o[0])
  );

endmodule
