# Install script for directory: C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/dlib/src/v20.0.1-28a03c1bc0.clean/dlib

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/pkgs/dlib_x64-windows")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/dlib/x64-windows-rel/dlib/dlib.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/dlib" TYPE DIRECTORY FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/dlib/src/v20.0.1-28a03c1bc0.clean/dlib/" FILES_MATCHING REGEX "/[^/]*\\.h$" REGEX "/[^/]*\\.cmake$" REGEX "/[^/]*\\_tutorial\\.txt$" REGEX "/cassert$" REGEX "/cstring$" REGEX "/fstream$" REGEX "/iomanip$" REGEX "/iosfwd$" REGEX "/iostream$" REGEX "/istream$" REGEX "/locale$" REGEX "/ostream$" REGEX "/sstream$" REGEX "c:/users/reuben/wdsys/api_sys/char_mind/vcpkg_installed/vcpkg/blds/dlib/x64-windows-rel/dlib" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/dlib" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/dlib/x64-windows-rel/dlib/config.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/dlib" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/dlib/x64-windows-rel/dlib/revision.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/dlib/dlib.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/dlib/dlib.cmake"
         "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/dlib/x64-windows-rel/dlib/CMakeFiles/Export/531253a20d02778163542f6aeae55b41/dlib.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/dlib/dlib-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/dlib/dlib.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/dlib" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/dlib/x64-windows-rel/dlib/CMakeFiles/Export/531253a20d02778163542f6aeae55b41/dlib.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/dlib" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/dlib/x64-windows-rel/dlib/CMakeFiles/Export/531253a20d02778163542f6aeae55b41/dlib-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/dlib" TYPE FILE FILES
    "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/dlib/x64-windows-rel/dlib/config/dlibConfig.cmake"
    "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/dlib/x64-windows-rel/dlib/config/dlibConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/dlib/x64-windows-rel/dlib/dlib-1.pc")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/Reuben/WDSYS/api_sys/char_mind/vcpkg_installed/vcpkg/blds/dlib/x64-windows-rel/dlib/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
