################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../code/kemu4/TLD7002_driver/TLD7002FuncLayer.c" \
"../code/kemu4/TLD7002_driver/TLD7002_ControlLayer.c" \
"../code/kemu4/TLD7002_driver/TLD7002_ServiceLayer.c" 

COMPILED_SRCS += \
"code/kemu4/TLD7002_driver/TLD7002FuncLayer.src" \
"code/kemu4/TLD7002_driver/TLD7002_ControlLayer.src" \
"code/kemu4/TLD7002_driver/TLD7002_ServiceLayer.src" 

C_DEPS += \
"./code/kemu4/TLD7002_driver/TLD7002FuncLayer.d" \
"./code/kemu4/TLD7002_driver/TLD7002_ControlLayer.d" \
"./code/kemu4/TLD7002_driver/TLD7002_ServiceLayer.d" 

OBJS += \
"code/kemu4/TLD7002_driver/TLD7002FuncLayer.o" \
"code/kemu4/TLD7002_driver/TLD7002_ControlLayer.o" \
"code/kemu4/TLD7002_driver/TLD7002_ServiceLayer.o" 


# Each subdirectory must supply rules for building sources it contributes
"code/kemu4/TLD7002_driver/TLD7002FuncLayer.src":"../code/kemu4/TLD7002_driver/TLD7002FuncLayer.c" "code/kemu4/TLD7002_driver/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fC:/Users/Ye/Desktop/hangzhou20/ECC/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=2 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/kemu4/TLD7002_driver/TLD7002FuncLayer.o":"code/kemu4/TLD7002_driver/TLD7002FuncLayer.src" "code/kemu4/TLD7002_driver/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/kemu4/TLD7002_driver/TLD7002_ControlLayer.src":"../code/kemu4/TLD7002_driver/TLD7002_ControlLayer.c" "code/kemu4/TLD7002_driver/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fC:/Users/Ye/Desktop/hangzhou20/ECC/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=2 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/kemu4/TLD7002_driver/TLD7002_ControlLayer.o":"code/kemu4/TLD7002_driver/TLD7002_ControlLayer.src" "code/kemu4/TLD7002_driver/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/kemu4/TLD7002_driver/TLD7002_ServiceLayer.src":"../code/kemu4/TLD7002_driver/TLD7002_ServiceLayer.c" "code/kemu4/TLD7002_driver/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fC:/Users/Ye/Desktop/hangzhou20/ECC/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=2 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/kemu4/TLD7002_driver/TLD7002_ServiceLayer.o":"code/kemu4/TLD7002_driver/TLD7002_ServiceLayer.src" "code/kemu4/TLD7002_driver/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-code-2f-kemu4-2f-TLD7002_driver

clean-code-2f-kemu4-2f-TLD7002_driver:
	-$(RM) ./code/kemu4/TLD7002_driver/TLD7002FuncLayer.d ./code/kemu4/TLD7002_driver/TLD7002FuncLayer.o ./code/kemu4/TLD7002_driver/TLD7002FuncLayer.src ./code/kemu4/TLD7002_driver/TLD7002_ControlLayer.d ./code/kemu4/TLD7002_driver/TLD7002_ControlLayer.o ./code/kemu4/TLD7002_driver/TLD7002_ControlLayer.src ./code/kemu4/TLD7002_driver/TLD7002_ServiceLayer.d ./code/kemu4/TLD7002_driver/TLD7002_ServiceLayer.o ./code/kemu4/TLD7002_driver/TLD7002_ServiceLayer.src

.PHONY: clean-code-2f-kemu4-2f-TLD7002_driver

