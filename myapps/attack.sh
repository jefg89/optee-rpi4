#!/bin/sh
echo "starting"
#for j in $(seq 1 10)
#do
    for i in $(seq -w 000 255)
    do  
        echo "launching sampler"
        ./sampler 1 2 > samples/samples_"$j"_"$i".txt &
        echo "launching attack"
        sleep 0.5
        ./tx $i
        echo "done, sleeping"
        sleep 2
    done
