# All the path are relative to build directory

# Define the path to the root directory of the project
set ROOT_DIR ../../../

# Define the path to the directory containing the standard cells
set STD_CELLS_DIR $ROOT_DIR/hw/asic/tech/std-cells/
set MEM_CELLS_DIR $ROOT_DIR/hw/asic/tech/memory/

# Define the name of the files containing the standard cells
set STD_CELLS_DB [glob -directory $STD_CELLS_DIR -- "sky130_fd_sc_hd*.db"]
set MEM_DB [glob -directory $MEM_CELLS_DIR -- "sky130_sram*.db"]

set target_library "$STD_CELLS_DB $MEM_DB"

# link library
set link_library "* $target_library"

#debug output info
puts "------------------------------------------------------------------"
puts "USED LIBRARIES"
puts $link_library
puts "------------------------------------------------------------------"

set link_library " * $link_library"

