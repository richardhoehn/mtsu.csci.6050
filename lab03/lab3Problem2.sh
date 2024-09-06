#!/bin/bash

gcc ./lab3Problem2.c -o lab3Problem2

./lab3Problem2 << EOF
Output format should be same as shown in the sample run below. Each word should be printed in separate lines.
EOF

./lab3Problem2 << EOF
A quick ivory unicorn jumps over the lazy elephant
EOF

./lab3Problem2 << EOF
A quick ivory unicorn jumps over the lazy elephant.
EOF