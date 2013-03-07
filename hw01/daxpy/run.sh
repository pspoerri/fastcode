#!/bin/bash

for (( i=1000; i<=2000000; i+=1000))
    do
        ./main $i
        ./main $i
    done
