# Install script for directory: C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/src/20260107.1-b1a4a53e9a.clean/absl/strings

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/pkgs/abseil_x64-windows")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_string_view.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_strings.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_charset.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_has_ostream_operator.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_strings_internal.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_strings_resize_and_overwrite.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_strings_append_and_overwrite.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_str_format.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_str_format_internal.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_cord_internal.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_cordz_update_tracker.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_cordz_functions.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_cordz_statistics.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_cordz_handle.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_cordz_info.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_cordz_sample_token.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_cordz_update_scope.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_cord.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_generic_printer_internal.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/absl/strings/absl_generic_printer_internal.lib")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/absl/strings/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
