#!/bin/bash
echo "You provided the arguments:" "$@"

COMPILER="/usr/bin/clang++-9"
ARGS=""
while [ "$1" != "" ]; do
    case $1 in
        -c)
            FILE=$2
            shift
            ;;
        -o)
            OUT=$2
            shift
            ;;
        *)
            ARGS=$ARGS" "$1
            ;;
    esac
    shift
done
if [ -z "$OUT" ]
then
    if [ -z "$FILE" ]
    then 
        OUT='a.out'
    else
        OUT=${FILE%.*}.o
    fi
fi

OPT=`cat /home/qian/llvm-pass-skeleton/parsec-3.0/bin/opt.txt`
if [ -z "$FILE" ]
then
    echo "$COMPILER $ARGS -o $OUT"
    eval $COMPILER $ARGS -o $OUT 
else
    echo "$COMPILER $ARGS -S -emit-llvm $FILE -o ${FILE%.*}.ll"
	eval "$COMPILER $ARGS -S -emit-llvm $FILE -o ${FILE%.*}.ll"
    echo "opt-9 $OPT -S ${FILE%.*}.ll -ogit  ${FILE%.*}_.ll"
	eval "opt-9 $OPT -S ${FILE%.*}.ll -o ${FILE%.*}_.ll"
    echo "$COMPILER $ARGS -c ${FILE%.*}_.ll -o $OUT"
	eval "$COMPILER $ARGS -c ${FILE%.*}_.ll -o $OUT"
fi