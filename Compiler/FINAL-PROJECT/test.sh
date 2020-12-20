#!/bin/bash

test_items=$(ls tests)
for item in $test_items;
do
   echo "./tests/$item"
    ./run.sh ./tests/$item
done

