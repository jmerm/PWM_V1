################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_19.6.0.STS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/Users/John/workspace_v9/PWM_V1" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/F2806x_common/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/common/lib" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/headers/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/headers/source" --include_path="C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_19.6.0.STS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2806x_CodeStartBranch.obj: C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/common/source/F2806x_CodeStartBranch.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_19.6.0.STS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/Users/John/workspace_v9/PWM_V1" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/F2806x_common/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/common/lib" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/headers/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/headers/source" --include_path="C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_19.6.0.STS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2806x_CpuTimers.obj: C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/common/source/F2806x_CpuTimers.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_19.6.0.STS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/Users/John/workspace_v9/PWM_V1" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/F2806x_common/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/common/lib" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/headers/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/headers/source" --include_path="C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_19.6.0.STS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2806x_DefaultIsr.obj: C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/common/source/F2806x_DefaultIsr.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_19.6.0.STS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/Users/John/workspace_v9/PWM_V1" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/F2806x_common/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/common/lib" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/headers/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/headers/source" --include_path="C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_19.6.0.STS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2806x_EPwm.obj: C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/common/source/F2806x_EPwm.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_19.6.0.STS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/Users/John/workspace_v9/PWM_V1" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/F2806x_common/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/common/lib" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/headers/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/headers/source" --include_path="C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_19.6.0.STS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2806x_GlobalVariableDefs.obj: C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/headers/source/F2806x_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_19.6.0.STS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/Users/John/workspace_v9/PWM_V1" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/F2806x_common/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/common/lib" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/headers/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/headers/source" --include_path="C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_19.6.0.STS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2806x_PieCtrl.obj: C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/common/source/F2806x_PieCtrl.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_19.6.0.STS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/Users/John/workspace_v9/PWM_V1" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/F2806x_common/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/common/lib" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/headers/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/headers/source" --include_path="C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_19.6.0.STS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2806x_PieVect.obj: C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/common/source/F2806x_PieVect.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_19.6.0.STS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/Users/John/workspace_v9/PWM_V1" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/F2806x_common/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/common/lib" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/headers/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/headers/source" --include_path="C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_19.6.0.STS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2806x_SysCtrl.obj: C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/common/source/F2806x_SysCtrl.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_19.6.0.STS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/Users/John/workspace_v9/PWM_V1" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/F2806x_common/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/common/lib" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/headers/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/headers/source" --include_path="C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_19.6.0.STS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F2806x_usDelay.obj: C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/common/source/F2806x_usDelay.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_19.6.0.STS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/Users/John/workspace_v9/PWM_V1" --include_path="C:/ti/controlSUITE/device_support/f2806x/v151/F2806x_common/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/common/lib" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/headers/include" --include_path="C:/ti/c2000/C2000Ware_2_01_00_00/device_support/f2806x/headers/source" --include_path="C:/ti/ccs930/ccs/tools/compiler/ti-cgt-c2000_19.6.0.STS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


