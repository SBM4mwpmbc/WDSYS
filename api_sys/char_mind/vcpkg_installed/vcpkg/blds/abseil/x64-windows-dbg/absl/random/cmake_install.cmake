# Install script for directory: C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/src/20260107.1-b1a4a53e9a.clean/absl/random

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/pkgs/abseil_x64-windows/debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "OFF")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_random.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_bit_gen_ref.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_internal_mock_helpers.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_distributions.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_seed_gen_exception.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_seed_sequences.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_internal_traits.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_internal_distribution_caller.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_internal_fast_uniform_bits.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_internal_seed_material.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_internal_entropy_pool.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/absl/random/absl_random_internal_entropy_pool.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_internal_salted_seed_seq.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_internal_iostream_state_saver.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_internal_generate_real.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_internal_wide_multiply.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_internal_fastmath.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_internal_nonsecure_base.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_internal_pcg_engine.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_internal_randen_engine.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_internal_platform.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_internal_randen.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_internal_randen_slow.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_internal_randen_hwaes.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_internal_randen_hwaes_impl.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_internal_distribution_test_util.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_random_internal_uniform_helper.pc")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/absl/random/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
