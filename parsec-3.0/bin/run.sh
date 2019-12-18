#!/bin/bash
BUILD_DIR="/home/qian/llvm-pass-skeleton/parsec-3.0/pkgs/kernels/streamcluster/inst/amd64-linux.gcc"
comb=50
for i in `seq 1 $comb`;
do
    echo "$i"
    if [ -d "$BUILD_DIR" ] 
    then
        #echo 'rm build dir'
        rm -r "$BUILD_DIR"
    fi
    cat opt_all.txt | python3.7 order_gen.py 270 > opt.txt

    parsecmgmt -a build -c gcc -p streamcluster > "/dev/null"
    n=10
    f_all=0.0
    u_all=0.0
    s_all=0.0
    for j in `seq 1 $n`;
    do
        x=$(parsecmgmt -a run -c gcc -p streamcluster -i simlarge | grep 'real\|user\|sys')
        f=$(echo "$x" | grep 'real')
        u=$(echo "$x" | grep 'user')
        s=$(echo "$x" | grep 'sys')
        f="${f#*m}"
        u="${u#*m}"
        s="${s#*m}"
        f="${f::-1}"
        u="${u::-1}"
        s="${s::-1}"
        f_all=$(echo "$f_all + $f" | bc) 
        u_all=$(echo "$u_all + $u" | bc) 
        s_all=$(echo "$s_all + $s" | bc) 
    done
    
    file="opts/opt_$(date +"%T").txt"
    mv opt.txt "$file"
    f_all=$(echo "$f_all / $n" | bc -l)
    u_all=$(echo "$u_all / $n" | bc -l)
    s_all=$(echo "$s_all / $n" | bc -l)
    echo "$f_all $u_all $s_all"
    echo "$f_all $u_all $s_all" >> "$file"
done
