del /F /Q build\common_obj\*.o

del /F /Q build\common_test_obj\*.o
del /F /Q build\testbin\vi_test_common.exe

del /F /Q build\encoder_test_obj\*.o
del /F /Q build\testbin\vi_test_encoder.exe

mingw32-make tests
