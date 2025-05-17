################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../code/kemu4/kemu444.c" \
"../code/kemu4/zf_device_dot_matrix_screen.c" \
"../code/kemu4/zf_device_tld7002.c" 

COMPILED_SRCS += \
"code/kemu4/kemu444.src" \
"code/kemu4/zf_device_dot_matrix_screen.src" \
"code/kemu4/zf_device_tld7002.src" 

C_DEPS += \
"./code/kemu4/kemu444.d" \
"./code/kemu4/zf_device_dot_matrix_screen.d" \
"./code/kemu4/zf_device_tld7002.d" 

OBJS += \
"code/kemu4/kemu444.o" \
"code/kemu4/zf_device_dot_matrix_screen.o" \
"code/kemu4/zf_device_tld7002.o" 


# Each subdirectory must supply rules for building sources it contributes
"code/kemu4/kemu444.src":"../code/kemu4/kemu444.c" "code/kemu4/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fC:/Users/Ye/Desktop/hangzhou20/ECC/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=2 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/kemu4/kemu444.o":"code/kemu4/kemu444.src" "code/kemu4/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/kemu4/zf_device_dot_matrix_screen.src":"../code/kemu4/zf_device_dot_matrix_screen.c" "code/kemu4/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fC:/Users/Ye/Desktop/hangzhou20/ECC/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=2 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/kemu4/zf_device_dot_matrix_screen.o":"code/kemu4/zf_device_dot_matrix_screen.src" "code/kemu4/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/kemu4/zf_device_tld7002.src":"../code/kemu4/zf_device_tld7002.c" "code/kemu4/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fC:/Users/Ye/Desktop/hangzhou20/ECC/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=2 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/kemu4/zf_device_tld7002.o":"code/kemu4/zf_device_tld7002.src" "code/kemu4/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-code-2f-kemu4

clean-code-2f-kemu4:
	-$(RM) ./code/kemu4/kemu444.d ./code/kemu4/kemu444.o ./code/kemu4/kemu444.src ./code/kemu4/zf_device_dot_matrix_screen.d ./code/kemu4/zf_device_dot_matrix_screen.o ./code/kemu4/zf_device_dot_matrix_screen.src ./code/kemu4/zf_device_tld7002.d ./code/kemu4/zf_device_tld7002.o ./code/kemu4/zf_device_tld7002.src

.PHONY: clean-code-2f-kemu4

