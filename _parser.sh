#!/bin/bash

gcc Parser.c
echo -e "gcc Parser.c\n"

echo -e "./a.out\n"
./a.out
echo -e "\n./a.out --Question"
./a.out --Question
echo -e "\n./a.out -q"
./a.out -q
echo -e "\n./a.out --query 6"
./a.out --query 6
echo -e "\n./a.out --longinformationrequest"
./a.out --longinformationrequest
echo -e "\n./a.out -l"
./a.out -l
echo -e "\n./a.out --version"
./a.out --version
echo -e "\n./a.out -Qviq 8"
./a.out -Qviq 8
echo -e "\n./a.out --version -q5"
./a.out --version -q5
echo -e "\n./a.out -q -iQ"
./a.out -q -iQ