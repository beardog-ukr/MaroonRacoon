#!/bin/bash

# This script works with canada_orig.txt;
# First the file will be preprocessed, then encrypted, then decrypted with plain decoder. Results should be the same.
# Uses alphabet with small letters and space

Basic="./samples/canada_orig.txt"
BasicTmp="./tmp/canada_orig.txt"
Preprocessed="./tmp/canada_p_sec.txt"
Alphabet="./samples/alphabets/englishSmall.txt"
Encrypted="./tmp/canada_E_sec.txt"
Decrypted="./tmp/canada_D_sec.txt"
KeyStr="gamma"

rm -f $BasicTmp
rm -f $Preprocessed
rm -f $Encrypted
rm -f $Decrypted

cp $Basic $BasicTmp

./build/bin/vi_preprocessor -i $BasicTmp -o $Preprocessed -a $Alphabet

./build/bin/vi_encoder -i $Preprocessed -o $Encrypted -k $KeyStr -a $Alphabet

./build/bin/vi_decoder -i $Encrypted -o $Decrypted -k  $KeyStr -a $Alphabet




