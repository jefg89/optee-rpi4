OPTEE_BASE=$(pwd)
export PATH=${OPTEE_BASE}/buildroot/output/host/bin:${OPTEE_BASE}/myrootfs/usr/include:${OPTEE_BASE}/myrootfs/usr/lib:$PATH
export TA_DEV_KIT_DIR=${OPTEE_BASE}/optee_os/out/arm-plat-rpi4/export-ta_arm64
export TEEC_EXPORT=${OPTEE_BASE}/buildroot/output/host/aarch64-buildroot-linux-gnu/sysroot/usr
export CROSS_COMPILE=aarch64-buildroot-linux-gnu-
export HOST_CROSS_COMPILE=aarch64-buildroot-linux-gnu-
export TA_CROSS_COMPILE=aarch64-buildroot-linux-gnu-

