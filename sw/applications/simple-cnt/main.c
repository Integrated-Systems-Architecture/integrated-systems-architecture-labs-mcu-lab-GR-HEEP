// System library headers
#include <stdio.h>

// Custom library headers
#include "core_v_mini_mcu.h"
#include "simple_cnt.h"
#include "ext_irq.h"

// Main body
// ---------
int main(void)
{
    uint32_t val = 256;
    uint32_t ret = 0;

    // Initialize external interrupts
    ext_irq_init();

    // Set the counter threshold
    simple_cnt_set_threshold(val);

    // Read back the counter threshold
    ret = simple_cnt_get_threshold();
    if (val != ret) {
        printf("Error: threshold value mismatch\n");
        return -1;
    }

    // Set the counter value
    val = 42;
    simple_cnt_set_value(val);

    // Read back the counter value
    ret = simple_cnt_get_value();
    if (val != ret) {
        printf("Error: value mismatch\n");
        return -1;
    }

    // Clear the counter
    simple_cnt_clear();

    // Read back the counter value
    ret = simple_cnt_get_value();
    if (0 != ret) {
        printf("Error: value mismatch\n");
        return -1;
    }

    // Enable the counter
    simple_cnt_enable();

    // Wait for the counter to reach the threshold
    while (!simple_cnt_tc()) {
        // Busy waiting
    }
    simple_cnt_clear_tc(); // clear TC bit
    printf("Counter reached threshold\n");

    // Wait for counter interrupt
    simple_cnt_wait();
    printf("Counter interrupt received\n");

    // Disable the counter
    simple_cnt_disable();

    // Read back the counter value
    ret = simple_cnt_get_value();
    printf("Done. Counter value: %d\n", ret);
}
