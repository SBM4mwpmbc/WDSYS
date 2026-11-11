# 1 "C:/Users/Reuben/AppData/Local/vcpkg/downloads/tools/cmake-4.4.0-windows/cmake-4.4.0-windows-x86_64/share/cmake-4.4/Modules/FortranCInterface/call_mod.f90"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "C:/Users/Reuben/AppData/Local/vcpkg/downloads/tools/cmake-4.4.0-windows/cmake-4.4.0-windows-x86_64/share/cmake-4.4/Modules/FortranCInterface/call_mod.f90"
subroutine call_mod
  !DIR$ NOINLINE
  use mymodule
  use my_module
  call mysub()
  call my_sub()
end subroutine call_mod
