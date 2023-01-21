#!/bin/bash

if [ ! -f "sat" ]; then
    make
fi

./sat <tests/test0.in >tests/results.out 
diff tests/test0.out tests/results.out

