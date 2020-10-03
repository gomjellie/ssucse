#!/usr/bin/zsh

for i in {1..8}
do
	./run ./test/$i\.c
done
