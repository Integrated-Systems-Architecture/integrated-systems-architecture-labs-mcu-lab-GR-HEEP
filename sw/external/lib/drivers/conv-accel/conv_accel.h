#ifndef CONV_ACCEL_HH_
#define CONV_ACCEL_HH_

/**
 * @brief Initialize the accelerator.
 * 
 */
void conv_accel_init();

/**
 * @brief Trigger the start of processing.
 * 
 */
void conv_accel_start();

/**
 * @brief Wait for the accelerator to complete execution.
 * 
 */
void conv_accel_wait();

#endif /* CONV_ACCEL_HH_ */
