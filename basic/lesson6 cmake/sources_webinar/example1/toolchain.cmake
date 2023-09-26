set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION "0.0.0")

set(TOOLCHAIN_PATH "/opt/homebrew")

SET(CMAKE_FIND_ROOT_PATH  ${TOOLCHAIN_PATH})

# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/bin/aarch64-none-elf-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/bin/aarch64-none-elf-g++)

set(CMAKE_C_FLAGS_INIT "-Wall -O2 -nostdlib -fpermissive -march=native" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_INIT "-Wall -O2 -nostdlib -fpermissive -march=native" CACHE STRING "" FORCE)
