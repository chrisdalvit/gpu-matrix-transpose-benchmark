# GPU Computing - First Assignment

This repository contains the code for the first assignment for the GPU computing course.

## Repository structure
The ```data``` folder contains the original benchmark data from the tested architectures that was used in the experimental analyses of the report. 

The ```lib``` folder contains C-functions used by all tested algorithms with the corresponding header file.

The ```report``` folder contains the LaTex report.

The ```src``` folder contains C files with the different algorithms for matrix transposition.

## Setup project
After cloning the repository you can run 
```
make
```
and the files in ```src``` are compiled, and the benchmark test is started and stored in the ```stats``` folder (that is created by the Makefile). __Waring: It can take a lot of time for the benchmarks to finish!__

If you only want to compile the files in ```src``` run 
```
make compile
```
This should compile all C files in ```src``` and store them into the (newly created) ```bin``` folder without starting the benchmarks. Compiled binaries follow the naming convention of ```<ALGORITHM>-<OPTIMIZATION LEVEL>```

## Validate implementations
The correctness of the provided implementations can be verified by running the compiled binaries in 'debug mode'. After compilation you can run 
```
./bin/<BINARY> <MATRIX SIZE> --debug
```
For example 
```
./bin/naive-0 2 --debug
```
Should output a randomly initialized matrix with dimension 2^2 and the corresponding transposed matrix. Additionaly the execution time and the effective bandwidth are displayed.