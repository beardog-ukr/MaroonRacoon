#!/bin/bash

#find ./samples -name *.txt | xargs ex -bsc '%!awk "{sub(/\r/,\"\")}1"' -cx 

for winfile in $(find ./samples -name *.txt); do
  ex -bsc '%!awk "{sub(/\r/,\"\")}1"' -cx $winfile
done
#  ex -bsc '%!awk "{sub(/\r/,\"\")}1"' -cx 

#find ./ -name *.c | xargs touch
#find ./ -name *.h | xargs touch

#touch Makefile 

