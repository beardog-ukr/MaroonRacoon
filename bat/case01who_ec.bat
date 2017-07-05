set ORIG_FILE=samples\WHO_orig.txt
set ENCODED_FILE=tmp\WHO_E_ec.txt
set ALPH_FILE=samples\alphabets\englishSmall.txt
set FREQ_FILE=samples\frequencies\engFreq.txt
set DECODED_FILE=tmp\WHO_D_ec.txt
set PREPROCESSED_FILE=tmp\WHO_P_ec.txt

del /F /Q %ENCODED_FILE%
del /F /Q %PREPROCESSED_FILE%

.\build\bin\vi_preprocessor.exe -o %PREPROCESSED_FILE%  --in %ORIG_FILE% --alph %ALPH_FILE% 
.\build\bin\vi_encoder.exe -o %ENCODED_FILE%  --in %ORIG_FILE% --alph %ALPH_FILE% -k hgfedcba
.\build\bin\vi_breaker.exe  -o %DECODED_FILE% --in %ENCODED_FILE%  --alph %ALPH_FILE% --fi %FREQ_FILE%
