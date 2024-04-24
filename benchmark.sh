#!/bin/sh

BIN_DIR=$1
STATS_DIR=$2
STATS_FILE=$STATS_DIR/runs.out
STATS_CACHE_DIR=$STATS_DIR/cache_runs
OPTIM=''
MIN_MATRIX_DIM=8
MAX_MATRIX_DIM=14
NUM_REPETIONS=50

echo name,optim,size,time,bandwidth >> $STATS_FILE;

for file in $(ls $BIN_DIR)
do
    OPTIM=${file#*-} # Get optimization flag from suffix
    NAME=${file%-*} # Get file name
    for size in $(seq $MIN_MATRIX_DIM $MAX_MATRIX_DIM) # Loop over sizes
    do
        for i in $(seq 1 $NUM_REPETIONS) # Loop over the number of repetitions
        do
            printf "$NAME,$OPTIM,$size," >> $STATS_FILE
            $BIN_DIR/$file $size >> $STATS_FILE
        done
    done
    command -v valgrind > /dev/null;
    if [ $? -eq 0 ]
    then    
        valgrind -q --cachegrind-out-file=$STATS_CACHE_DIR/$file --tool=cachegrind $BIN_DIR/$file $MIN_MATRIX_DIM >/dev/null 2>>$STATS_DIR/cachegrind.err
        valgrind -q --cachegrind-out-file=$STATS_CACHE_DIR/$file --tool=cachegrind $BIN_DIR/$file $MAX_MATRIX_DIM >/dev/null 2>>$STATS_DIR/cachegrind.err
    fi
done

# Create summary of all cachegrind outputs
ls -A1q $STATS_CACHE_DIR | grep -q .
if [ $? -eq 0 ]
then 
    echo "name,Ir,I1mr,ILmr,Dr,D1mr,DLmr,Dw,D1mw,DLmw" >> $STATS_DIR/cache.out
    for file in $(ls $STATS_CACHE_DIR)
    do
        cache_summary=$(grep 'summary' $STATS_CACHE_DIR/$file)
        cache_file_summary=$(echo $file ${cache_summary#*:} | sed 's/ /,/g')
        echo $cache_file_summary >> $STATS_DIR/cache.out
    done
else
    echo No cachegrind files to summarize...
fi

