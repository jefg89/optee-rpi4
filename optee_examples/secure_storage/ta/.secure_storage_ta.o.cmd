old-cmd-./secure_storage_ta.o := aarch64-buildroot-linux-gnu-gcc -std=gnu11 -fdiagnostics-show-option -Wall -Wcast-align -Werror-implicit-function-declaration -Wextra -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Wmissing-prototypes -Wnested-externs -Wpointer-arith -Wshadow -Wstrict-prototypes -Wswitch-default -Wwrite-strings -Wno-missing-field-initializers -Wno-format-zero-length -Wno-c2x-extensions -Wredundant-decls -Wold-style-definition -Wstrict-aliasing=2 -Wundef -Wno-error=cast-align -Os -g3 -fpic -mstrict-align -mno-outline-atomics -fstack-protector-strong -MD -MF ./.secure_storage_ta.o.d -MT secure_storage_ta.o -nostdinc -isystem /home/jeferson/optee/buildroot/output/host/lib/gcc/aarch64-buildroot-linux-gnu/11.3.0/include -I./include -I./. -DARM64=1 -D__LP64__=1 -DMBEDTLS_SELF_TEST -D__OPTEE_CORE_API_COMPAT_1_1=1 -DTRACE_LEVEL=2 -I. -I/home/jeferson/optee/optee_os-rpi4/out/arm-plat-rpi4/export-ta_arm64/include -DCFG_ARM64_ta_arm64=1 -DCFG_TEE_TA_LOG_LEVEL='2' -DCFG_SYSTEM_PTA=1 -DCFG_UNWIND=1 -DCFG_TA_MBEDTLS=1 -DCFG_TA_MBEDTLS_SELF_TEST=1 -DCFG_TA_MBEDTLS_MPI=1 -DCFG_TA_FLOAT_SUPPORT=1 -DCFG_TA_OPTEE_CORE_API_COMPAT_1_1=1 -D__FILE_ID__=secure_storage_ta_c -c secure_storage_ta.c -o secure_storage_ta.o