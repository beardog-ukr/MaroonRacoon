del /F /Q build\common_obj\*

del /F /Q build\common_test_obj\*
del /F /Q build\testbin\vi_test_common.exe

del /F /Q build\chi2breaker_test_obj\*
del /F /Q build\testbin\vi_test_chi2breaker.exe

mingw32-make tests
