#!/bin/bash
echo "enter  angle A"
read A
echo "enter angle B"
read B
echo "enter angle C"
read C
# sum all three angles
d=$((A+B+C))
if [ $A -eq 0 -o $B -eq 0 -o $C -eq 0 ]
then
echo "Enter angles greater than zero"
else
    if [ $d == 180 ];
    then
    echo "valid traingle"
    else
    echo "not a valid traingle"
    fi
fi