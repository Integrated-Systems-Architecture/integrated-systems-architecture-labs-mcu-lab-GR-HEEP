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
// File: simple-cnt.c
// Author(s):
//   Michele Caon
// Date: 10/11/2024
// Description: Driver for the simple counter.

#include <stdint.h>

#include "simple-cnt.h"
#include "gr_heep.h"
#include "cnt_control_reg.h"
#include "hart.h" // for wait_for_interrupt()

// Interrupt flag
static volatile uint8_t simple_cnt_irq_flag = 0;

inline void simple_cnt_enable() {
    *(volatile uint32_t *)(SIMPLECNTCTL_START_ADDRESS + CNT_CONTROL_CONTROL_REG_OFFSET) |= (1 << CNT_CONTROL_CONTROL_ENABLE_BIT);
}

inline void simple_cnt_disable() {
    *(volatile uint32_t *)(SIMPLECNTCTL_START_ADDRESS + CNT_CONTROL_CONTROL_REG_OFFSET) &= ~(1 << CNT_CONTROL_CONTROL_ENABLE_BIT);
}

inline void simple_cnt_clear() {
    *(volatile uint32_t *)(SIMPLECNTCTL_START_ADDRESS + CNT_CONTROL_CONTROL_REG_OFFSET) |= (1 << CNT_CONTROL_CONTROL_CLEAR_BIT);
}

void simple_cnt_set_threshold(uint32_t threshold) {
    *(volatile uint32_t *)(SIMPLECNTCTL_START_ADDRESS + CNT_CONTROL_THRESHOLD_REG_OFFSET) = threshold;
}

uint32_t simple_cnt_get_threshold() {
    return *(volatile uint32_t *)(SIMPLECNTCTL_START_ADDRESS + CNT_CONTROL_THRESHOLD_REG_OFFSET);
}

void simple_cnt_set_value(uint32_t value) {
    *(volatile uint32_t *)(SIMPLECNT_START_ADDRESS) = value;
}

uint32_t simple_cnt_get_value() {
    return *(volatile uint32_t *)(SIMPLECNT_START_ADDRESS);
}

inline uint8_t simple_cnt_tc() {
    return (*(volatile uint32_t *)(SIMPLECNTCTL_START_ADDRESS + CNT_CONTROL_STATUS_REG_OFFSET) & (1 << CNT_CONTROL_STATUS_TC_BIT)) != 0;
}

void simple_cnt_clear_tc() {
    *(volatile uint32_t *)(SIMPLECNTCTL_START_ADDRESS + CNT_CONTROL_STATUS_REG_OFFSET) |= (1 << CNT_CONTROL_STATUS_TC_BIT);
}

void simple_cnt_irq_handler() {
    // Set IRQ flag
    simple_cnt_irq_flag = 1;

    // Clear the TC bit
    simple_cnt_clear_tc();
}

void simple_cnt_wait() {
    // Wait for the kernel to complete
    while (simple_cnt_irq_flag == 0) {
        wait_for_interrupt();
    }
    simple_cnt_irq_flag = 0; // reset counter interrupt flag
}
