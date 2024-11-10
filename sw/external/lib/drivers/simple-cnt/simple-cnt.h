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
// File: simple-cnt.h
// Author(s):
//   Michele Caon
// Date: 10/11/2024
// Description: Driver header for the counter peripheral

#ifndef SIMPLE_CNT_HH_
#define SIMPLE_CNT_HH_

#include <stdint.h>

/*****************************/
/* ---- DRIVER ROUTINES ---- */
/*****************************/

/**
 * @brief Enable the counter.
 * 
 */
inline void simple_cnt_enable();

/**
 * @brief Disable the counter.
 * 
 */
inline void simple_cnt_disable();

/**
 * @brief Clear the counter.
 * 
 */
inline void simple_cnt_clear();

/**
 * @brief Set the threshold value of the counter.
 * 
 * @param threshold The threshold value to set.
 */
void simple_cnt_set_threshold(uint32_t threshold);

/**
 * @brief Get the threshold value of the counter.
 * 
 * @return The threshold value.
 */
uint32_t simple_cnt_get_threshold();

/**
 * @brief Set the value of the counter.
 * 
 * @param value The desired counter value.
 */
void simple_cnt_set_value(uint32_t value);

/**
 * @brief Get the current value of the counter.
 * 
 * @return The current value.
 */
uint32_t simple_cnt_get_value();

/**
 * @brief Poll the TC bit of the counter.
 * 
 * @return true if the TC bit is set, false otherwise.
 */
inline uint8_t simple_cnt_tc();

/**
 * @brief Clear the counter TC bit.
 * 
 */
inline void simple_cnt_clear_tc();

/**
 * @brief Counter interrupt handler.
 * 
 */
void simple_cnt_irq_handler();

/**
 * @brief Wait for the counter interrupt.
 *
 */
void simple_cnt_wait();

#endif /* SIMPLE_CNT_HH_ */
