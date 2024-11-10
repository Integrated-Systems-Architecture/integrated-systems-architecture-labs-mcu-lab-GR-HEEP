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
// File: gr_heep.h.tpl
// Author(s):
//   Michele Caon
// Date: 10/11/2024
// Description: GR-HEEP definitions

#ifndef GR_HEEP_H_
#define GR_HEEP_H_

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include "core_v_mini_mcu.h"

// MEMORY MAP
// ----------
// External peripherals
% for peripheral in peripherals:
#define ${peripheral['name'].upper()}_START_ADDRESS (PERIPHERAL_START_ADDRESS + ${hex(peripheral['offset'])})
#define ${peripheral['name'].upper()}_SIZE ${hex(peripheral['size'])}
#define ${peripheral['name'].upper()}_END_ADDRESS ${hex(peripheral['end_address'])}
#define ${peripheral['name'].upper()}_IDX ${peripheral['idx']}

%endfor

// External slaves
% for slave in slaves:
#define ${slave['name'].upper()}_START_ADDRESS (EXT_SLAVE_START_ADDRESS + ${hex(slave['offset'])})
#define ${slave['name'].upper()}_SIZE ${hex(slave['size'])}
#define ${slave['name'].upper()}_END_ADDRESS ${hex(slave['end_address'])}
#define ${slave['name'].upper()}_IDX ${slave['idx']}

%endfor

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // GR_HEEP_H_
