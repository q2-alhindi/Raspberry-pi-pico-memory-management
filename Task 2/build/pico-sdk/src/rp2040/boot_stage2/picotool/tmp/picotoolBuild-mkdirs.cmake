# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/qaisalhindi/Documents/pico/w1part1/task2/cap_template/build/_deps/picotool-src"
  "/home/qaisalhindi/Documents/pico/w1part1/task2/cap_template/build/_deps/picotool-build"
  "/home/qaisalhindi/Documents/pico/w1part1/task2/cap_template/build/_deps"
  "/home/qaisalhindi/Documents/pico/w1part1/task2/cap_template/build/pico-sdk/src/rp2040/boot_stage2/picotool/tmp"
  "/home/qaisalhindi/Documents/pico/w1part1/task2/cap_template/build/pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp"
  "/home/qaisalhindi/Documents/pico/w1part1/task2/cap_template/build/pico-sdk/src/rp2040/boot_stage2/picotool/src"
  "/home/qaisalhindi/Documents/pico/w1part1/task2/cap_template/build/pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/qaisalhindi/Documents/pico/w1part1/task2/cap_template/build/pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/qaisalhindi/Documents/pico/w1part1/task2/cap_template/build/pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
