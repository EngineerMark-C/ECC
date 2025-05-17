################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../code/kemu4/xf_asr/asr_audio.c" \
"../code/kemu4/xf_asr/base64.c" \
"../code/kemu4/xf_asr/hmac_sha256.c" \
"../code/kemu4/xf_asr/sha1.c" \
"../code/kemu4/xf_asr/websocket_client.c" 

COMPILED_SRCS += \
"code/kemu4/xf_asr/asr_audio.src" \
"code/kemu4/xf_asr/base64.src" \
"code/kemu4/xf_asr/hmac_sha256.src" \
"code/kemu4/xf_asr/sha1.src" \
"code/kemu4/xf_asr/websocket_client.src" 

C_DEPS += \
"./code/kemu4/xf_asr/asr_audio.d" \
"./code/kemu4/xf_asr/base64.d" \
"./code/kemu4/xf_asr/hmac_sha256.d" \
"./code/kemu4/xf_asr/sha1.d" \
"./code/kemu4/xf_asr/websocket_client.d" 

OBJS += \
"code/kemu4/xf_asr/asr_audio.o" \
"code/kemu4/xf_asr/base64.o" \
"code/kemu4/xf_asr/hmac_sha256.o" \
"code/kemu4/xf_asr/sha1.o" \
"code/kemu4/xf_asr/websocket_client.o" 


# Each subdirectory must supply rules for building sources it contributes
"code/kemu4/xf_asr/asr_audio.src":"../code/kemu4/xf_asr/asr_audio.c" "code/kemu4/xf_asr/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fC:/Users/Ye/Desktop/hangzhou20/ECC/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=2 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/kemu4/xf_asr/asr_audio.o":"code/kemu4/xf_asr/asr_audio.src" "code/kemu4/xf_asr/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/kemu4/xf_asr/base64.src":"../code/kemu4/xf_asr/base64.c" "code/kemu4/xf_asr/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fC:/Users/Ye/Desktop/hangzhou20/ECC/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=2 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/kemu4/xf_asr/base64.o":"code/kemu4/xf_asr/base64.src" "code/kemu4/xf_asr/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/kemu4/xf_asr/hmac_sha256.src":"../code/kemu4/xf_asr/hmac_sha256.c" "code/kemu4/xf_asr/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fC:/Users/Ye/Desktop/hangzhou20/ECC/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=2 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/kemu4/xf_asr/hmac_sha256.o":"code/kemu4/xf_asr/hmac_sha256.src" "code/kemu4/xf_asr/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/kemu4/xf_asr/sha1.src":"../code/kemu4/xf_asr/sha1.c" "code/kemu4/xf_asr/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fC:/Users/Ye/Desktop/hangzhou20/ECC/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=2 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/kemu4/xf_asr/sha1.o":"code/kemu4/xf_asr/sha1.src" "code/kemu4/xf_asr/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"code/kemu4/xf_asr/websocket_client.src":"../code/kemu4/xf_asr/websocket_client.c" "code/kemu4/xf_asr/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc26xb "-fC:/Users/Ye/Desktop/hangzhou20/ECC/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=2 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"code/kemu4/xf_asr/websocket_client.o":"code/kemu4/xf_asr/websocket_client.src" "code/kemu4/xf_asr/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-code-2f-kemu4-2f-xf_asr

clean-code-2f-kemu4-2f-xf_asr:
	-$(RM) ./code/kemu4/xf_asr/asr_audio.d ./code/kemu4/xf_asr/asr_audio.o ./code/kemu4/xf_asr/asr_audio.src ./code/kemu4/xf_asr/base64.d ./code/kemu4/xf_asr/base64.o ./code/kemu4/xf_asr/base64.src ./code/kemu4/xf_asr/hmac_sha256.d ./code/kemu4/xf_asr/hmac_sha256.o ./code/kemu4/xf_asr/hmac_sha256.src ./code/kemu4/xf_asr/sha1.d ./code/kemu4/xf_asr/sha1.o ./code/kemu4/xf_asr/sha1.src ./code/kemu4/xf_asr/websocket_client.d ./code/kemu4/xf_asr/websocket_client.o ./code/kemu4/xf_asr/websocket_client.src

.PHONY: clean-code-2f-kemu4-2f-xf_asr

