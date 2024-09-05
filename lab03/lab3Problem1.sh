#!/bin/bash

gcc ./lab3Problem1.c -o lab3Problem1

./lab3Problem1 << EOF
5
9 8 2 14 6
EOF

./lab3Problem1 << EOF
6
1 2 3 4 5 6
EOF

./lab3Problem1 << EOF
7
1 2 3 4 5 6 7
EOF