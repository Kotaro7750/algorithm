#!/bin/bash

echo "n,appendT,appendAVG,eraseT" > bench.csv
for ((i=1000 ; i<100000000 ; i*=5))
do
   ./a.out $i >> bench.csv
done

