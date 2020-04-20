#!/bin/bash

# Executes job in the queue "std.q" unless you have special requirements.
#$ -q std.q

# Changes to the current working directory before performing any further action
#$ -cwd

# Name of your job. Unless you use the -o and -e options, output will
# go to a unique file name.ojob_id for each job.
#$ -N task2

# Redirect output stream to this file.
#$ -o output_task4_2.dat

# Join the error stream to the output stream.
#$ -j yes

# Parallel environment for using OpenMP, allocates 8 cores on a single node
#$ -pe openmp 8

# Increase the virtual memory per slot to 4GB
#$ -l h_vmem=4G

# Use gcc 8.2.0 as the default gcc
#module load gcc/8.2.0

# Set up any environment variables
#export ENVIRONMENT_VARIABLE=foobar
OMP_NUM_THREADS=1 ./ex2 1500
OMP_NUM_THREADS=2 ./ex2 1500
OMP_NUM_THREADS=4 ./ex2 1500
OMP_NUM_THREADS=8 ./ex2 1500
OMP_NUM_THREADS=1 ./ex2parallel 1500
OMP_NUM_THREADS=2 ./ex2parallel 1500
OMP_NUM_THREADS=4 ./ex2parallel 1500
OMP_NUM_THREADS=8 ./ex2parallel 1500
