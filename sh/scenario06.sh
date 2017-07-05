#!/bin/bash

# This script works with pureRandom15_orig.txt;
# Uses capitalized alphabet
# First the file will be preprocessed, then encrypted, then decrypted without key. Results should be the same.

Basic="./samples/pureRandom15_orig.txt"
BasicTmp="./tmp/pureRandom15_orig.txt"
Preprocessed="./tmp/pureRandom15_p_sec.txt"
Alphabet="./samples/alphabets/simpleEnglishCaps.txt"
Encrypted="./tmp/pureRandom15_e_sec.txt"
Decrypted="./tmp/pureRandom15_d_sec.txt"
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
echo "Note: source file had ramdom content, so result may be incorrect"




