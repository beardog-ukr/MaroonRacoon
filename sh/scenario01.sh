#!/bin/bash

# This script works with m1_orig.txt;
# First the file will be preprocessed, then encrypted, then decrypted. Results should be the same.
# Uses capitalized alphabet

Basic="./samples/m1_orig.txt"
BasicTmp="./tmp/m1_orig.txt"
Preprocessed="./tmp/m1_p_sec.txt"
Alphabet="./samples/alphabets/simpleEnglishCaps.txt"
Encrypted="./tmp/m1_E_sec.txt"
Decrypted="./tmp/m1_D_sec.txt"
KeyStr="BRAVO"

rm -f $BasicTmp
rm -f $Preprocessed
rm -f $Encrypted
rm -f $Decrypted

cp $Basic $BasicTmp

./build/bin/vi_preprocessor -i $BasicTmp -o $Preprocessed -a $Alphabet

./build/bin/vi_encoder -i $Preprocessed -o $Encrypted -k $KeyStr -a $Alphabet

./build/bin/vi_decoder -i $Encrypted -o $Decrypted -k  $KeyStr -a $Alphabet




