################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../code/button.c" \
"../code/encoder.c" \
"../code/imu.c" \
"../code/init.c" \
"../code/ipsShow.c" \
"../code/motor.c" \
"../code/pid.c" \
"../code/sreer.c" \
"../code/uartReceiver.c" 

COMPILED_SRCS += \
"code/button.src" \
"code/encoder.src" \
"code/imu.src" \
"code/init.src" \
"code/ipsShow.src" \
"code/motor.src" \
"code/pid.src" \
"code/sreer.src" \
"code/uartReceiver.src" 

C_DEPS += \
"./code/button.d" \
"./code/encoder.d" \
"./code/imu.d" \
"./code/init.d" \
"./code/ipsShow.d" \
"./code/motor.d" \
"./code/pid.d" \
"./code/sreer.d" \
"./code/uartReceiver.d" 

OBJS += \
"code/button.o" \
"code/encoder.o" \
"code/imu.o" \
"code/init.o" \
"code/ipsShow.o" \
"code/motor.o" \
"code/pid.o" \
"code/sreer.o" \
"code/uartReceiver.o" 


# Each subdirectory must supply rules for building sources it contributes
"code/button.src":"../code/button.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/code/20/TC264_Library/Example/ECC/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/button.o":"code/button.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/encoder.src":"../code/encoder.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/code/20/TC264_Library/Example/ECC/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/encoder.o":"code/encoder.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/imu.src":"../code/imu.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/code/20/TC264_Library/Example/ECC/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/imu.o":"code/imu.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/init.src":"../code/init.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/code/20/TC264_Library/Example/ECC/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/init.o":"code/init.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/ipsShow.src":"../code/ipsShow.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/code/20/TC264_Library/Example/ECC/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/ipsShow.o":"code/ipsShow.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/motor.src":"../code/motor.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/code/20/TC264_Library/Example/ECC/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/motor.o":"code/motor.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/pid.src":"../code/pid.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/code/20/TC264_Library/Example/ECC/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/pid.o":"code/pid.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/sreer.src":"../code/sreer.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/code/20/TC264_Library/Example/ECC/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/sreer.o":"code/sreer.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/uartReceiver.src":"../code/uartReceiver.c" "code/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/code/20/TC264_Library/Example/ECC/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/uartReceiver.o":"code/uartReceiver.src" "code/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-code

clean-code:
	-$(RM) ./code/button.d ./code/button.o ./code/button.src ./code/encoder.d ./code/encoder.o ./code/encoder.src ./code/imu.d ./code/imu.o ./code/imu.src ./code/init.d ./code/init.o ./code/init.src ./code/ipsShow.d ./code/ipsShow.o ./code/ipsShow.src ./code/motor.d ./code/motor.o ./code/motor.src ./code/pid.d ./code/pid.o ./code/pid.src ./code/sreer.d ./code/sreer.o ./code/sreer.src ./code/uartReceiver.d ./code/uartReceiver.o ./code/uartReceiver.src

.PHONY: clean-code

