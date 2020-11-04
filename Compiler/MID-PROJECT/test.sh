#!/bin/bash

test_items=$(ls test)

for item in $test_items;
do
    echo "[$item test start]"
    echo "[original source code]"
    cat "./test/$item"
    echo "[original source code end]"
    echo "[syntax tree]"
    ./run ./test/$item
    echo "[syntax tree end]"
    echo "[$item test end]"
done
