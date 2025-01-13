# Vendoring components

[Vendor](https://opentitan.org/book/util/doc/vendor.html) is a tool from OpenTitan that allows to import files from other repositories. We use it to import hardware modules and primitives that we want to use inside our own project. Together with FuseSoC and `.core` files, Vendor makes it possible to import hardware modules similarly to how software modules are imported in Python or other languages.

In order to know where to fetch the files from, Vendor needs a `.vendor.hjson` file like the ones that you see in this directory. Optionally, Vendor may apply patches to the imported files, for example to make the imported module compatible with our project build and simulation flow.

## Assignment
In this laboratory experience, you must use Vendor to import the RTL description of the 1D convolution accelerator that you designed, so you can instantiate it into GR-HEEP external peripherals and access it through the bus and, therefore, from the software running on the CPU.

To do so, you need to write the appropriate `conv1d.vendor.hjson` file, taking inspiration from the [`simple_cnt.vendor.hjson`](./simple_cnt.vendor.hjson) file in this directory, that imports the RTL description of a simple memory-mapped counter used by the [`sw/applications/simple-cnt`](./../../sw/applications/simple-cnt/main.c) application.

Once yu have created the file, run the `make vendor-update` target from the top-level makefile, that pulls all the vendored IPs into this directory.

After doing so, you can instantiate the module inside [`gr_heep_peripherals.sv.tpl`](../peripherals/gr_heep_peripherals.sv.tpl), and add a dependency into the top-level [`GR-HEEP.core`](../../GR-HEEP.core) file, exactly as it is already done for the simple counter.