#!/bin/bash

gcc ./lab4Problem2.c -o lab4Problem2

./lab4Problem2  << EOF
user1
password1
EOF

./lab4Problem2  << EOF
user2
password2
EOF

./lab4Problem2  << EOF
user10
password10
EOF