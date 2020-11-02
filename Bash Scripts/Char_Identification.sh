#!/bin/bash
echo "enter a char"
read c

#set specified is [a-z], which is a shorthand way of typing [abcdefghijklmnopqrstuvwxyz]

#set specified is [0-9], which is a shorthand way of typing [0123456789]
if [[ $c == [A-Z] ]];
then
    echo "you have entered an alphabet"
elif [[ $c == [a-z] ]];
then
    echo "you have entered an alphabet"
elif [[ $c == [0-9] ]];
then
    echo "you have entered is a digit"
else
    echo "you have entered a special symbols!"
fi