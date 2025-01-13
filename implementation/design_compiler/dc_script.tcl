set ROOT_DIR ../../..

set_host_options -max_cores 16

set READ_LIBS ${SCRIPT_DIR}/read_libs.tcl
set CONSTRAINTS ${SCRIPT_DIR}/set_constraints.tcl

remove_design -all

source ${READ_LIBS}

define_design_lib WORK -path ./work

source ${READ_SOURCES}.tcl

elaborate ${TOP_MODULE}
link

write -f ddc -hierarchy -output ${REPORT_DIR}/precompiled.ddc

source ${CONSTRAINTS}

report_clocks -attributes -skew > ${REPORT_DIR}/clocks.rpt
report_timing -loop -max_paths 10 > ${REPORT_DIR}/timing_loop.rpt

compile_ultra -no_autoungroup -no_boundary_optimization -timing -gate_clock

write -f ddc -hierarchy -output ${REPORT_DIR}/compiled.ddc

change_names -rules verilog -hier

write -format verilog -hier -o ${REPORT_DIR}/netlist.v

write_sdc -version 1.7 ${REPORT_DIR}/netlist.sdc
write_sdf -version 2.1 ${REPORT_DIR}/netlist.sdf

report_timing -nosplit > ${REPORT_DIR}/timing.rpt
report_area -hier -nosplit > ${REPORT_DIR}/area.rpt
report_resources -hierarchy > ${REPORT_DIR}/resources.rpt
report_constraints > ${REPORT_DIR}/constraints.rpt
report_clock_gating > ${REPORT_DIR}/clock_gating.rpt
report_power > ${REPORT_DIR}/power.rpt

### save here also the report
set report_date [sh date +%Y_%m_%d_%k:%M]

set REPORT_PATH ${ROOT_DIR}/synthesis

file mkdir ${REPORT_PATH}/output_$report_date

write -f ddc -hierarchy -output ${REPORT_PATH}/output_$report_date/compiled.ddc

sh cp -R ${REPORT_DIR} ${REPORT_PATH}/output_$report_date

#this is where the backend tool gets all the files
sh rm -rf ${REPORT_DIR}/synthesis/last_output
file mkdir ${REPORT_PATH}/last_output

sh cp -R ${REPORT_DIR}/synth.log ${REPORT_PATH}/last_output
sh cp -R ${REPORT_DIR}/netlist.sdc ${REPORT_PATH}/last_output
sh cp -R ${REPORT_DIR}/netlist.sdf ${REPORT_PATH}/last_output
sh cp -R ${REPORT_DIR}/netlist.v ${REPORT_PATH}/last_output
sh cp -R ${REPORT_DIR}/precompiled.ddc ${REPORT_PATH}/last_output
sh cp -R ${REPORT_DIR}/compiled.ddc ${REPORT_PATH}/last_output
sh cp -R ${REPORT_DIR}/timing.rpt ${REPORT_PATH}/last_output
sh cp -R ${REPORT_DIR}/area.rpt ${REPORT_PATH}/last_output
sh cp -R ${REPORT_DIR}/resources.rpt ${REPORT_PATH}/last_output
sh cp -R ${REPORT_DIR}/timing_loop.rpt ${REPORT_PATH}/last_output
sh cp -R ${REPORT_DIR}/clocks.rpt ${REPORT_PATH}/last_output
