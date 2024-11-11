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
// File: handler.c
// Author(s):
//   Michele Caon
// Date: 11/11/2024
// Description: External interrupt handlers

#include "handler.h"
#include "rv_plic.h"
#include "core_v_mini_mcu.h"
#include "simple_cnt.h"

/**********************************/
/* ---- FUNCTION DEFINITIONS ---- */
/**********************************/

int ext_irq_init(void) {
    // Initialize PLIC for external interrupts
    if (plic_Init() != kPlicOk)
        return -1;
    if (plic_irq_set_priority(EXT_INTR_0, 1) != kPlicOk)
        return -1;
    if (plic_irq_set_enabled(EXT_INTR_0, kPlicToggleEnabled) != kPlicOk)
        return -1;

    // Install external interrupt handler(s)

    // Simple counter interrupt handler (EXT_INTR_0)
    if (plic_assign_external_irq_handler(EXT_INTR_0, &simple_cnt_irq_handler) != kPlicOk)
        return -1;

    // Other external interrupt handlers...

    // Return success
    return 0;
}
