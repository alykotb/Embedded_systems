################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
MCAL/CAN/CAN.obj: ../MCAL/CAN/CAN.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Aly/workspace_v7/node2" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --strict_ansi --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --check_misra="all" --preproc_with_compile --preproc_dependency="MCAL/CAN/CAN.d_raw" --obj_directory="MCAL/CAN" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


