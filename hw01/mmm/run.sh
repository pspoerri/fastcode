#!/bin/bash

for (( i=100; i<=1500; i+=100))
    do
        echo "##############################################################"
        echo "## RUN $i"
        echo "##############################################################"
        ./main $i $i $i
        ./main $i $i $i
    done
