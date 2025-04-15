# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/qaisalhindi/capp/cap_template/task2/build/_deps/picotool-src"
  "/home/qaisalhindi/capp/cap_template/task2/build/_deps/picotool-build"
  "/home/qaisalhindi/capp/cap_template/task2/build/_deps"
  "/home/qaisalhindi/capp/cap_template/task2/build/pico-sdk/src/rp2040/boot_stage2/picotool/tmp"
  "/home/qaisalhindi/capp/cap_template/task2/build/pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp"
  "/home/qaisalhindi/capp/cap_template/task2/build/pico-sdk/src/rp2040/boot_stage2/picotool/src"
  "/home/qaisalhindi/capp/cap_template/task2/build/pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/qaisalhindi/capp/cap_template/task2/build/pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/qaisalhindi/capp/cap_template/task2/build/pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
