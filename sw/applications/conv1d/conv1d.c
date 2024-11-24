#include <stdint.h>
#include <limits.h>
#include "conv1d.h"
#include "dma_sdk.h"
#include "data.h" // for PAD, STRIDE, KERNEL_LEN

void conv1d_sw(const int8_t * const input_data, const int8_t * const filter, int32_t *output_data, const uint32_t input_len, const uint32_t input_ch, const uint32_t output_ch)
{
    // Calculate the length of the input data after padding
    uint32_t padded_input_len = input_len + 2 * PAD;

    // Calculate the length of the output data
    uint32_t output_len = ((padded_input_len - KERNEL_LEN) / STRIDE) + 1;

    // Loop over each output channel (output_ch times)
    for (uint32_t m = 0; m < output_ch; m++) {
        // Loop over each output position
        for (uint32_t o = 0; o < output_len; o++) {
            int32_t accumulated_output = 0;

            // Loop over each input channel
            for (uint32_t n = 0; n < input_ch; n++) {
                // Compute the starting index in the input data for this convolution window
                int32_t input_start = o * STRIDE - PAD;

                int32_t sum = 0;

                // Loop over the kernel elements
                for (uint32_t k_idx = 0; k_idx < KERNEL_LEN; k_idx++) {
                    int32_t input_index = input_start + k_idx;
                    int8_t input_value;

                    // Handle padding: if the input index is outside the valid range, use zero
                    if (input_index < 0 || input_index >= (int32_t)input_len) {
                        // Input value is zero due to padding
                        input_value = 0;
                    } else {
                        // Access the input data using the mem2d macro
                        input_value = mem2d(input_data, input_len, n, input_index);
                    }

                    // Access the filter coefficient using the mem3d macro
                    int8_t filter_value = mem3d(filter, input_ch, KERNEL_LEN, m, n, k_idx);

                    // Multiply and accumulate
                    sum += input_value * filter_value;
                }

                // Accumulate the sum from all input channels
                accumulated_output += sum;
            }

            // Store the accumulated result in the output data array
            // The output data is organized in row-major order: output_data[m][o] = output_data[m * output_len + o]
            output_data[m * output_len + o] = accumulated_output;
        }
    }
}

void conv1d_hw(const int8_t * const in_data, const int8_t * const filter, int32_t *output_data, const uint32_t input_len, const uint32_t input_ch, const uint32_t output_ch) {
    // Tiling loop(s)
    for (size_t o = 0; o < output_ch; o++)
    {
        // for ...

        /*
         * TODO: program the system DMA to transfer the current input data chunk
         * (tile) and, possibly, filters, from the system memory to the hardware
         * accelerator's private buffer.
         */
        // dma_copy(...); // from `dma_sdk.h`

        /*
         * TODO: call the appropriate functions from the hardware accelerator's
         * driver to start the computation, then wait for it to complete.
         */
        // conv_accel_start(); // from `conv_accel.h`
        // conv_accel_wait(); // from `conv_accel.h`

        /*
         * TODO: program the system DMA to transfer the current output data chunk
         * from the hardware accelerator's private buffer to the `R` buffer in
         * the system main memory.
         */
        // dma_copy(...); // from `dma_sdk.h`
    }
    
    return;
}