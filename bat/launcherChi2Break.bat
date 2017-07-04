REM .\build\bin\vi_encoder.exe -o tmp\act_E_sec.txt --in .\samples\act_orig.txt --alph .\samples\simpleEnglishCaps.txt -k AUSTRALIA
REM .\build\bin\vi_chi2breaker.exe  -o tmp\act.txt --in tmp\act_E_sec.txt --alph .\samples\simpleEnglishCaps.txt -k 9 --fi .\samples\engCapsFreq.txt

.\build\bin\vi_encoder.exe -o tmp\canada_E_sec.txt --in .\samples\canada_orig.txt --alph .\samples\simpleEnglishCaps.txt -k AIP
.\build\bin\vi_chi2breaker.exe  -o tmp\canada_D.txt --in tmp\canada_E_sec.txt --alph .\samples\simpleEnglishCaps.txt -k 3 --fi .\samples\engCapsFreq.txt



REM .\build\bin\CDapp.exe -r -i 555 -o oooo

REM .\build\bin\CDapp.exe --in aaa.txt  --out bbb.txt

REM .\build\bin\CDapp.exe --in --out bbb.txt
