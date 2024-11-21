import argparse
import os
import numpy as np
from torch.nn import functional as fun
from c_gen import CFileGen


def main():
    descr = """\
# Generate the input data and the golden output for 1D convolution, used by main.c to run the kernel.
    R = conv1D(A, F, STRIDE, PAD)
"""

    # Create command line parser
    cmd_parser = argparse.ArgumentParser(
        prog="datagen", description="Conv1d golden model.", epilog=descr
    )

    # Define command line options
    cmd_parser.add_argument(
        "--in_len", "-l", type=int, default=8, help="Length of every input channel."
    )
    cmd_parser.add_argument(
        "--in_ch", "-n", type=int, default=4, help="Number of input channels."
    )
    cmd_parser.add_argument(
        "--k_len", "-k", type=int, default=3, help="Length of the kernel."
    )
    cmd_parser.add_argument(
        "--f_num",
        "-f",
        type=int,
        default=1,
        help="Number of filters (output channels).",
    )
    cmd_parser.add_argument(
        "--stride", "-r", type=int, default=1, help="Stride of the convolution."
    )
    cmd_parser.add_argument(
        "--padding", "-p", type=int, default=0, help="Padding of the convolution."
    )
    cmd_parser.add_argument(
        "--outdir",
        "-o",
        type=str,
        default=os.path.dirname(__file__),
        help="directory where to store the otuput files.",
    )
    cmd_parser.add_argument(
        "--seed", "-s", type=int, help="Seed for numpy PRG (normally used for debug)."
    )
    cmd_parser.add_argument(
        "--version",
        "-v",
        action="version",
        version="%(prog)s 0.1.0",
        help="print the version and exit.",
    )

    # Parse command line arguments
    args = cmd_parser.parse_args()

    # Set parameters
    out_dir = args.outdir
    input_len = args.in_len
    input_ch = args.in_ch
    kernel_len = args.k_len
    f_num = args.f_num
    stride = args.stride
    pad = args.padding
    data_header = "data.h"

    # Print arguments
    print("!D convolution golden model.")
    print("    R = conv1D(A, F, STRIDE, PAD)")
    print("Arguments:")
    print("- output directory: " + out_dir)
    print("- input length: " + str(input_len))
    print("- input channels: " + str(input_ch))
    print("- kernel length: " + str(kernel_len))
    print("- number of filters: " + str(f_num))
    print("- stride: " + str(stride))
    print("- padding: " + str(pad))

    # Generate random inputs
    if args.seed is not None:
        np.random.seed(args.seed)

    # Input matrix A [input_len x input_ch]
    A = np.random.randint(
        low=0, high=(2**7) - 1, size=(input_len, input_ch), dtype=np.int8
    )

    # Filter F [kernel_len x input_ch x f_num]
    F = np.random.randint(
        low=0, high=(2**7) - 1, size=(kernel_len, input_ch, f_num), dtype=np.int8
    )

    # Bias B [f_num]
    B = np.random.randint(low=0, high=(2**7) - 1, size=(f_num), dtype=np.int8)

    # Golden output [input_len x f_num]
    R = np.zeros((input_len, f_num), dtype=np.int32)
    R = fun.conv1d(A, F, stride=stride, padding=pad, bias=B)

    # Generate C files

    header_gen = CFileGen()

    header_gen.add_comment("1D convolution data")
    header_gen.add_comment("Input data")
    header_gen.add_comment("A: input matrix [input_len x input_ch]")
    header_gen.add_comment("F: filter matrix [kernel_len x input_ch x f_num]")
    header_gen.add_comment("Output data")
    header_gen.add_comment("R: output matrix [input_len x f_num]")
    header_gen.add_comment("Stride: " + str(stride))
    header_gen.add_comment("Padding: " + str(pad))

    header_gen.add_define("INPUT_LEN", str(input_len))
    header_gen.add_define("INPUT_CH", str(input_ch))
    header_gen.add_define("KERNEL_LEN", str(kernel_len))
    header_gen.add_define("F_NUM", str(f_num))
    header_gen.add_define("STRIDE", str(stride))
    header_gen.add_define("PAD", str(pad))

    header_gen.add_input_matrix("A", A)
    header_gen.add_input_matrix("F", F)
    header_gen.add_input_matrix("B", B)
    header_gen.add_output_matrix("R", R)

    header_gen.write_header(out_dir, data_header)
    print("- generated header file in '" + out_dir + "/" + data_header + "'.")


if __name__ == "__main__":
    main()
