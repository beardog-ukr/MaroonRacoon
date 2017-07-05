set ORIG_FILE=samples\WHO_orig.txt
set ENCODED_FILE=tmp\WHO_E_sec.txt
set ALPH_FILE=samples\alphabets\simpleEnglishCaps.txt
set FREQ_FILE=samples\frequencies\engCapsFreq.txt
set DECODED_FILE=tmp\WHO_D_sec.txt
set PREPROCESSED_FILE=tmp\WHO_P_ec.txt

del /F /Q %ENCODED_FILE%

.\build\bin\vi_encoder.exe -o %ENCODED_FILE%  --in %ORIG_FILE% --alph %ALPH_FILE% -k HGFEDCBA
.\build\bin\vi_breaker.exe  -o %DECODED_FILE% --in %ENCODED_FILE%  --alph %ALPH_FILE% --fi %FREQ_FILE%

