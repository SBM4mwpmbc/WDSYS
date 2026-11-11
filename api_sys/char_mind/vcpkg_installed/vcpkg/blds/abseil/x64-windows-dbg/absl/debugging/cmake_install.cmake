# Install script for directory: C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/src/20260107.1-b1a4a53e9a.clean/absl/debugging

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_borrowed_fixup_buffer.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/absl/debugging/absl_borrowed_fixup_buffer.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_stacktrace.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_symbolize.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_examine_stack.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_failure_signal_handler.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_debugging_internal.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_demangle_internal.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_bounded_utf8_length_sequence.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_decode_rust_punycode.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/absl/debugging/absl_decode_rust_punycode.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_demangle_rust.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/absl/debugging/absl_demangle_rust.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_utf8_for_code_point.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/absl/debugging/absl_utf8_for_code_point.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_leak_check.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/lib/pkgconfig/absl_debugging.pc")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-dbg/absl/debugging/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
