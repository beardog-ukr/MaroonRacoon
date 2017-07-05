#!/bin/bash

# This script works with m2_orig.txt;
# Uses capitalized alphabet
# First the file will be preprocessed, then encrypted, then decrypted without key. Results should be the same.

Basic="./samples/m2_orig.txt"
BasicTmp="./tmp/m2_orig.txt"
Preprocessed="./tmp/m2_p_sec.txt"
Alphabet="./samples/alphabets/simpleEnglishCaps.txt"
Encrypted="./tmp/m2_e_sec.txt"
Decrypted="./tmp/m2_d_sec.txt"
KeyStr="FIRE"
Frequencies="./samples/frequencies/engCapsFreq.txt"

rm -f $BasicTmp
rm -f $Preprocessed
rm -f $Encrypted
rm -f $Decrypted

cp $Basic $BasicTmp

./build/bin/vi_preprocessor -i $BasicTmp -o $Preprocessed -a $Alphabet

./build/bin/vi_encoder -i $Preprocessed -o $Encrypted -k $KeyStr -a $Alphabet

#echo ./build/bin/vi_breaker -i $Encrypted -o $Decrypted -f $Frequencies -a $Alphabet
./build/bin/vi_breaker -i $Encrypted -o $Decrypted -f $Frequencies -a $Alphabet

echo "Note: the real keyword was \"$KeyStr\""




