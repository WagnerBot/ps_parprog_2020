#!/bin/bash

# Executes job in the queue "std.q" unless you have special requirements.
#$ -q std.q

# Changes to the current working directory before performing any further action
#$ -cwd

# Name of your job. Unless you use the -o and -e options, output will
# go to a unique file name.ojob_id for each job.
#$ -N had1

# Redirect output stream to this file.
#$ -o output_task7_1.dat

# Join the error stream to the output stream.
#$ -j yes

# Parallel environment for using OpenMP, allocates 8 cores on a single node
#$ -pe openmp 8

# Increase the virtual memory per slot to 4GB
#$ -l h_vmem=16G

# Use gcc 8.2.0 as the default gcc
#module load gcc/8.2.0

# Set up any environment variables
#export ENVIRONMENT_VARIABLE=foobar
./ex1 100000000 0 1
./ex1 100000000 1 1
./ex1 100000000 1 2
./ex1 100000000 1 4
./ex1 100000000 1 8



