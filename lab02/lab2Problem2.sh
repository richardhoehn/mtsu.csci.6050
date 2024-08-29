#!/bin/bash

gcc ./lab2Problem2.c -o lab2Problem2.out

echo ""
./lab2Problem2.out

echo ""
./lab2Problem2.out 1

echo ""
./lab2Problem2.out 1 1

echo ""
./lab2Problem2.out 2 2 

echo "Should be: "
./lab2Problem2.out 2 3

echo "Should be: 24 - 4"
./lab2Problem2.out 4 3
echo ""

echo ""
./lab2Problem2.out 5 4
echo ""


echo "Should be = 3628800, 1"
./lab2Problem2.out 10 10
echo ""

echo "Should be = 30,240, 252"
./lab2Problem2.out 10 5
echo ""

echo "Should be 2,432,902,008,176,640,000, 1"
./lab2Problem2.out 20 20
echo ""

echo "Should be: 670,442,572,800 - 184,756"
./lab2Problem2.out 20 10
echo ""

echo ""
./lab2Problem2.out 5 21