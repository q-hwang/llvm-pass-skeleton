#!/bin/bash
BUILD_DIR="/home/qian/llvm-pass-skeleton/parsec-3.0/pkgs/kernels/streamcluster/inst/amd64-linux.gcc"
for i in {0..0}
do
    if [ -d "$BUILD_DIR" ] 
    then
        echo 'rm build dir'
        rm -r "$BUILD_DIR"
    fi
    cat opt_all.txt | python3.7 order_gen.py 10 > opt.txt

    parsecmgmt -a build -c gcc -p streamcluster > "/dev/null"

    for j in {0..5}
    do
        echo "$j"
        parsecmgmt -a run -c gcc -p streamcluster -i simlarge
    done
    mv opt.txt opts/opt_$(date +"%T").txt
done
