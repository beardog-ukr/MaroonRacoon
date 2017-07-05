#!/bin/bash

# This script works with WHO_orig.txt;
# First the file will be preprocessed, then encrypted, then decrypted. Results should be the same.
# Uses alphabet with small letters and space

Basic="./samples/WHO_orig.txt"
BasicTmp="./tmp/WHO_orig.txt"
Preprocessed="./tmp/WHO_p_sec.txt"
Alphabet="./samples/alphabets/englishSmall.txt"
Encrypted="./tmp/WHO_E_sec.txt"
Decrypted="./tmp/WHO_D_sec.txt"
KeyStr="whiteowl"
Frequencies="./samples/frequencies/engFreq.txt"

rm -f $BasicTmp
rm -f $Preprocessed
rm -f $Encrypted
rm -f $Decrypted

cp $Basic $BasicTmp

./build/bin/vi_preprocessor -i $BasicTmp -o $Preprocessed -a $Alphabet

./build/bin/vi_encoder -i $Preprocessed -o $Encrypted -k $KeyStr -a $Alphabet

./build/bin/vi_breaker -i $Encrypted -o $Decrypted -f $Frequencies -a $Alphabet




