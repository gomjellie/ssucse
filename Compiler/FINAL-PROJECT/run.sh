#!/bin/bash

COMPILER_PATH="/home/ubuntu/Developer/ssucse/Compiler/FINAL-PROJECT/compiler"
INTERPRETER_PATH="/home/ubuntu/Developer/ssucse/Compiler/FINAL-PROJECT/interpreter"

$COMPILER_PATH/compiler $1
$INTERPRETER_PATH/interpreter a.asm
