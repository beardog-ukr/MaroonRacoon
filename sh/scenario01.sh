#!/bin/bash

# This script works with m1_orig.txt;
# First the file will be preprocessed, then encrypted, then decrypted. Results should be the same.

cp ./samples/m1_orig.txt ./tmp/m1_orig.txt

build/bin/vi_preprocessor -i ./tmp/m1_orig.txt -o ./tmp/m1_p_sec.txt -a ./samples/simpleEnglishCaps.txt

build/bin/vi_encoder -i ./tmp/m1_p_sec.txt -o ./tmp/m1_E_sec.txt -k BRAVO -a ./samples/simpleEnglishCaps.txt

build/bin/vi_decoder -i ./tmp/m1_E_sec.txt -o ./tmp/m1_dec.txt -k BRAVO -a ./samples/simpleEnglishCaps.txt




